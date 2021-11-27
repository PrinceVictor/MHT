// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/28
// Author: Hongbin Zhou

#ifndef MHT_RANDOM_H
#define MHT_RANDOM_H

#include <random>
#include <chrono>
#icnlude <vector>

#include "log/log.h"

namespace mht_common {

class Random{

public:
    
    Random();

    void get_uniform_randoms(std::vector<float>& result, float min=0.0, float max=1.0, int num=1);

    template<typename T>
    void get_possion_randoms(std::vector<T>& result, float expect, int num=1);

private:

    std::default_random_engine _random_engine;

};

}


#endif