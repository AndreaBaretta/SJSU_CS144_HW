#include "hw6.sea.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

// 2. (a) [2 points]
// Initialize INIT_NUM_FISH number of fish in random cells.
Sea::Sea() {
    for (int i = 0; i < INIT_NUM_FISH; ++i) {
        int cell_index_x = (int)(((double)rand() / RAND_MAX)*SIZE);
        if (cell_index_x == SIZE) {
            cell_index_x -= 1;
        }
        int cell_index_y = (int)(((double)rand() / RAND_MAX)*SIZE);
        if (cell_index_y == SIZE) {
            cell_index_y -= 1;
        }
        cells[cell_index_x][cell_index_y].push_back(new Fish());
    }
}

// (b) [8 points]
// For each fish in the sea, call Grow(), then call Reproduce() even if
// after Grow() fish is no longer alive.
// If Reproduce() returns a new fish, add it to the vector for that cell.
// Then move the fish to an adjacent cell (no diagonal) at random.
// Note that in the same simulation step, this same fish should not be
// processed again.
// If the random direction chosen goes outside the sea, then remove this
// fish from the sea, and deallocate memory.
// If fish is no longer alive, remove from vector, and deallocate memory.
void Sea::SimulateOneStep() {
    temp_cells = new std::vector<Fish*>[SIZE][SIZE];
    for (int cell_index_x = 0; cell_index_x < SIZE; ++cell_index_x) {
        for (int cell_index_y = 0; cell_index_y < SIZE; ++cell_index_y) {
            temp_cells[cell_index_x][cell_index_y] = std::vector<Fish*>();
        }
    }

    for (int cell_index_x = 0; cell_index_x < SIZE; ++cell_index_x) {
        for (int cell_index_y = 0; cell_index_y < SIZE; ++cell_index_y) {
            for (int i = 0; i < cells[cell_index_x][cell_index_y].size(); ++i) {
                Fish* fish = cells[cell_index_x][cell_index_y][i];
                fish->Grow();
                Fish* new_fish = fish->Reproduce();
                if (new_fish != nullptr) {
                    temp_cells[cell_index_x][cell_index_y].push_back(new_fish);
                }

            }
        }
    }
}