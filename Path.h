#pragma once
#include <queue>
#include "TerrainMap.h"
#include <map>

class Path {
public:
    Path(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);
    void printStats() const;    
    void saveToFile() const;
    std::string getName() const; 

	std::vector<Point> getNeighbors(Point const& p);
    void reconstructPath(Point& current);
    void setPointCost(Point const& p, Point& parent);
    struct Compare {
        bool operator()(Point const& p1, Point const& p2) {
			return p1.cost > p2.cost;
		}
	};


    virtual bool find() = 0;
    virtual double costFunc(int dx, int dy, double dz) const = 0;
    virtual bool isPointValid(int x, int y, double dz) const = 0;
protected:
    TerrainMap& map;
    std::priority_queue<Point, std::vector<Point>, Compare> frontier;
    std::map<Point, Point*> came_from;
    std::map<Point, double> cost_so_far;
    std::vector<Point*> path;
    const Point start; 
    const Point finish;
private:
    std::string name;
};

