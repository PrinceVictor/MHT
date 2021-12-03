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
    int last_track_num = _track_tree.size();

    for(int i = 0; i < meas.size(); i++){
        
        LOG_INFO("meas id:{} \tpos x:{:.2f}, y:{:.2f}", i, meas[i](0), meas[i](1));

        if(last_track_num){

        }
        _track_tree.emplace_back(std::make_shared<TrackTree>(SCAN_K, meas[i]));
        
    }

    MHT::addScanCount();
}

void MHT::addScanCount(){

    ++SCAN_K;
}

void MHT::test(){

}


}