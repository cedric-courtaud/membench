//
// Created by Cedric Courtaud on 23/05/2020.
//

#ifndef MEMBENCH_CLI_H
#define MEMBENCH_CLI_H

#include <exception>

#include "MemBenchParams.h"
#include "macros.h"

namespace membench {
    MB_EXCEPTION(IllFormattedSizeException, "Ill formatted size");

    MB_EXCEPTION(UnspecifiedReadNumberException, "Number of read is not specified");
    MB_EXCEPTION(UnspecifiedWriteNumberException, "Number of write is not specified");
    MB_EXCEPTION(UnspecifiedThrottleException, "Throttle is not specified");
    MB_EXCEPTION(UnspecifiedSequenceAccessPolicyException, "Sequence's access policy is not specified");

    void parse_membench_args (MemBenchParams & p, int argc, char **argv, bool support_interleaving=true);
    void parse_sequence_args (MemBenchParams & p, int argc, char **argv, bool support_interleaving=true);
}

#endif
