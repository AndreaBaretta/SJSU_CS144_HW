#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Animal {
   public:
    Animal() : age(0){};
    virtual void Speak() { cout << "Growl." << endl; };
    void Grow() { age++; };
    virtual ~Animal() {};

   private:
    int age;
};

class Dog : public Animal {
   public:
    Dog(){};
    void Speak() { cout << "Woof!" << endl; };
};

class Cat : public Animal {
   public:
    Cat() : num_lives(9) {
        lives = new int[num_lives];
        for (int i = 0; i < num_lives; i++) {
            lives[i] = i;
        }
    };
    void Speak() { cout << "Meow." << endl; };
    ~Cat() {
        delete[] lives;
    }

   private:
    int num_lives;
    int* lives;
};

// Write your answer to Q1 here.
void MakeAnimalSpeak(Animal& a) {
    a.Speak();
}

// Write code for Q3 here.
void Separate(const vector<Animal*>& a, vector<Dog*>& d, vector<Cat*>& c) {
    for (Animal* aptr : a) {
        if (dynamic_cast<Dog*>(aptr) != nullptr) {
            d.push_back(static_cast<Dog*>(aptr));
        } else if (dynamic_cast<Cat*>(aptr) != nullptr) {
            c.push_back(dynamic_cast<Cat*>(aptr));
        }
    }
}

int main() {
    Animal a_array[10];
    Dog d_array[10];
    Cat c_array[10];

    // Q1. [6 points]
    // Write the function MakeAnimalSpeak that can take any of the above 30
    // animals as argument and make it speak using the most specific
    // (most derived class) Speak() function.
    // For example, if you call this function on c_array[3],
    // it should print "Meow".
    // You can determine the argument type of this function.
    // You may also make code changes to the classes above.
    // ... give argument to pass in c_array[3]...
    MakeAnimalSpeak(c_array[3]);

    // Q2. [ 6 points]
    // Write code in the classes above so that the code below frees memory
    // correctly.
    // In other words, when "delete aptr" is called, the dynamically allocated
    // array in Cat::lives is freed.
    // Do not change the code below.
    Animal* aptr = new Cat;
    aptr->Grow();
    delete aptr;

    cout << "Cat" << endl;

    // [6 points]
    // Q3. Write the Separate function that receives a vector of Animal*
    // and puts all the pointers to Dogs in the dogs vector, and all the
    // pointers to Cats in the cats vector.
    vector<Dog*> dogs;
    vector<Cat*> cats;
    vector<Animal*> animals;
    int cat_counter = 0;
    for (int i = 0; i < 20; i++) {
        int r = rand() % 3;
        cout << "r = " << r << endl;
        if (r == 0) {
            animals.push_back(new Dog);
        } else if (r == 1) {
            ++cat_counter;
            animals.push_back(new Cat);
        } else if (r == 2) {
            animals.push_back(new Animal);
        }
    }
    cout << "cat_counter = " << cat_counter << endl;

    Separate(animals, dogs, cats);

    cout << "discovered cats = " << cats.size() << endl;
    cout << endl << endl << "Printing cats" << endl;
    for (int i = 0; i < cats.size(); i++) {
        cats[i]->Speak();
    }

    return 0;
}
