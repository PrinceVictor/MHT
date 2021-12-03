// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#ifndef MHT_TRACK_H
#define MHT_TRACK_H

#include <vector>
#include <memory>

#include "log/log.h"
#include "tracker/target.h"

namespace mht_tracker {

#define NEW_TRACK 0
#define ASSCIATED_TRACK 1
#define MISS_DETECTION 2

using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

class TrackTree{

public:

    TrackTree(const uint scan_k);

    TrackTree(const int flag, const uint scan_k, const Eigen::VectorXf meas, const float& r, const float& p, 
              const vector<float>& q, const float& delta_t);

    // TrackTree(shared_ptr<TrackTree>& parent);

    void addChild(shared_ptr<TrackTree>& child);

    ~TrackTree();

private:

    static void trackCount();

public:

    const uint _scan_k;

    weak_ptr<TrackTree> _parent;

    vector<shared_ptr<TrackTree>> _leaves;

    shared_ptr<Target> _target;

    uint _track_id;

private:

    static uint TRACK_ID_COUNT;
    

};
    
}

#endif 