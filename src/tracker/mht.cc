// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "tracker/mht.h"

namespace mht_tracker {

MHT::MHT(){

    LOG_INFO("Construct Multiple Hypothesis Tracker");
}

MHT::MHT(const string& param_path):_params(param_path){

    LOG_INFO("Construct Multiple Hypothesis Tracker");
}

MHT::~MHT(){

}

void MHT::run(const float& t, const vector<Eigen::VectorXf>& meas){

    LOG_INFO("run MHT! t:{:.1f}s\tmeas size:{}", t, meas.size());

    for(int i = 0; i < meas.size(); i++){
        
    }
}

void MHT::test(){

    _track_tree = make_shared<TrackTree>();
    {
        auto child1 = make_shared<TrackTree>(_track_tree);
        _track_tree->_children.push_back(child1);
        {
            auto child2 = make_shared<TrackTree>(child1);
            child1->_children.push_back(child2);
        }
    }
    _track_tree.reset();
    
}


}