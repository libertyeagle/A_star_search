//
// Created by 吴永基 on 2019/4/28.
//

#include "maze.h"

AStarSearch::AStarSearch(ifstream &ifs, const Point &maze_entry, const Point &maze_target) :
        maze(ifs), entry(maze_entry), target(maze_target) {

}

void AStarSearch::search() {
    auto p = make_shared<Node>(nullptr, entry.first, entry.second, get_evaluation(entry.first, entry.second, 0.), 0.);
    queue.push(p);
    while (not queue.empty()) {
        auto p = queue.top();
        queue.pop();
        if (visited_points.find(make_pair(p->x, p->y)) != visited_points.end()) continue;
        if (p->x == target.first && p->y == target.second) {
            final = p;
            visited.push_back(p);
            visited_points.insert(make_pair(p->x, p->y));
            break;
        }
        extend_frontier(p);
        visited.push_back(p);
        visited_points.insert(make_pair(p->x, p->y));
    }
}

void AStarSearch::extend_frontier(shared_ptr<Node> node) {
    // right, left, down, up
    const int delta_xs[] = {0, 0, 1, -1};
    const int delta_ys[] = {1, -1, 0, 0};
    for (int i = 0; i < 4; ++i) {
        auto dx = delta_xs[i];
        auto dy = delta_ys[i];
        int new_x = node->x + dx;
        int new_y = node->y + dy;
        if (not maze.is_valid_coordinate(new_x, new_y)) continue;
        if (visited_points.find(make_pair(new_x, new_y)) != visited_points.end()) continue;
        auto new_cost = node->cost + 1.;
        auto new_value = get_evaluation(new_x, new_y, new_cost);
        auto new_node = make_shared<Node>(node, new_x, new_y, new_value, new_cost);
        queue.push(new_node);
    }
}

double AStarSearch::get_evaluation(int x, int y, double cost) {
    if (METHOD == "L2")
        return cost + sqrt(((x - target.first) * (x - target.first)) + ((y - target.second) * (y - target.second)));
    else
        return cost + fabs(x - target.first) + fabs(y - target.second);
}

string AStarSearch::construct_path() {
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

