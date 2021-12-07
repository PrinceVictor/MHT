// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#ifndef MHT_TRACK_H
#define MHT_TRACK_H

#include <vector>
#include <memory>

#include "log/log.h"
#include "tracker/target.h"
#include "tracker/mhtparam.h"

namespace mht_tracker {

#define MISS_DETECTION 0
#define NEW_TRACK 1
#define ASSCIATED_TRACK 2

using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

class TrackTree;

typedef shared_ptr<Target> MyTarget;
typedef shared_ptr<TrackTree> MyTrack;

class TrackTree{

public:

    TrackTree();

    TrackTree(const int flag, uint scan_k, uint detection_id, 
              const Eigen::VectorXf meas, const MHTParams& params);

    TrackTree(const int flag, MyTrack& parent, const int& detect_id,
              const Eigen::VectorXf& meas=Eigen::VectorXf::Zero(0));

    // TrackTree(shared_ptr<TrackTree>& parent);
    ~TrackTree();

    void initParams(const MHTParams& params);

    void predict();

    void update(const int flag, MyTrack& parent, const int& detect_id=0, const Eigen::VectorXf& meas=Eigen::VectorXf::Zero(0));

    void inherit(const int flag);

    void addChild(shared_ptr<TrackTree>& child);

    static void getLeaves(const MyTrack& root, vector<MyTrack>& result, const int& dim);

    static void getConflictHypos(const vector<MyTrack>& hypos, vector<vector<int>>& conflict_ids, const int& N_scan);

private:

    static void trackCount();

public:

    int _scan_k, _detection_id;

    int _track_id;

    vector<uint> _track_history;

    weak_ptr<TrackTree> _parent;

    vector<MyTrack> _children;

    MyTarget _target;

    

private:

    static uint TRACK_ID_COUNT;
    

};
    
}

#endif 