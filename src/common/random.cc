// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/28
// Author: Hongbin Zhou

#include "common/random.h"

namespace mht_common {

Random::Random(){

    LOG_INFO("Construct RANDOM GENERATOR");

    auto curr_seed = std::chrono::system_clock::now().time_since_epoch.count();
    _random_engine.seed(curr_seed);
}

void Random::get_uniform_randoms(std::vector<float>& result, float min, float max, int num){
    
    if(num < 1) return;

    result.resize(num);
    std::uniform_real_distribution<float> distribution(min,max);
    for(int i = 0; i < num; ++i){
        result[i] = distribution(_random_engine);
    }
}

template<typename T>
void Random::get_possion_randoms(std::vector<T>& result, float expect, int num=1){
    
    if(num < 1) return;

    result.resize(num);
    std::poisson_distribution<T> distribution(expect);
    for(int i = 0; i < num; ++i){
        result[i] = distribution(_random_engine);
    }
}

}