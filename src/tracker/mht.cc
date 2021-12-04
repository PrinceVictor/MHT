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
    
    vector<MyTrack> leaves;
    for(int i = 0; i < _track_trees.size(); i++){
        TrackTree::getLeaves(_track_trees[i], leaves, MHT::SCAN_K-1);
    }
    for(int i = 0; i < leaves.size(); i++){
        leaves[i]->predict();
    }

    int last_tracks_num = leaves.size();

    for(int i = 0; i < meas.size(); i++){
        
        LOG_INFO("meas id:{} \tpos x:{:.2f}, y:{:.2f}", i, meas[i](0), meas[i](1));

        if(last_tracks_num){
            for(int j = 0; j < last_tracks_num; j++){
                leaves[i]->update(meas[i]);
            }
        }
        
        
        // _track_trees.emplace_back(std::make_shared<TrackTree>(NEW_TRACK, i+1, SCAN_K,
        //                                                       p_d, p_fa, p_n, _d_gate,
        //                                                       _track_score_conf_thre, _track_score_conf_thre,
        //                                                       meas[i], r, p, q, delta_t));

        
    }

    MHT::addScanCount();
}

void MHT::addScanCount(){

    ++SCAN_K;
}

void MHT::test(){

}


}