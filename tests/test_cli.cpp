//
// Created by Cedric Courtaud on 25/05/2020.
//

#include <membench/cli.h>
#include <gtest/gtest.h>

TEST(MembenchCLI, InstanceArgParsing) {
    const char * argv [] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", nullptr
    };

    auto argc = 7;

    membench::MemBenchParams p;

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.interleaved, false);
}

TEST(MembenchCLI, InstanceArgParsingIgnoreInterleaving) {
    const char * argv [] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", nullptr
    };

    auto argc = 8;

    membench::MemBenchParams p;

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), false);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.interleaved, false);
}

TEST(MembenchCLI, InstanceArgParsingSetInterleaving) {
    const char * argv [] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", nullptr
    };

    auto argc = 8;

    membench::MemBenchParams p;

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.interleaved, true);
}

TEST(MembenchCLI, InstanceArgParsingSetMemorySize) {
    const char *argv[] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", "-s", "256", nullptr
    };

    auto argc = 10;

    membench::MemBenchParams p;

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.array_size_B, 256);
}

TEST(MembenchCLI, InstanceArgParsingSetMemorySizeK) {
    auto argc = 10;
    membench::MemBenchParams p;

    const char *argv[] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", "-s", "256K", nullptr
    };

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.array_size_B, 256 * 1000);
}

TEST(MembenchCLI, InstanceArgParsingSetMemorySizeM) {
    auto argc = 10;
    membench::MemBenchParams p;

    const char *argv[] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", "-s", "256M", nullptr
    };

    argv[9] = "256M";

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.array_size_B, 256 * 1000 * 1000);
}

TEST(MembenchCLI, InstanceArgParsingSetMemorySizeG) {
    auto argc = 10;
    membench::MemBenchParams p;

    const char * argv [] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", "-s", "256G", nullptr
    };

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.array_size_B, 256000000000);
}

TEST(MembenchCLI, InstanceArgParsingSetMemorySizeKi) {
    auto argc = 10;
    membench::MemBenchParams p;

    const char *argv[] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", "-s", "256Ki", nullptr
    };

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.array_size_B, 256 * 1024);
}

TEST(MembenchCLI, InstanceArgParsingSetMemorySizeMi) {
    auto argc = 10;
    membench::MemBenchParams p;

    const char *argv[] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", "-s", "256Mi", nullptr
    };

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.array_size_B, 256u << 20u);
}


TEST(MembenchCLI, InstanceArgParsingSetMemorySizeGi) {
    auto argc = 10;
    membench::MemBenchParams p;

    const char * argv [] = {
            "unused", "--read", "10", "--write", "5", "--throttle", "100", "-i", "-s", "256Gi", nullptr
    };

    membench::parse_sequence_args(p, argc, const_cast<char **>(argv), true);

    ASSERT_EQ(p.n_read, 10);
    ASSERT_EQ(p.n_write, 5);
    ASSERT_EQ(p.throttle, 100);
    ASSERT_EQ(p.array_size_B, 274877906944);
}

TEST(MembenchCLI, InstanceArgMissingReadArgs) {
    const char * argv [] = {
            "unused", "--write", "5", "--throttle", "100", nullptr
    };

    auto argc = 5;

    membench::MemBenchParams p;

    ASSERT_THROW(
            membench::parse_sequence_args(p, argc, const_cast<char **>(argv), false),
            membench::UnspecifiedReadNumberException
    );
}

TEST(MembenchCLI, InstanceArgMissingWriteArgs) {
    const char * argv [] = {
            "unused", "--read", "5", "--throttle", "100", nullptr
    };

    auto argc = 5;

    membench::MemBenchParams p;

    ASSERT_THROW(
            membench::parse_sequence_args(p, argc, const_cast<char **>(argv), false),
            membench::UnspecifiedWriteNumberException
    );
}

TEST(MembenchCLI, InstanceArgMissingThrottleArgs) {
    const char * argv [] = {
            "unused", "--read", "5", "--write", "100", nullptr
    };

    auto argc = 5;

    membench::MemBenchParams p;

    ASSERT_THROW(
            membench::parse_sequence_args(p, argc, const_cast<char **>(argv), false),
            membench::UnspecifiedThrottleException
    );
}

TEST(MembenchCLI, MembenchApp) {
    const char * argv [] = {
            "unused", "-a","seq-id" ,"--read", "5", "--write", "100", "-t", "0", nullptr
    };

    auto argc = 9;

    membench::MemBenchParams p;
    membench::parse_membench_args(p, argc, const_cast<char **>(argv), false);

    ASSERT_TRUE(p.access_policy == "seq-id");
}

TEST(MembenchCLI, MembenchAppMissingAccessSequenceId) {
    const char * argv [] = {
            "unused", "--read", "5", "--write", "100", "-t", "0", nullptr
    };

    auto argc = 7;

    membench::MemBenchParams p;

    ASSERT_THROW(
            membench::parse_membench_args(p, argc, const_cast<char **>(argv), false),
            membench::UnspecifiedSequenceAccessPolicyException
    );
}