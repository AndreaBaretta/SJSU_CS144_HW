#include <iostream>
#include <cstdlib>
#include "hw7.sea.hpp"

using namespace std;

Sea::Sea() {
    for (int i = 0; i < INIT_NUM_FISH; i++) {
        Fish* fptr = new Fish;
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        cells[x][y].push_back(fptr);
    }
    for (int i = 0; i < INIT_NUM_SHARK; i++) {
        Fish* fptr = new Shark;
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        cells[x][y].push_back(fptr);
    }
}

// For each fish in the sea, call Grow(),
// If the fish is still alive after Grow(), then call Eat(), and then Reproduce()
// If Reproduce() returns a new fish, add it to the vector for that cell.
// Then move the fish to an adjacent cell (no diagonal) at random.
// Note that in the same simulation step, this same fish should not be
// processed again.
// If the random direction chosen goes outside the sea, then remove this
// fish from the sea, and deallocate memory.
// If fish is no longer alive, remove from vector, and deallocate memory.
void Sea::SimulateOneStep() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp_cells[i][j].clear();
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
	    vector<Fish*> to_delete;
            for (Fish* fptr : cells[i][j]) {
                fptr->Grow();
		// Update: Don't delete yet, so that later Eat() will not
		// try to eat a deleted fish. Instead put in vector first,
		// and delete only after this for-loop is done.
                if (!fptr->IsAlive()) {
		    to_delete.push_back(fptr);
                    continue;
                }
                fptr->Eat(cells[i][j]);
                Fish* baby_fish = fptr->Reproduce();
                if (baby_fish != nullptr) {
                    temp_cells[i][j].push_back(baby_fish);
                }
                int ni = i;
                int nj = j;
                int move_dir = rand() % 4;
                switch(move_dir) {
                case 0:
                    ni++;
                    break;
                case 1:
                    ni--;
                    break;
                case 2:
                    nj++;
                    break;
                case 3:
                    nj--;
                    break;
                }
                if ((ni < 0) || (ni >= SIZE) ||
                    (nj < 0) || (nj >= SIZE)) {
		    to_delete.push_back(fptr);
                } else {
                    temp_cells[ni][nj].push_back(fptr);
                }
            }
	    for (Fish* fptr : to_delete) {
	        delete fptr;
	    }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cells[i][j].clear();
            cells[i][j] = temp_cells[i][j];
        }
    }
}

// For each cell print all the fish in the cell.
void Sea::Print() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!cells[i][j].empty()) {
                cout << i << ", " << j << ":" << endl;
                for (Fish* fptr : cells[i][j]) {
                    fptr->Print();
                }
            }
        }
    }

}

void Sea::PopulationCensus(int& nshark, int& nfish) {
    nshark = 0;
    nfish = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (Fish* fptr : cells[i][j]) {
	        // Update: Also check IsAlive() because fish eaten can still
	        // end up in temp_cells of adjacent node and thus copied into
	        // cells.
	        if (fptr->IsEdible() && fptr->IsAlive()) {
                    nfish++;
                } else if (!fptr->IsEdible()) {
                    nshark++;
                }
            }
        }
    }

}


