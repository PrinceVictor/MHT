// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/02
// Author: Hongbin Zhou

#include "tracker/tracktree.h"

namespace mht_tracker {

uint TrackTree::TRACK_ID_COUNT = 1;

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
        _track_history.resize(_scan_k, 0);
        _track_history.back() = _detection_id;
        _target = make_shared<Target>(meas, r, p, d_gate, q, delta_t);
        _target->initTrackScore(p_d, track_score_del_thres, track_score_conf_thre, 
                                p_fa, p_n, volume);


        TrackTree::trackCount();
    }
}

TrackTree::TrackTree(const int flag, MyTrack& parent, const int& detect_id, const Eigen::VectorXf& meas){
    
    _parent = parent;
    _target = std::make_shared<Target>(*parent->_target);
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

    #ifdef USE_DEBUG
        LOG_INFO("Scan: {} Track ID: {}, histories: {}, Hypo score: {:.3f}",
                 _scan_k, _track_id, fmt::join(_track_history, " -> "), _target->getTrackScore());
    #endif
}

void TrackTree::predict(){

    _target->predict();

    #ifdef USE_DEBUG
        LOG_INFO("Track id {} X_state x: {:.3f} y: {:.3f}", _track_id, _target->_X_pre(0), _target->_X_pre(1));
    #endif
}

void TrackTree::update(const int flag, MyTrack& parent, const int& detect_id, const Eigen::VectorXf& meas){

    _children.emplace_back(make_shared<TrackTree>(flag, parent, detect_id, meas));

}

void TrackTree::trackCount(){
    
    TrackTree::TRACK_ID_COUNT++;
}

void TrackTree::getLeaves(const MyTrack& root, vector<MyTrack>& result, const int& dim){

    if(root->_scan_k == dim){
        result.emplace_back(root);
        return;
    }
    
    for(int i=0; i<root->_children.size(); i++){
        getLeaves(root->_children[i], result, dim);
    }
}

void TrackTree::getConflictHypos(const vector<MyTrack>& hypos, vector<vector<int>>& conflict_ids, const int& N_scan){

    LOG_INFO("Get Conflict Hypothesis IDs!");

    int hypos_size = hypos.size();
    for(int i=0; i<hypos_size-1; i++){
        for(int j=1; j<hypos_size; j++){
            if(hypos[i]->_track_id == hypos[j]->_track_id){
                conflict_ids.emplace_back(vector<int>{i, j});
            }
            else{
                auto& left = hypos[i]->_track_history;
                auto& right = hypos[j]->_track_history;
                
                int k = std::max((int)(left.size()-N_scan-1), 0);
                for(; k<left.size(); k++){
                    if(left[k] != 0 && right[k] != 0 && left[k] == right[k]){
                        conflict_ids.emplace_back(vector<int>{i, j});
                        break;
                    }
                }
            }
        }
    }
}

void TrackTree::deleteConflictTrees(vector<MyTrack>& root, const vector<MyTrack>& best_hypos, const int& purn_scan){

    if(purn_scan <1) return;
    // vector<MyTrack> purn_scan_trees;
    // for(auto it: root) getLeaves(it, purn_scan_trees, purn_scan);
    LOG_INFO("Purn the Trees in SCAN: {}", purn_scan);

    for(int i=0; i<best_hypos.size(); i++){
        int detect_id = best_hypos[i]->_track_history[purn_scan-1];
        #ifdef USE_DEBUG
            LOG_INFO("Keep Hypo Scan: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
                     best_hypos[i]->_scan_k, best_hypos[i]->_track_id, fmt::join(best_hypos[i]->_track_history, " -> "), best_hypos[i]->_target->getTrackScore());
        #endif

        for(int j=0; j<root.size();){    

            if(root[j]->_scan_k > purn_scan) {
                j++; continue;
            }
            else if(best_hypos[i]->_track_id == root[j]->_track_id){
                #ifdef USE_DEBUG
                    LOG_INFO("To Delete Scan: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
                    root[j]->_scan_k, root[j]->_track_id, fmt::join(root[j]->_track_history, " -> "), root[j]->_target->getTrackScore());
                #endif
                auto& root_children = root[j]->_children;
                for(int k=0; k<root_children.size(); k++){
                    if(root_children[k]==getParent(best_hypos[i], purn_scan+1)){
                        root[j] = root_children[k];
                    }
                }
            }
            else if(detect_id == root[j]->_track_history[purn_scan-1]){
                #ifdef USE_DEBUG
                    LOG_INFO("To Delete Scan: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
                    root[j]->_scan_k, root[j]->_track_id, fmt::join(root[j]->_track_history, " -> "), root[j]->_target->getTrackScore());
                #endif
                
                root.erase(root.begin()+j);
                continue;
            }
            j++;
        }
    }

    for(int i=0; i<root.size(); ){
        if(root[i]->_scan_k == purn_scan){
            #ifdef USE_DEBUG
                LOG_INFO("Delete Old Hypo Scan: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
                        root[i]->_scan_k, root[i]->_track_id, fmt::join(root[i]->_track_history, " -> "), root[i]->_target->getTrackScore());
            #endif
            root.erase(root.begin()+i);
        }
        else i++;
    }
}

void TrackTree::deleteDeadTrees(vector<MyTrack>& roots){
    for(int i=0; i<roots.size();){
        if(roots[i]->_target->isDead()){

            #ifdef USE_DEBUG
                LOG_INFO("Delete Dead Hypo Scan: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
                          roots[i]->_scan_k, roots[i]->_track_id, fmt::join(roots[i]->_track_history, " -> "), roots[i]->_target->getTrackScore());
            #endif
            roots.erase(roots.begin()+i);
        }
        else{
            deleteDeadTrees(roots[i]->_children);
            i++;
        }
    }

}

MyTrack TrackTree::getParent(MyTrack child, const int& scan_k){

    while(child && child->_scan_k != scan_k){
        child = child->_parent.lock();
    }
    return child;
}

void TrackTree::showTrackTrees(const vector<MyTrack>& trees){
    
    for(auto tree : trees){
        #ifdef USE_DEBUG
            LOG_INFO("Scan: {} track ID: {}, histories: {}, Hypo score: {:.3f}",
                      tree->_scan_k, tree->_track_id, fmt::join(tree->_track_history, " -> "), tree->_target->getTrackScore());
        #endif
        showTrackTrees(tree->_children);
    }
}

}