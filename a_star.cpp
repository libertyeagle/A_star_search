//
// Created by libertyeagle on 2019/4/28.
//

#include "maze.hpp"

AStarSearch::AStarSearch(ifstream &ifs, const Point &maze_entry, const Point &maze_target) : Search(ifs, maze_entry,
                                                                                                    maze_target) {}

void AStarSearch::maze_search() {
    auto p = make_shared<Node>(nullptr, entry.first, entry.second, get_evaluation(entry.first, entry.second, 0.), 0.);
    queue.push(p);
    while (not queue.empty()) {
        auto p = queue.top();
        queue.pop();
        if (visited_points.find(make_pair(p->x, p->y)) != visited_points.end()) continue;
        num_nodes += 1;
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
        auto new_cost = node->cont_cost + 1.;
        auto new_value = get_evaluation(new_x, new_y, new_cost);
        auto new_node = make_shared<Node>(node, new_x, new_y, new_value, new_cost);
        queue.emplace(make_shared<Node>(node, new_x, new_y, new_value, new_cost));
    }
}

double AStarSearch::get_evaluation(int x, int y, double cost) {
    if (ASTAR_METHOD == "L2")
        return cost + sqrt(((x - target.first) * (x - target.first)) + ((y - target.second) * (y - target.second)));
    else
        return cost + fabs(x - target.first) + fabs(y - target.second);
}
