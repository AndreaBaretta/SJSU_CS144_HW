#include "hw7.fish.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Fish::Fish() {
    reproduce_probability = 0.2;  // Initialized to 0.2
    growth_rate = 0.2;            // Initialized to 0.2
    size = 1;                     // Initialized to 1
    age = 0;                      // Initialized to 0
    alive = true;                 // Initialized to true
    edible = true;
}

// Increment age. Increase size by growth_rate.
// Then set growth rate to 0.8 of the current growth rate.
// If age is greater than 3, set alive to false with a probability of 0.8.
void Fish::Grow() {
    size += growth_rate * size;
    growth_rate *= 0.8;
    age++;
    if (age > 3) {
        int i = rand() % 1000;
        if (i < 800)
            alive = false;
    }
}

// Reproduce with the probability given by reproduce_probability x (age - 2).
// If decide to reproduce, return pointer to new Fish.
// Otherwise, return null pointer.
Fish* Fish::Reproduce() {
    float threshold =
        static_cast<float>(age - 2) * reproduce_probability * 1000.0;
    float f = static_cast<float>(rand() % 1000);
    if (f < threshold) {
        return new Fish;
    } else {
        return nullptr;
    }
}

// Print the vital stats of the fish.
void Fish::Print() {
    cout << "Age: " << age << " Size: " << size << endl;
}

// (1 point)
// Write a getter function to return the value of member variable alive.
bool Fish::IsAlive() {
    return alive;
}

// (1 point) Set alive to false.
void Fish::Die() {
    alive = false;
}

// (1 point)
// A new member variable edible is added.
// Write a getter function to return the value of edible.
bool Fish::IsEdible() {
    return edible;
}

// (1 point)
// A new member variable edible is added.
// Write a setter function to set the value of edible to input e.
void Fish::SetEdible(bool e) {
    edible = e;
}

// (1 point)
// Write a getter function to return the size of the fish.
float Fish::GetSize() {
    return size;
}

int Fish::GetAge() {
    return age;
}

float Fish::GetReproduceProbability() {
    return reproduce_probability;
}

void Fish::Eat(std::vector<Fish*> fish_in_cell) {}