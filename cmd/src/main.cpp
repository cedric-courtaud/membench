#include <iostream>

#include <membench/MemBenchParams.h>
#include <membench/cli.h>
#include <membench/RCW.h>

#include "instances.h"

int main(int argc, char ** argv) {
    membench::MemBenchParams p;
    membench::parse_membench_args(p, argc, argv);

    auto it = instances.find(p.access_policy);

    if (it == instances.end()) {
        std::cerr << "Error: instance with id \"" << p.access_policy << "\" does not exist." << std::endl;
        exit(EXIT_FAILURE);
    }

    auto v = it->second;
    try {
        v->init(p);
    } catch (membench::DifferentMLPInterleavingException & e) {
        std::cerr << "Trying to interleave iterators with different MLP values. Aborting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    auto value = v->run();

    std::cout << "[MemBench] computed value is " << value << std::endl;

    return 0;
}
