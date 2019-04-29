//
// Created by 吴永基 on 2019/4/26.
//

#include "maze.hpp"

Maze::Maze(ifstream &ifs) : rows(MAZE_ROWS), cols(MAZE_COLS) {
    int status;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            ifs >> status;
            if (status) obstacles.insert(make_pair(i, j));
        }
}

bool Maze::is_valid_coordinate(int x, int y) {
    if ((x < 0) or (x >= rows) or (y < 0) or (y >= cols)) return false;
    Point coord = make_pair(x, y);
    if (obstacles.find(coord) == obstacles.end()) return true;
    else return false;
}
