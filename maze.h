//
// Created by 吴永基 on 2019/4/26.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <iostream>
#include <memory>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <utility>
#include <fstream>

#define MAZE_ROWS 18
#define MAZE_COLS 25
#define METHOD "L2"

using namespace std;
typedef pair<int, int> Point;

struct Node {
    Node(shared_ptr<Node> node_parent, int xx, int yy, double node_value, double node_cost)
            : parent(move(node_parent)), x(xx), y(yy), value(node_value), cost(node_cost) {}

    shared_ptr<Node> parent;
    int x;
    int y;
    double value;
    double cost;
};

struct PointHash {
    inline std::size_t operator()(const Point &v) const {
        return v.first * 31 + v.second;
    }
};

struct NodePtrCmp {
    inline bool operator()(const shared_ptr<Node> &a, const shared_ptr<Node> &b) {
        return a->value > b->value;
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

class AStarSearch {
public:
    explicit AStarSearch(ifstream &ifs, const Point &maze_entry, const Point &maze_target);

    void search();

    string construct_path();

private:
    void extend_frontier(shared_ptr<Node> node);

    double get_evaluation(int x, int y, double cost);

    shared_ptr<Node> final;
    Maze maze;
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, NodePtrCmp> queue;
    vector<shared_ptr<Node>> visited;
    unordered_set<Point, PointHash> visited_points;
    Point entry;
    Point target;
};

#endif //MAZE_MAZE_H
