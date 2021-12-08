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

    vector<vector<int>> ind_sets;
    wgraph.bronKerbosh3(wgraph, ind_sets);

    auto mySum = [&wgraph] (vector<int>& set) -> float {
        float sum = 0;
        for(auto it:set) sum+=wgraph._weights[it];
        return sum;
    };

    float max_weight;
    for(int i = 0; i < ind_sets.size(); i++){
        auto curr_weight = mySum(ind_sets[i]);
        if(curr_weight > max_weight || result.size()==0){
            max_weight = curr_weight;
            result = ind_sets[i];
        }
    }
}

void weightedGraph::bronKerbosh3(weightedGraph& wgraph, vector<vector<int>>& result){

    auto &g = wgraph._complement;
    mySet P(wgraph._vertex.begin(), wgraph._vertex.end());
    mySet R, X;
    
    vector<int> order;
    wgraph.degeneracyOrder(g, order);
    for(int i=0; i<order.size(); i++){
        auto v = order[i];
        mySet neighbors;
        getNeighbors(v, g, neighbors);
        bronKerbosh2(R | mySet{v}, P & neighbors, X & neighbors, g, result);
        P = P - mySet{v};
        X = X | mySet{v};
    }
}

void weightedGraph::bronKerbosh2(const mySet& R, mySet P, mySet X, 
                                 const vector<vector<int>>& g, vector<vector<int>>& result){
    if(P.size()==0 && X.size()==0){
        result.emplace_back(vector<int>{R.begin(), R.end()});
    }
    else{
        mySet P_X = P | X;
        vector<int> random_id;
        mht_common::Random::getUniformRandoms(random_id, 0, P_X.size()-1, 1);

        auto iter = P_X.begin();
        mySet neighbors;
        for(int i = 0; i <= random_id[0]; i++){
            if(i == random_id[0]){
                getNeighbors(*iter, g, neighbors);
            }
            iter++;
        }

        mySet P_N = P - neighbors;
        for(auto v: P_N){
            getNeighbors(v, g, neighbors);
            bronKerbosh2(R | mySet{v}, P & neighbors, X & neighbors, g, result);
            P = P - mySet{v};
            X = X | mySet{v};
        }
    }

}

void weightedGraph::getNeighbors(const int& v, const vector<vector<int>>& g, mySet& n){

    n.clear();
    for(int i=0; i<g[v].size(); i++){
        if(g[v][i]) n.insert(i);
    }

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

mySet operator - (const mySet& a, const mySet& b){
    mySet result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

mySet operator & (const mySet& a, const mySet& b){
    mySet result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

mySet operator | (const mySet& a, const mySet& b){
    mySet result;
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

}