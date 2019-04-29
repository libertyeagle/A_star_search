//
// Created by 吴永基 on 2019/4/28.
//
#include "maze.hpp"

Search::Search(ifstream &ifs, const Point &maze_entry, const Point &maze_target) : maze(ifs), entry(maze_entry),
                                                                                   target(maze_target) {}

string Search::construct_path() {
    string path;
    for (auto p = final; p->parent != nullptr; p = p->parent) {
        auto parent = p->parent;
        int delta_x = p->x - parent->x;
        int delta_y = p->y - parent->y;
        if (delta_x == 0 and delta_y == 1) path.push_back('R');
        else if (delta_x == 0 and delta_y == -1) path.push_back('L');
        else if (delta_x == 1 and delta_y == 0) path.push_back('D');
        else path.push_back('U');
    }
    reverse(path.begin(), path.end());
    return path;
}

void Search::search() {
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    maze_search();
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    search_duration = chrono::duration_cast<chrono::microseconds>(t2 - t1);
}