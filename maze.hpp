//
// Created by libertyeagle on 2019/4/26.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <utility>
#include <chrono>
#include <fstream>

#define MAZE_ROWS 18
#define MAZE_COLS 25
#define ASTAR_METHOD "L2"

using namespace std;
typedef pair<int, int> Point;

struct Node {
    Node(shared_ptr<Node> node_parent, int xx, int yy, double node_value, double node_cost)
            : parent(move(node_parent)), x(xx), y(yy), cont_value(node_value), cont_cost(node_cost) {}

    Node(shared_ptr<Node> node_parent, int xx, int yy, int node_value, int node_cost)
            : parent(move(node_parent)), x(xx), y(yy), disc_value(node_value), disc_cost(node_cost) {}

    shared_ptr<Node> parent;
    int x;
    int y;
    union {
        double cont_value;
        int disc_value;
    };
    union {
        double cont_cost;
        int disc_cost;
    };
};

struct PointHash {
    inline std::size_t operator()(const Point &v) const {
        return v.first * 31 + v.second;
    }
};

struct ContNodePtrCmp {
    inline bool operator()(const shared_ptr<Node> &a, const shared_ptr<Node> &b) {
        return a->cont_value > b->cont_value;
    }
};

class Maze {
public:
    explicit Maze(ifstream &ifs);

    bool is_valid_coordinate(int x, int y);

private:
    unordered_set<Point, PointHash> obstacles;
    int rows;
    int cols;
};

class Search {
public:
    explicit Search(ifstream &ifs, const Point &maze_entry, const Point &maze_target);
    void search();
    string construct_path();

    chrono::microseconds search_duration;

    int num_nodes;

protected:
    virtual void maze_search() = 0;
    shared_ptr<Node> final;
    Maze maze;
    Point entry;
    Point target;
    vector<shared_ptr<Node>> visited;
    unordered_set<Point, PointHash> visited_points;
};

class AStarSearch : public Search {
public:
    explicit AStarSearch(ifstream &ifs, const Point &maze_entry, const Point &maze_target);

    void maze_search() override;

private:
    void extend_frontier(shared_ptr<Node> node);

    double get_evaluation(int x, int y, double cost);

    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, ContNodePtrCmp> queue;
};

class IDAStarSearch : public Search {
public:
    explicit IDAStarSearch(ifstream &ifs, const Point &maze_entry, const Point &maze_target);

    void maze_search() override;

private:
    void extend_frontier(shared_ptr<Node> node, int max_value);

    int get_evaluation(int x, int y, int cost);

    deque<shared_ptr<Node>> frontier;
};


#endif //MAZE_MAZE_H
