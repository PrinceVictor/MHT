// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#include "tracker/tracktree.h"

namespace mht_tracker {

uint TrackTree::TRACK_ID_COUNT = 0;

TrackTree::TrackTree(){
}

TrackTree::TrackTree(const int flag, const uint scan_k, const uint detection_id, 
                     Eigen::VectorXf meas, const MHTParams& params){
    _scan_k = scan_k;
    _detection_id = detection_id;

    auto delta_t = params._DELTA_T, r = params._MEAS_VAR, p = params._STATE_VAR;
    auto p_d = params._P_DETECTION, _d_gate=params._TRACK_GATE_THRES; 
    auto track_score_conf_thre=params._TRACK_SCORE_CONF_THRES, track_score_del_thres= params._TRACK_SCORE_DEL_THRES;
    auto p_fa = params._CLUTTER_DENSITY, p_n=params._NEW_TARGET_DENSITY;
    auto q = {params._POSITION_VAR, params._VELOCITY_VAR};

    if(flag == NEW_TRACK){
        
        _track_id = TrackTree::TRACK_ID_COUNT;
        _track_history.emplace_back(_detection_id);
        _target = make_shared<Target>(meas, r, p, q, delta_t);


        TrackTree::trackCount();
    }

}

void initParams(const MHTParams& params){

}

// TrackTree::TrackTree(shared_ptr<TrackTree>& parent):_parent(parent){

// }

TrackTree::~TrackTree(){

    std::cout<< "delete tree" << std::endl;
}

void TrackTree::predict(){

    _target->predict();

}

void TrackTree::update(const Eigen::VectorXf& meas){

    _target->update(meas);
}

void TrackTree::addChild(shared_ptr<TrackTree>& child){

}

void TrackTree::trackCount(){
    
    TrackTree::TRACK_ID_COUNT++;
}

void TrackTree::getLeaves(MyTrack& root, vector<MyTrack>& result, const int& dim){
    if(root->_scan_k == dim){
        result.push_back(root);
        return;
    }
    
    for(int i=0; i<root->_children.size(); i++){
        getLeaves(root->_children[i], result, dim);
    }

}
    
}