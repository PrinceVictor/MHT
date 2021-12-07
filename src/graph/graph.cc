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

void Graph::complementGraph();

}