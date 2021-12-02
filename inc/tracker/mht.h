// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_KALMAN_H
#define MHT_KALMAN_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "log/log.h"
#include "common/utils.h"
#include "tracker/mht_param.h"

namespace mht_tracker {

using std::string;
using std::vector;

class MHT {
    
public:

    MHT();

    MHT(const std::string& param_path);

    void run();

    ~MHT();

private:

    std::map<string, string> load_param_file(const string& param_path);

private:

    MHTParams _params;
    

};

}

#endif