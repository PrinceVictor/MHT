// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/28
// Author: Hongbin Zhou

#ifndef MHT_RANDOM_H
#define MHT_RANDOM_H

#include <random>
#include <chrono>
#include <vector>
#include <iostream>

#include "log/log.h"

namespace mht_common {

class Random{

public:
    
    Random();

    template<typename T>
    void get_uniform_randoms(std::vector<T>& result, float min=0.0, float max=1.0, int num=1){
    
        if(num < 1) return;

        result.resize(num);
        std::uniform_real_distribution<T> distribution(min,max);
        for(int i = 0; i < num; ++i){
            result[i] = distribution(_random_engine);
        }
    }

    template<typename T>
    void get_normal_randoms(std::vector<T>& result, float mean=0, float variance=1, int num=1){
        
        if(num < 1) return;

        result.resize(num);
        std::normal_distribution<T> distribution(mean, variance);
        for(int i = 0; i < num; ++i){
            result[i] = distribution(_random_engine);
        }
    }

    template<typename T>
    void get_possion_randoms(std::vector<T>& result, float expect, int num=1){
        
        if(num < 1) return;

        result.resize(num);
        std::poisson_distribution<T> distribution(expect);
        for(int i = 0; i < num; ++i){
            result[i] = distribution(_random_engine);
        }
    }

private:

    std::default_random_engine _random_engine;

};

}


#endif