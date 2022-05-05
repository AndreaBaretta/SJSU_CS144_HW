#include <vector>
#include <string>
#include <iostream>
#include "hw9.ocean.hpp"

using namespace std;

// 2. (1 point)
// Start with one Sea with starting coordinates (0, 0).
// Populate this Sea with some fish.
// Assume top left corner is (0, 0). The y-coordinate increases downwards.
Ocean::Ocean() : seas() {
    seas.push_back(new Sea(0, 0, true));
}

// 3a. (6 points)
// First call SimulateOneStep() for all seas in the ocean.
// Then, if fish or shark moves outside of a sea, move into adjacent sea.
// If adjacent sea doesn't exist, make a new sea. Add sea to seas.
// Also make sure you set the sea's member variables (above, below etc.).
// Note: Sea above has smaller y-coordinate. y-coordinate is in cells[y][].
//       The y-coordinate is the row number.
// b. (2 points)
// Throw an exception when number of seas is greater than max_seas.
// Make sure you catch the exception in the main() function.
// c. (2 points)
// Make threads to run Sea::SimulateOneStep() in parallel.
// Use lambda expression.
// Make sure no race conditions.
// To use member variables in lambda expression, capture this.
void Ocean::SimulateOneStep() {
    for (Sea* sptr : seas) {
        sptr->SimulateOneStep();
    }
    for (Sea* sptr : seas) {
        for (int i = 0; i < SIZE; ++i) {
            if (!sptr->up_buffer[i].empty()) {
                if (sptr->above == nullptr) {
                    MakeAndConnectSea(sptr->startx, sptr->starty - SIZE);
                }
                for (Fish* fptr : sptr->up_buffer[i]) {
                    sptr->above->cells[SIZE - 1][i].push_back(fptr);
                }
            }
            if (!sptr->down_buffer[i].empty()) {
                if (sptr->below == nullptr) {
                    MakeAndConnectSea(sptr->startx, sptr->starty + SIZE);
                }
                for (Fish* fptr : sptr->down_buffer[i]) {
                    sptr->below->cells[0][i].push_back(fptr);
                }
            }
            if (!sptr->left_buffer[i].empty()) {
                if (sptr->left == nullptr) {
                    MakeAndConnectSea(sptr->startx - SIZE, sptr->starty);
                }
                for (Fish* fptr : sptr->left_buffer[i]) {
                    sptr->left->cells[i][SIZE].push_back(fptr);
                }
            }
            if (!sptr->right_buffer[i].empty()) {
                if (sptr->right == nullptr) {
                    MakeAndConnectSea(sptr->startx + SIZE, sptr->starty);
                }
                for (Fish* fptr : sptr->right_buffer[i]) {
                    sptr->right->cells[i][0].push_back(fptr);
                }
            }
        }
    }
    if (seas.size() > max_seas) {
        throw std::string("Max number of seas reached");
    }
}
// helper function
void Ocean::MakeAndConnectSea(int sx, int sy) {
    Sea* sptr = new Sea(sx, sy, false);
    for (int i = 0; i < seas.size(); ++i) {
        if (seas[i]->startx == sx + SIZE && seas[i]->starty == sy) {
            seas[i]->left = sptr;
            sptr->right = sptr;
        }
        if (seas[i]->startx == sx - SIZE && seas[i]->starty == sy) {
            seas[i]->right = sptr;
            sptr->left = sptr;
        }
        if (seas[i]->starty == sy + SIZE && seas[i]->startx == sx) {
            seas[i]->above = sptr;
            sptr->below = sptr;
        }
        if (seas[i]->starty == sy - SIZE && seas[i]->startx == sx) {
            seas[i]->below = sptr;
            sptr->above = sptr;
        }
    }
    seas.push_back(sptr);
}

// 4. (4 points)
// First, print the min and max x and y coordinates of the ocean.
// Then, print the matrix of the number of fish in each cell.
// If no sea exists, then print x for all the cells in the sea.
// If greater than 9 fish in the cell, print 'M'.
// Top left is (minx, miny).
void Ocean::Print() {
    for (Sea* sptr : seas) {
        // cout << "(" << sptr->startx << ", " << sptr->starty << ")" << endl;
        if (sptr->startx <= min_x) {
            min_x = sptr->startx;
        }
        if (sptr->startx + SIZE - 1 >= max_x) {
            max_x = sptr->startx + SIZE - 1;
        }
        if (sptr->starty <= min_y) {
            min_y = sptr->starty;
        }
        if (sptr->starty + SIZE - 1 >= max_y) {
            max_y = sptr->starty + SIZE - 1;
        }
    }
    cout << "min_x: " << min_x << endl;
    cout << "max_x: " << max_x << endl;
    cout << "min_y: " << min_y << endl;
    cout << "max_y: " << max_y << endl;
    cout << "num_seas: " << seas.size() << endl;
    
    const int range_x = max_x - min_x + 1;
    const int range_y = max_y - min_y + 1;
    char array[range_y][range_x];
    for (int i = 0; i < range_x; ++i) {
        for (int j = 0; j < range_y; ++j) {
            array[j][i] = 'x';
        }
    }
    for (Sea* sptr : seas) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                int n = sptr->cells[j][i].size();
                char val;
                if (n <= 9) {
                    val = '0' + n;
                } else {
                    val = 'M';
                }
                array[sptr->starty + j - min_y][sptr->startx + i - min_x] = val;
            }
        }
    }
    for (int j = 0; j < range_y; ++j) {
        for (int i = 0; i < range_x; ++i) {
            cout << array[j][i];
        }
        cout << endl;
    }
}

// 5a. (1 point)
// Find total number of fish and sharks in all seas.
// b. (2 points)
// Make threads to run in parallel. Make sure no race conditions.
// Use lambda expression.
// To use member variables in lambda expression, capture this.
void Ocean::PopulationCensus(int& nshark, int& nfish) {
    nshark = 0;
    nfish = 0;
    for (Sea* sptr : seas) {
        int nshark_sea = 0;
        int nfish_sea = 0;
        sptr->PopulationCensus(nshark_sea, nfish_sea);
        nshark += nshark_sea;
        nfish += nfish_sea;
    }
}