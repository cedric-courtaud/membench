//
// Created by Cedric Courtaud on 23/05/2020.
//

#include "../include/membench/cli.h"

#include <getopt.h>
#include <iostream>
#include <regex>
#include <map>
#include <string>


#define INTERLEAVING_LONG_OPTS \
        {"interleaved",no_argument, nullptr,'i'}
#define INTERLEAVING_SHORT_OPTS "i"

#define INSTANCE_LONG_OPTS \
        {"read",required_argument, nullptr,'r'}, \
        {"write",required_argument, nullptr,'w'}, \
        {"throttle",required_argument, nullptr,'t'}, \
        {"memory-size",required_argument, nullptr,'s'}, \
        {"n-access",required_argument, nullptr,'n'}, \
        {"as-load",required_argument, nullptr,'l'}, \
        {"version", no_argument, nullptr, 'v'}

#define INSTANCE_SHORT_OPTS "r:w:t:s:vn:l"

#define SEQUENCE_ID_LONG_OPTS \
        {"access-sequence-id", required_argument, nullptr,'a'}

#define SEQUENCE_ID_SHORT_OPTS "a:"

std::map<std::string, size_t> size_multipliers = {
        {"K", 1000},
        {"M", 1000000},
        {"G", 1000000000},
        {"Ki", 0x400},
        {"Mi", 0x100000},
        {"Gi", 0x40000000},
};


static size_t parse_size(const std::string & s) {
    if (std::regex_match(s, std::regex("^[0-9]+$"))) {
        return std::stoi(s);
    }

    std::smatch matches;
    if (std::regex_search(s, matches,std::regex("^([0-9]+)([KMG]i?)$"))) {
        return std::stoi(matches[1]) * size_multipliers[matches[2]];
    }

    throw membench::IllFormattedSizeException();
}

static void parse_args (membench::MemBenchParams & p, int argc, char * const * argv, const char * short_ops,
                        const option * long_opts, bool support_interleaving=true) {

    char c = getopt_long(argc, argv, short_ops, long_opts, nullptr);
    while (c != -1) {
        switch (c) {
            case 'i':
                p.interleaved = support_interleaving;
                break;

            case 'r':
                p.n_read = std::stoi(optarg);
                break;

            case 'w':
                p.n_write = std::stoi(optarg);
                break;

            case 't':
                p.throttle = std::stoi(optarg);
                break;

            case 's':
                p.array_size_B = parse_size(optarg);
                break;

            case 'a':
                p.access_policy = std::string(optarg);
                break;

            case 'n':
                p.max_count = parse_size(optarg);
                break;

            case 'l':
                p.as_load = true;
                break;

            case 'v':
                std::cout << "0.0.1" << std::endl;
                exit(EXIT_SUCCESS);


            default:
                std::cerr << "Unrecognized option: " << c << std::endl;
                exit(EXIT_FAILURE);
        }

        c = getopt_long(argc, argv, short_ops, long_opts, nullptr);
    }
}

void membench::parse_sequence_args (membench::MemBenchParams & p, int argc, char **argv, bool support_interleaving) {
    auto * short_ops = INSTANCE_SHORT_OPTS INTERLEAVING_SHORT_OPTS;

    const option long_opts [] = {
            INTERLEAVING_LONG_OPTS,
            INSTANCE_LONG_OPTS,
            {nullptr,0, nullptr,0}
    };

    parse_args(p, argc, argv, short_ops, long_opts, support_interleaving);

    if (p.n_read   < 0) throw membench::UnspecifiedReadNumberException();
    if (p.n_write  < 0) throw membench::UnspecifiedWriteNumberException();
    if (p.throttle < 0) throw membench::UnspecifiedThrottleException();
}

void membench::parse_membench_args (membench::MemBenchParams & p, int argc, char **argv, bool support_interleaving) {
    auto * short_ops = INSTANCE_SHORT_OPTS INTERLEAVING_SHORT_OPTS SEQUENCE_ID_SHORT_OPTS;

    const option long_opts [] = {
            INTERLEAVING_LONG_OPTS,
            INSTANCE_LONG_OPTS,
            SEQUENCE_ID_LONG_OPTS,
            {nullptr,0, nullptr,0}
    };

    parse_args(p, argc, argv, short_ops, long_opts, support_interleaving);

    if (p.n_read   < 0) throw membench::UnspecifiedReadNumberException();
    if (p.n_write  < 0) throw membench::UnspecifiedWriteNumberException();
    if (p.throttle < 0) throw membench::UnspecifiedThrottleException();
    if (p.access_policy.empty()) throw membench::UnspecifiedSequenceAccessPolicyException();
}