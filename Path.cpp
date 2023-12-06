#include "Path.h"
#include <cmath>
#include <fstream>
#include <iostream>

Path::Path(TerrainMap& m, std::string name_in, Point start_in, Point finish_in)
    : map(m), name(name_in), start(start_in), finish(finish_in) {};

void Path::printStats() const {
    bool land = false;
    bool water = false;
    double length = 0.0;
    double alt = 0.0;
    int max_alt = map.alt(*path[0]);

    for (int i=1; i<path.size(); ++i) {
        Point u = *path[i];
        Point u_prev = *path[i-1];
        if (i < path.size() - 1 && map.alt(u) > 0) land = true;
        if (map.alt(u) < 0) water = true;
        length += (u - u_prev).length();
        alt += std::abs(map.alt(u) - map.alt(u_prev));
        if (map.alt(u) > max_alt) max_alt = map.alt(u);
    }

    if (land) std::cout << "Path from [" << start.x << ", " << start.y << "] to [" << finish.x << ", " << finish.y << "]" << std::endl;
    if (land) std::cout << "Path type: land" << std::endl;
    if (water) std::cout << "Path type: water" << std::endl;
    std::cout << "Path length: " << length << " km" << std::endl;
    std::cout << "Total elevation gain + loss: " << alt << " m" << std::endl;
    std::cout << "Max. elevation: " << max_alt << " m" << std::endl;
}

std::string Path::getName() const {
    return name;
}

void Path::saveToFile() const {
    std::ofstream output(name + ".dat");

    if (!output) throw std::runtime_error("Cannot open file " + name + ".dat");

    for (const Point* u : path) {
        output << u->x << " " << u->y << std::endl;
    }
}

void Path::setPointCost(const Point& p, Point& parent) {
    double z1 = map.alt(p);
    double z2 = map.alt(parent);
    int dx = p.x - parent.x;
    int dy = p.y - parent.y;
    double dz = z1 - z2;
    parent.cost = p.cost + costFunc(dx, dy, dz);
}

std::vector<Point> Path::getNeighbors(Point const& p) {
	std::vector<Point> neighbors;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
			if (i == 0 && j == 0) continue;
            int xi = p.x + i; int yj = p.y + j;
            if (!map.validCoords(xi, yj)) continue;
			double dz = map.alt(xi, yj) - map.alt(p);
            if (!isPointValid(xi, yj, dz)) continue;
			Point neighbor(xi,yj);
            setPointCost(p, neighbor);
			neighbors.push_back(neighbor);
		}
	}
	return neighbors;
}

void Path::reconstructPath(Point& current) {
    path.clear();
    int i = 0;
    while (current != start) {
        if (i++ % 1 == 0) {
			std::cout << "Current value: " << current.x << current.y << std::endl;
            while (true) {
				std::cout << "Press ENTER to continue..." << std::endl;
				if (std::cin.get() == '\n') break;
			}
        }
		path.push_back(&current);
		current = *came_from[current];
	}
    std::reverse(path.begin(), path.end());
}


