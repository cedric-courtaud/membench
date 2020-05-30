//
// Created by Cedric Courtaud on 26/05/2020.
//

#ifndef MEMBENCH_INSTANCES_H
#define MEMBENCH_INSTANCES_H

#include <map>
#include <memory>
#include <membench/MemBenchParams.h>

extern std::map<const std::string, std::shared_ptr<membench::MemBenchInstance> > instances;

#endif //MEMBENCH_INSTANCES_H
