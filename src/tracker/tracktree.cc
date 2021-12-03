// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#include "tracker/tracktree.h"

namespace mht_tracker {

uint TrackTree::TRACK_ID_COUNT = 0;

TrackTree::TrackTree(const uint scan_k):_scan_k(scan_k){

}

TrackTree::TrackTree(const int flag, const uint scan_k, const Eigen::VectorXf meas, const float& r, const float& p, 
                     const vector<float>& q, const float& delta_t)
:_scan_k(scan_k){
    
    if(flag == NEW_TRACK){
        _track_id = TrackTree::TRACK_ID_COUNT;

        _target = make_shared<Target>(meas, r, p, q, delta_t);
        TrackTree::trackCount();
    }

}

// TrackTree::TrackTree(shared_ptr<TrackTree>& parent):_parent(parent){

// }

TrackTree::~TrackTree(){

    std::cout<< "delete tree" << std::endl;
}

void TrackTree::trackCount(){
    
    TrackTree::TRACK_ID_COUNT++;
}

void TrackTree::addChild(shared_ptr<TrackTree>& child){

}

    
}