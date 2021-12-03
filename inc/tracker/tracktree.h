// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#ifndef MHT_TRACK_H
#define MHT_TRACK_H

#include <vector>
#include <memory>

#include "log/log.h"
#include "tracker/kalman.h"

namespace mht_tracker {

using std::vector;
using std::shared_ptr;
using std::weak_ptr;

class TrackTree{

public:

    TrackTree(const uint scan_k);

    TrackTree(const uint scan_k, const Eigen::VectorXf meas);

    // TrackTree(shared_ptr<TrackTree>& parent);

    void addChild(shared_ptr<TrackTree>& child);

    ~TrackTree();

public:

    const uint _scan_k;

    weak_ptr<TrackTree> _parent;

    vector<shared_ptr<TrackTree>> _children;



private:

    static uint TRACK_ID;

};
    
}

#endif 