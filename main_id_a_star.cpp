//
// Created by libertyeagle on 2019/4/30.
//

#include "maze.hpp"
#include <fstream>

int main(int argc, char **argv) {
    ifstream input_maze("input.txt");
    Point entry = make_pair(1, 0);
    Point target = make_pair(16, 24);
    IDAStarSearch maze_search(input_maze, entry, target);
    maze_search.search();
    auto result = maze_search.construct_path();
    ofstream ofs("output_IDA.txt");
    ofs << static_cast<double>(maze_search.search_duration.count()) * 1.e-6 << endl;
    ofs << result << endl;
    ofs << result.size() << endl;
    cout << "#search steps: " << maze_search.num_nodes << endl;
}