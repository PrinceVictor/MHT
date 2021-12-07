// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_GRAPH_H
#define MHT_GRAPH_H

#include <vector>
#include <map>

#include "log/log.h"

namespace mht_graph {

using std::vector;
using std::map;

class Graph {

public:

    Graph();

    ~Graph();

    void addVertex(const int& vertex);

    void setEdges(const vector<vector<int>>& edges);

    void complementGraph();

public:

    vector<int> _vertex;

    vector<vector<int>> _edges;

};

}

#endif