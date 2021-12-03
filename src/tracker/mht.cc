// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "tracker/mht.h"

namespace mht_tracker {

uint MHT::SCAN_K = 0;

MHT::MHT(){

    LOG_INFO("Construct Multiple Hypothesis Tracker");
}

MHT::MHT(const string& param_path):_params(param_path){

    LOG_INFO("Construct Multiple Hypothesis Tracker");
}

MHT::~MHT(){

}

void MHT::run(const float& t, const vector<Eigen::VectorXf>& meas){

    LOG_INFO("run MHT! t:{:.1f}s \tmeas size:{}", t, meas.size());
    int last_track_num = _track_trees.size();

    for(int i = 0; i < last_track_num; i++){
        auto& leaves = _track_trees[i]->_leaves;
        for(int j = 0; j < leaves.size(); j++){

        }
    }

    for(int i = 0; i < meas.size(); i++){
        
        LOG_INFO("meas id:{} \tpos x:{:.2f}, y:{:.2f}", i, meas[i](0), meas[i](1));

        if(last_track_num){
            for(int j = 0; j < last_track_num; j++){
                auto& leaves = _track_trees[j]->_leaves;
                for(int k = 0; k < leaves.size(); k++){
                    // curr_tracks[k]->_target.update
                }
            }
        }
        
        auto delta_t = _params._DELTA_T, r = _params._MEAS_VAR, p = _params._STATE_VAR;
        auto q = {_params._POSITION_VAR, _params._VELOCITY_VAR};
        _track_trees.emplace_back(std::make_shared<TrackTree>(NEW_TRACK, SCAN_K, meas[i],
                                                             r, p, q, delta_t));

        
    }

    MHT::addScanCount();
}

void MHT::addScanCount(){

    ++SCAN_K;
}

void MHT::test(){

}


}