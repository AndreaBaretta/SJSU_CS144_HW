#include "hw6.fish.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

// 1. (a) [1 point]
// Initialize the private member variables to the values
// in the comments next to the variables.
Fish::Fish() : reproduce_probability(0.4), growth_rate(0.2), size(1), age(0), alive(true) {}

// (b) [2 points]
// Increment age. Increase size by growth_rate times current size.
// Then set growth rate to 0.8 of the current growth rate.
// If age is greater than 3, set alive to false with a probability of 0.8.
void Fish::Grow() {
    size += size*growth_rate;
    growth_rate *= 0.8;
    if (age > 3) {
        if ((double)rand() / RAND_MAX <= 0.8) {
            alive = false;
        }
    }
}

// (c) [3 points]
// Reproduce with the probability given by reproduce_probability.
// If decide to reproduce, return pointer to new Fish.
// Otherwise, return null pointer.
Fish* Fish::Reproduce() {
    if ((double)rand() / RAND_MAX <= reproduce_probability) {
        return new Fish();
    } else {
        return nullptr;
    }
}

// (d) [1 point]
// Returns true if fish is alive, false otherwise.
bool Fish::IsAlive() {
    return alive;
}
// (e) [1 point]
// Print the vital stats (size and age) of the fish.
void Fish::Print() {
    cout << "Age: " << age << " Size: " << size << endl; 
}