#include <iostream>
#include <map>
#include "MyPath.h"
#include "TerrainMap.h"


MyPath::MyPath(TerrainMap& m, std::string name_in, Point start_in, Point finish_in)
    : Path(m, name_in, start_in, finish_in) {}

double MyPath::costFunc(int dx, int dy, double dz) const {
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

bool MyPath::isPointValid(int x, int y, double dz) const {
	return true;
}

bool MyPath::find() {
    came_from[start] = nullptr;
    cost_so_far[start] = start.cost;
    frontier.push(start);

    int i = 0;
    while (!frontier.empty()) {

        Point current = frontier.top();
        frontier.pop();

        if (current == finish) {
            std::cout << "Goal found!" << std::endl;
            reconstructPath(current);  
            std::cout << "Path reconstructed!" << std::endl;
            return true;
        }

        std::vector<Point> neighbors = getNeighbors(current);
        for (Point neighbor : neighbors ) {
            if (cost_so_far.find(neighbor) == cost_so_far.end() || neighbor.cost < cost_so_far[neighbor]) {
                cost_so_far[neighbor] = neighbor.cost;
				came_from[neighbor] = &current;
                frontier.push(neighbor);
            }
        }
    }
    return false;
}

