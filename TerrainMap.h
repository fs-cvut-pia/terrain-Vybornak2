#pragma once

#include <cmath>
#include <vector>
#include <string>

struct Point {
	Point() : x(0), y(0), cost(0.0) {}
    Point(int x, int y, double cost = 0.0) : x(x), y(y), cost(cost) {}
    int x, y;
    double cost;

    constexpr static int nx_max = 10000;
    bool operator!= (Point const& v) const { return !(operator== (v)); };
    bool operator== (Point const& v) const { return x == v.x && y == v.y; };
    Point operator+ (Point const& v) const { return Point(x+v.x,y+v.y); };
    Point operator- (Point const& v) const { return Point(x-v.x,y-v.y); };
    bool operator<  (Point const& v) const { return x + y*nx_max < v.x + v.y*nx_max; };
    double length() const { return std::sqrt(x*x + y*y); };
};

template<typename T>
class Matrix {
public:
    Matrix(int n, int m) : nx(n), ny(m), data(n*m) {};
    void zero() { for (T& i : data) i = 0; };
    T operator() (int i, int j) const { return data[i+nx*j]; };
    T& operator() (int i, int j) { return data[i+nx*j]; };
    T operator() (Point const& ij) const { return data[ij.x+nx*ij.y]; };
    T& operator() (Point const& ij) { return data[ij.x+nx*ij.y]; };
    T flattened(int i) const { return data[i]; };
    T& flattened(int i) { return data[i]; };
private:
    int nx; int ny;
    std::vector<T> data;
};

class TerrainMap {
public:
    TerrainMap(int n, int m);                      
    TerrainMap(int n, int m, std::string filename); 

    int alt(int x, int y);                
    int alt(Point const& v);

    bool isWater(int x, int y) { return alt(x,y) < 0; } ;
    bool isLand(int x, int y) { return alt(x,y) > 0; } ;

    void outputStats();                
    bool validCoords(int x, int y) ;
    bool validCoords(Point const& p) ;
    const int nx; const int ny;
private:
    Matrix<int> altitude;
    Matrix<int> access_count;
};

