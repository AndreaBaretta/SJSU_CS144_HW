// Do not use the STL set and map classes
// such as ordered_set, unordered_set, ordered_map and unordered_map.
#include <iostream>
using namespace std;
// A Set contains ints with no duplicates.

class Set {
   private:
    int* data;
    int size;
    int capacity;

   public:
    Set() : data(nullptr), size(0), capacity(0) {};
    // (c) [3 points] Write a constructor that takes two arguments:
    // int arr[], which is an array of ints to put into data, and
    // int len, which is the length of arr.
    // Post-conditions:
    // data[] should contain all the ints in arr[], except no duplicates. For
    // example, if 7 appears three times in arr[], it should only appear once
    // in data[].
    // size should be the number of ints data[] contains.
    // Initially, data should be null pointer, and capacity 0.
    Set(int arr[], int len) : data(new int[len]), size(0), capacity(len) {
        for (int i = 0; i < len; ++i) {
            Insert(arr[i]);
        }
    }
    // (b) [2 points] Modify the Insert function to make sure that
    // we don't insert a value that already exists in the set.
    void Insert(int val) {
        if (Exists(val)) return;
        if (capacity < size + 1) {
            DoubleCapacity();
        }
        data[size] = val;
        size++;
    };

    void DoubleCapacity() {
        int* old = data;
        data = new int[(capacity + 1) * 2];
        for (int i = 0; i < size; i++) {
            data[i] = old[i];
        }
        if (capacity > 0)
            delete[] old;
        capacity = (capacity + 1) * 2;
    };
    // (d) [1 points] Return that value at the given index.
    int GetVal(int ind) {
        return data[ind];
    }

    void Print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    };
    // (e) [2 points] Swap the values of data[i] and data[j].
    void Swap(int i, int j) {
        if (0 <= i && 0 <= j && i < size && j < size) {
            int val_i = data[i];
            int val_j = data[j];
            data[i] = val_j;
            data[j] = val_i;
        }
    }

    int GetSize() { return size; };
    // (f) [2 points] Write the copy constructor. It is required that the data[]
    // for this object points to a different memory location as the data[] in
    // the copied object. Also, it is required to avoid memory leak.

    Set(const Set& set) : data(new int[set.size]), size(set.size), capacity(set.size) {
        for (int i = 0; i < set.size; ++i) {
            data[i] = set.data[i];
        }
    }

    // (g) [2 points] Overload the assignment operator. Sane requirements as
    // copy constructor.
    Set& operator=(const Set& set) {
        delete[] data;
        data = new int[set.size];
        size = set.size;
        capacity = set.size;
        for (int i = 0; i < set.size; ++i) {
            data[i] = set.data[i];
        }
        return *this;
    }

    // (h) [2 points] Write the destructor. You must free memory so that there
    // is no memory leak.
    ~Set() {
        delete[] data;
    }

   private:
    // (a) [2 points] Returns true if val is in data[], false otherwise.
    bool Exists(int val) {
        for (int i = 0; i < size; ++i) {
            if (data[i] == val) {
                return true;
            }
        }
        return false;
    }
};
// OrderedSet is like a Set: It cannot contain duplicate values.
// One additional property of OrderedSet: Its values are stored in order,
// from lowest value to highest value.
// Do not add new member variables into OrderedSet or Set.
// Do not add new public member functions into Set.
// Do not make OrderedSet a friend of Set.
class OrderedSet : public Set {
   public:
    OrderedSet() : Set(){};
    // (i) [4 points] Override the base Insert() function, so that the
    // OrderedSet remains in order, from smallest to biggest. First, put the new
    // value at the end of the array. Then, repeatedly swap backwards until it
    // finds its rightful position.
    void Insert(int val) {
        Set::Insert(val);
        for (int i = Set::GetSize() - 1; i > 0; --i) {
            if (Set::GetVal(i - 1) > Set::GetVal(i)) {
                Set::Swap(i - 1, i);
            } else {
                return;
            }
        }
    }
};
int main() {
    int arr[6] = {1, 4, 7, 7, 2, 15};
    Set s(arr, 6);
    Set s2(s);
    s2.Swap(2, 3);
    s.Print();
    s2.Print();
    s.Insert(5);
    s.Insert(1);
    s.Insert(9);
    s.Insert(4);
    s.Insert(5);
    s.Print();
    OrderedSet o;
    o.Insert(5);
    o.Insert(1);
    o.Insert(9);
    o.Insert(4);
    o.Insert(5);
    o.Insert(2);
    o.Insert(8);
    o.Insert(9);
    o.Insert(3);
    o.Print();
    return 0;
}
/*
Sample output (Note: This doesn't test all functionality):
1 4 7 2 15
1 4 2 7 15
1 4 7 2 15 5 9
1 2 3 4 5 8 9
*/