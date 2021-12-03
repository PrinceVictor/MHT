// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#include "tracker/tracktree.h"

namespace mht_tracker {

TrackTree::TrackTree(){
}

TrackTree::TrackTree(shared_ptr<TrackTree>& parent):_parent(parent){

}

void TrackTree::addChild(shared_ptr<TrackTree>& child){

}

TrackTree::~TrackTree(){

    std::cout<< "delete tree" << std::endl;
}
    
}