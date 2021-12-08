// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/07
// Author: Hongbin Zhou

#include "graph/graph.h"

namespace mht_graph {

Graph::Graph(){}

Graph::~Graph(){}

void Graph::addVertex(const int& vertex){
    
    _vertex.emplace_back(vertex);
}

void Graph::setEdges(const vector<vector<int>>& edges){

    _edges = edges;
}

void Graph::calComplementGraph(){

    int n = _vertex.size();
    
    _complement.resize(n, vector<int>(n, 1));
    for(int i = 0; i < n; i++) _complement[i][i] = 0;

    for(int i = 0; i < _edges.size(); i++){
        auto& edge = _edges[i];
        _complement[edge[0]][edge[1]] = 0;
        _complement[edge[1]][edge[0]] = 0;
    }
}

void Graph::calVertexDegrees(const vector<vector<int>>& g, vector<pair<int, int>>& degrees){

    degrees.resize(g.size());
    for(int i=0; i<g.size(); i++){
        int sum=0;
        for(auto it:g[i]){
            sum += it;
        }
        degrees[i].first = i;
        degrees[i].second = sum;
    }
}
}