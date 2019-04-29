//
// Created by libertyeagle on 2019/4/28.
//

#include "maze.hpp"

IDAStarSearch::IDAStarSearch(ifstream &ifs, const Point &maze_entry, const Point &maze_target) : Search(ifs, maze_entry,
                                                                                                        maze_target) {}

void IDAStarSearch::extend_frontier(shared_ptr<Node> node, int max_value) {
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
        auto new_cost = node->disc_cost + 1;
        auto new_value = get_evaluation(new_x, new_y, new_cost);
        if (new_value <= max_value) frontier.emplace_back(make_shared<Node>(node, new_x, new_y, new_value, new_cost));
    }
}

void IDAStarSearch::maze_search() {
    auto start = make_shared<Node>(nullptr, entry.first, entry.second, get_evaluation(entry.first, entry.second, 0), 0);
    frontier.push_back(start);
    bool found = false;
    for (int threshold = get_evaluation(entry.first, entry.second, 0);; ++threshold) {
        while (not frontier.empty()) {
            auto p = frontier.front();
            frontier.pop_front();
            if (visited_points.find(make_pair(p->x, p->y)) != visited_points.end()) continue;
            num_nodes += 1;
            if (p->x == target.first && p->y == target.second) {
                final = p;
                visited.push_back(p);
                visited_points.insert(make_pair(p->x, p->y));
                found = true;
                break;
            }
            extend_frontier(p, threshold);
            visited.push_back(p);
            visited_points.insert(make_pair(p->x, p->y));
        }
        if (found) break;
        frontier.clear();
        visited.clear();
        visited_points.clear();
    }
}

inline int IDAStarSearch::get_evaluation(int x, int y, int cost) {
    return cost + abs(x - target.first) + abs(y - target.second);
}