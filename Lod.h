#pragma once
#include "Path.h"

class Lod : public Path {
public:
    Lod(TerrainMap& m, std::string name_in, Point start_in, Point finish_in);
    bool find() override;
    double costFunc(int dx, int dy, double dz) const override;
    bool isPointValid(int x, int y, double dz) const override;
};
