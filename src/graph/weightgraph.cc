// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/07
// Author: Hongbin Zhou

#include "graph/weightgraph.h"

namespace mht_graph {

weightedGraph::weightedGraph(){}

weightedGraph::~weightedGraph(){}

void weightedGraph::addWeightedVertex(const int& vertex, const float& weight){

    addVertex(vertex);
    _weights[vertex] = weight;
}

void weightedGraph::getMWIS(weightedGraph& wgraph, vector<int>& result){

    wgraph.calComplementGraph();

    result.clear();
    wgraph.bronKerbosh3(wgraph, result);

}

void weightedGraph::bronKerbosh3(weightedGraph& wgraph, vector<int>& result){

    auto &g = wgraph._complement;
    set<int> P(wgraph._vertex.begin(), wgraph._vertex.end());
    set<int> R, X;
    
    vector<int> order;
    wgraph.degeneracyOrder(g, order);
    for(int i=0; i<order.size(); i++){
        auto v = order[i];
        set<int> neighbors;
        getNeighbors(v, g, neighbors);
        bronKerbosh2(R | set<int>{v}, P & neighbors, X & neighbors, g, result);
        P = P - set<int>{v};
        X = X | set<int>{v};
    }
}

void weightedGraph::bronKerbosh2(const set<int>& R, set<int> P, set<int> X, 
                                 const vector<vector<int>>& g, vector<int>& result){
    if(P.size()==0 && X.size()==0){
        std::copy(R.begin(), R.end(), std::back_inserter(result));
    }
    else{
        set<int> temp = P | X;
        vector<int> random_id;
        mht_common::Random::getUniformRandoms(random_id, 0, temp.size()-1, 1);

        vector<int> n_temp(temp.begin(), temp.end());
        auto random_v = n_temp[random_id[0]];
        set<int> neighbors;
        getNeighbors(random_v, g, neighbors);

        auto temp_P = P - neighbors;
        for(auto v:temp_P){
            getNeighbors(v, g, neighbors);
            bronKerbosh2(R | set<int>{v}, P & neighbors, X & neighbors, g, result);
            P = P - set<int>{v};
            X = X | set<int>{v};
        }
    }

}

void weightedGraph::getNeighbors(const int& v, const vector<vector<int>>& g, set<int>& n){

    vector<int> neighbors;
    for(int i=0; i<g[v].size(); i++){
        if(g[v][i]) neighbors.emplace_back(i);
    }
    n = set<int>(neighbors.begin(), neighbors.end());

}

void weightedGraph::degeneracyOrder(const vector<vector<int>>& g, vector<int>& order){

    vector<pair<int, int>> vertex_deg;
    calVertexDegrees(g, vertex_deg);
    auto cmp = [](pair<int, int>&a, pair<int, int>&b) -> bool {
        if(a.second < b.second) return true;
        else if(a.second > b.second) return false;
        else {
            return a.first <= b.first;
        }
    };
    sort(vertex_deg.begin(), vertex_deg.end(), cmp);
    
    order.resize(vertex_deg.size());
    for(int i=order.size()-1; i>=0; i--){
        order[i] = vertex_deg[order.size()-i-1].first;
    }
}

set<int> operator-(const set<int>& a, const set<int>& b){
    set<int> result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), 
                        std::inserter(result, result.begin()));
    return result;
}

set<int> operator & (const set<int>& a, const set<int>& b){
    set<int> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), 
                          std::inserter(result, result.begin()));
    return result;
}

set<int> operator | (const set<int>& a, const set<int>& b){
    set<int> result;
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), 
                   std::inserter(result, result.begin()));
    return result;
}
}