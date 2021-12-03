// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_TARGET_H
#define MHT_TARGET_H

#include "log/log.h"
#include "tracker/kalman.h"

namespace mht_tracker {


class Target: protected Kalman {

public:

    Target();
  
    ~Target();

    float likeLihood();

private:

};

}

#endif