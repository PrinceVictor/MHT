// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_MEAS_H
#define MHT_MEAS_H

#include "log/log.h"
#include <iostream>

namespace mht_measurement {

class Measurement {

public:
  
    Measurement();

    Measurement(const string& param_path);

    ~Measurement();

    add_target();

private:

    const string _param_path;


};

}

#endif