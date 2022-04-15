#include "hw7.shark.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Shark::Shark() : Fish(), hunger(0) {
    Fish::SetEdible(false);
}

// (3 points)
// Redefine the Grow() function for Shark that:
//   1. If hunger is greater than max_hunger, call Die().
//   2. Increase hunger by hunger_increment.
//   3. Call the regular Fish::Grow() function to grow just like a fish.
void Shark::Grow() {
    if (hunger >= max_hunger) {
        Die();
    } else {
        hunger += hunger_increment;
        Fish::Grow();
    }
}

// (1 point)
// Redefine the Reproduce() function that is same as the regular
// Fish::Reproduce() except that it should return a Shark rather than a
// Fish.
Shark* Shark::Reproduce() {
    float threshold =
        static_cast<float>(Fish::GetAge() - 2) * Fish::GetReproduceProbability() * 1000.0;
    float f = static_cast<float>(rand() % 1000);
    if (f < threshold) {
        return new Shark();
    } else {
        return nullptr;
    }
}

// When this function is called, eat as much Fish as necessary to satisfy
// hunger.
// For example, if the shark's hunger is 7, and there are four fish whose
// sizes are 2, 4, 2, 5,
// then the first 3 fish will be eaten, and the shark's hunger is set to
// zero. For each fish eaten, call Die() for the fish. Note that only edible
// fish can be eaten. Sharks are not edible. Another example, suppose the
// shark's hunger is 7, and there are two fish whose sizes are 2, 3, then
// both fish would be eaten, and the shark's new hunger value is 7 - 2 - 3
// = 5. Note that Eat() is called in Sea::SimulateOneStep().
void Shark::Eat(std::vector<Fish*> fish_in_cell) {
    for (Fish* fish : fish_in_cell) {
        if (hunger <= 0) {
            hunger = 0;
            break;
        }
        if (fish->IsEdible()) {
            hunger -= fish->GetSize();
            fish->Die();
            fish->SetEdible(false);
        }
    }
}