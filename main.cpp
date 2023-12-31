#include "TerrainMap.h"
#include "Path.h"
#include <vector>
#include <iostream>
#include <string>

#include "Letadlo.h"
#include "Lod.h"

int main() {
    TerrainMap m(256, 256,"terrain.dat");
    Point start(198, 205);
    Point finish(78, 17);

    std::vector<Path*> paths = { 
        new Letadlo(m, "Letadlo", start, finish),
        new Lod(m, "Lod", start, finish)
    };

    for (auto& p : paths) {
        std::cout << "Path search: " << p->getName() << std::endl;
        std::cout << "=============" << std::endl;
        p->find();
        p->printStats();
        std::cout << "=============" << std::endl;
        p->saveToFile();
        delete p;
    }

    return 0;
}
