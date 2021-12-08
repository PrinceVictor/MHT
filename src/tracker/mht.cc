// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "tracker/mht.h"

namespace mht_tracker {

int MHT::SCAN_K = 1;

MHT::MHT(){

    LOG_INFO("Construct Multiple Hypothesis Tracker");
}

MHT::MHT(const string& param_path):_params(param_path){

    LOG_INFO("Construct Multiple Hypothesis Tracker");
}

MHT::~MHT(){

    LOG_INFO("Destroy Multiple Hypothesis Tracker");
}

void MHT::run(const float& t, const vector<Eigen::VectorXf>& meas){
    
    #ifdef USE_DEBUG
        printf("\n");
    #endif
    LOG_INFO("run MHT! t:{:.1f}s\tmeas size:{}", t, meas.size());  
    
    vector<MyTrack> leaves;
    for(int i = 0; i < _track_trees.size(); i++){
        TrackTree::getLeaves(_track_trees[i], leaves, MHT::SCAN_K-1);
    }

    int last_tracks_num = leaves.size();
    LOG_INFO("last_tracks_num {}", last_tracks_num);

    //prediction
    for(int i = 0; i < last_tracks_num; i++){
        leaves[i]->predict();
    }

    //update without detection
    for(int i = 0; i < last_tracks_num; i++){
        leaves[i]->update(MISS_DETECTION, leaves[i]);
    }

    for(int i = 0; i < meas.size(); i++){
        
        LOG_INFO("meas id:{}  pos x:{:.2f}, y:{:.2f}", i+1, meas[i](0), meas[i](1));

        //update with detection
        if(last_tracks_num){
            for(int j = 0; j < last_tracks_num; j++){
                leaves[j]->update(ASSCIATED_TRACK, leaves[j], i+1, meas[i]);
            }
        #ifdef USE_DEBUG
            printf("\n\n");
        #endif
        }
        
        //create new tracks
        _track_trees.emplace_back(make_shared<TrackTree>(NEW_TRACK, SCAN_K, i+1, meas[i], _params));
    }

    leaves.clear();
    for(int i = 0; i < _track_trees.size(); i++){
        TrackTree::getLeaves(_track_trees[i], leaves, MHT::SCAN_K);
    }
    
    LOG_INFO("current hypothesis size {}", leaves.size());
    
    vector<vector<int>> conflict_hypo_ids;
    TrackTree::getConflictHypos(leaves, conflict_hypo_ids, _params._N_SCAN);

    mht_graph::weightedGraph weighted_graph;
    int curr_hypos_size = leaves.size();
    for(int i = 0; i < curr_hypos_size; i++){
        // #ifdef USE_DEBUG
        //     LOG_INFO("Hypo ID: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
        //              i, leaves[i]->_track_id, fmt::join(leaves[i]->_track_history, " -> "), leaves[i]->_target->getTrackScore());
        // #endif

        auto& target = leaves[i]->_target;
        weighted_graph.addWeightedVertex(i, target->getTrackScore());
    }
    weighted_graph.setEdges(conflict_hypo_ids);
    
    vector<int> best_hypos_ids;
    weighted_graph.getMWIS(weighted_graph, best_hypos_ids);
    #ifdef USE_DEBUG
        printf("\n");
        LOG_INFO("Best Hypo size {}", best_hypos_ids.size());
    #endif
    LOG_INFO("Best Hypo size {}", best_hypos_ids.size());
    vector<MyTrack> best_hypos(best_hypos_ids.size());
    for(int i = 0; i < best_hypos.size(); i++){
        best_hypos[i] = leaves[best_hypos_ids[i]];
        #ifdef USE_DEBUG
            LOG_INFO("Best Hypo ID: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
                     best_hypos_ids[i], best_hypos[i]->_track_id, fmt::join(best_hypos[i]->_track_history, " -> "), best_hypos[i]->_target->getTrackScore());
        #endif
    }
    leaves.clear();
    #ifdef USE_DEBUG
        printf("\n");
    #endif
    TrackTree::showTrackTrees(_track_trees);

    #ifdef USE_DEBUG
        printf("\n");
    #endif
    int purn_scan = MHT::SCAN_K - _params._N_SCAN;
    TrackTree::deleteTrees(_track_trees, best_hypos, purn_scan);

    
    #ifdef USE_DEBUG
        printf("\n");
    #endif
    TrackTree::showTrackTrees(_track_trees);


    MHT::addScanCount();
}

void MHT::addScanCount(){

    ++SCAN_K;
}

void MHT::test(){

}


}