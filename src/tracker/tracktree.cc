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
    auto p_d = params._P_DETECTION, d_gate=params._TRACK_GATE_THRES; 
    auto track_score_conf_thre=params._TRACK_SCORE_CONF_THRES, track_score_del_thres= params._TRACK_SCORE_DEL_THRES;
    auto p_fa = params._CLUTTER_DENSITY/params._SCENE_VOLUME, p_n=params._NEW_TARGET_DENSITY;
    auto volume = params._SCENE_VOLUME;
    auto q = {params._POSITION_VAR, params._VELOCITY_VAR};

    if(flag == NEW_TRACK){
        
        _track_id = TrackTree::TRACK_ID_COUNT;
        _track_history.emplace_back(_detection_id);
        _target = make_shared<Target>(meas, r, p, d_gate, q, delta_t);
        _target->initTrackScore(p_d, track_score_del_thres, track_score_conf_thre, 
                                p_fa, p_n, volume);


        TrackTree::trackCount();
    }
}

TrackTree::TrackTree(const int flag, MyTrack& parent, const int& detect_id, const Eigen::VectorXf& meas){
    
    _parent = parent;
    _target = parent->_target;
    _track_history = parent->_track_history;
    _track_id = parent->_track_id;
    _scan_k = parent->_scan_k+1;
    _detection_id = detect_id;
    _track_history.emplace_back(_detection_id);
    _children.clear();

    if(flag==MISS_DETECTION){
        
        _target->missDetection();
    }
    else if(flag==ASSCIATED_TRACK){
        
        #ifdef USE_DEBUG
            LOG_INFO("Track Tree id:{} Parent:{} Current:{}", _track_id, parent->_detection_id, detect_id);
        #endif
        _target->updateLLR(meas);
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

    #ifdef USE_DEBUG
        LOG_INFO("Track id {} X_state x:{:.3f} y{:.3f}", _track_id, _target->_X_pre(0), _target->_X_pre(1));
    #endif
}

void TrackTree::update(const int flag, MyTrack& parent, const int& detect_id, const Eigen::VectorXf& meas){

    _children.emplace_back(make_shared<TrackTree>(flag, parent, detect_id, meas));

}

void TrackTree::addChild(shared_ptr<TrackTree>& child){

}

void TrackTree::trackCount(){
    
    TrackTree::TRACK_ID_COUNT++;
}

void TrackTree::getLeaves(MyTrack& root, vector<MyTrack>& result, const int& dim){

    if(root->_scan_k == dim){
        result.emplace_back(root);
        return;
    }
    
    for(int i=0; i<root->_children.size(); i++){
        getLeaves(root->_children[i], result, dim);
    }

}
    
}