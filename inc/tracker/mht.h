// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_MHT_H
#define MHT_MHT_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "log/log.h"
#include "common/utils.h"
#include "tracker/mht_param.h"
#include "tracker/tracktree.h"

namespace mht_tracker {

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

class MHT {
    
public:

    MHT();

    MHT(const std::string& param_path);

    void run(const float& t, const vector<Eigen::VectorXf>& meas);

    void test();

    ~MHT();

private:

private:

    MHTParams _params;

    std::shared_ptr<TrackTree> _track_tree;
    

};

}

#endif