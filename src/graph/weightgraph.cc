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

void weightedGraph::getMWIS(weightedGraph& wgraph, vector<int>& optimals){

    wgraph.calComplementGraph();

    optimals.clear();
    wgraph.bronKerbosh3(wgraph);

}

void weightedGraph::bronKerbosh3(weightedGraph& wgraph){

    set<int> P(wgraph._vertex.begin(), wgraph._vertex.end());
    set<int> R, X;

    vector<int> order;
    wgraph.degeneracyOrder(wgraph, order);
    for(int i=0; i<order.size(); i++){
        
    }

}

void weightedGraph::degeneracyOrder(weightedGraph& wgraph, vector<int>& order){

    vector<pair<int, int>> vertex_deg;
    wgraph.calVertexDegrees(vertex_deg);
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
}