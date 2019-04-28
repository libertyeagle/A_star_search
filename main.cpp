//
// Created by 吴永基 on 2019/4/27.
//

#include "maze.h"

int main(int argc, char **argv) {
    ifstream input_maze("../input.txt");
    Point entry = make_pair(1, 0);
    Point target = make_pair(16, 24);
    AStarSearch maze_search(input_maze, entry, target);
    maze_search.search();
    auto result = maze_search.construct_path();
    cout << result << endl;
}