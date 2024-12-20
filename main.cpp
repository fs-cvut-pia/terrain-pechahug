#include "TerrainMap.h"
#include "Path.h"
#include "Letadlo.h"
#include "Lod.h"
#include <vector>
#include <iostream>
#include <string>

Point read_coordinates(int argc, char *argv[], int i_option) {
    Point p;

    if (argc > i_option+1) {
        p.x = std::atoi(argv[i_option]); 
        p.y = std::atoi(argv[i_option + 1]);
    } else {
        throw std::runtime_error("Coordinates incorrectly specified!");
    }

    return p;
}

int main(int argc, char *argv[]) {
    const int nx = 256;
    const int ny = 256;

    std::string terrain_filename;

    // Load the terrain map
    if (argc > 1) {
        terrain_filename = argv[1];
    } else {
        std::cout << "No terrain file specified!" << std::endl;
        return 0;
    }

    TerrainMap m(nx, ny, terrain_filename);

    // Load the coordinates of the start and end points
    Point start = read_coordinates(argc, argv, 2);
    Point finish = read_coordinates(argc, argv, 4);

    std::vector<Path*> paths = {
        new Letadlo(m, start, finish),
        new Lod(m, start, finish)
    };

    for (auto& p : paths) {
        std::cout << "Path search: " << p->getName() << std::endl;
        std::cout << "=============" << std::endl;
        if (p->find()) {
            p->printStats();
            p->saveToFile();
        } else {
            std::cout << "No valid path found for " << p->getName() << "!" << std::endl;
        }
        std::cout << "=============" << std::endl;
        delete p;
    }

    return 0;
}
