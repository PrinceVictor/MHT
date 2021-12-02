// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/28
// Author: Hongbin Zhou

#include "common/random.h"

namespace mht_common {

Random::Random(){

    LOG_INFO("Construct RANDOM GENERATOR");
    
}

std::default_random_engine Random::_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

}