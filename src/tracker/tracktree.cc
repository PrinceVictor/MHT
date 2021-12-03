// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#include "tracker/tracktree.h"

namespace mht_tracker {

uint TrackTree::TRACK_ID = 0;

TrackTree::TrackTree(const uint scan_k):_scan_k(scan_k){

}

TrackTree::TrackTree(const uint scan_k, const Eigen::VectorXf meas)
:_scan_k(scan_k){
    

}

// TrackTree::TrackTree(shared_ptr<TrackTree>& parent):_parent(parent){

// }

TrackTree::~TrackTree(){

    std::cout<< "delete tree" << std::endl;
}

void TrackTree::addChild(shared_ptr<TrackTree>& child){

}

    
}