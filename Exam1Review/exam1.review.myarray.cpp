#include <cassert>
#include <iostream>
using namespace std;
class MyArray {
   private:
    int* data;
    int size;
    int capacity;

   public:
    MyArray() : size(0), capacity(2) { data = new int[2]; };

    MyArray(const MyArray& m) {
        size = m.size;
        capacity = m.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = m.data[i];
        }
    };
    ~MyArray() { delete[] data; };

    void Insert(int n) {
        if (size >= capacity) {
            int* olddata = data;
            data = new int[capacity * 2];
            for (int i = 0; i < capacity; i++) {
                data[i] = olddata[i];
            }
            capacity = capacity * 2;
            delete[] olddata;
        }
        data[size] = n;
        size++;
    };
    void Print() const {
        cout << "MyArray size: " << size << " capacity: " << capacity << endl;
        cout << "  data: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    int& operator[](int ind) {
        assert((ind >= 0) && (ind < size));
        return data[ind];
    };
    // Write a function Remove that removes items from index start_ind to
    // end_ind inclusive.
    void Remove(int start_ind, int end_ind) {
        assert((start_ind >= 0) && (start_ind < size));
        assert((end_ind >= 0) && (end_ind < size));
        assert(start_ind >= end_ind);
        int* const new_data = new int[capacity];
        for (std::size_t i = 0; i < start_ind; ++i) {
            new_data[i] = data[i];
        }
        for (std::size_t i = end_ind + 1; i < size; ++i) {
            new_data[i - (start_ind - 1)] = data[i];
        }
        delete[] data;
        data = new_data;
        size -= ((start_ind - end_ind) + 1);
    }
    // Write a function Repeat that repeats each item in the array k times.
    // capacity does not need to be power of 2.
    void Repeat(int k){};
};
// Write a function that puts all odd elements of a in odds,
// and all even elements of a in evens.
// Remove all previous content of odds and evens.
// a remains unchanged.
void Split(const MyArray& a, MyArray* odds, MyArray* evens) {}
int main() {
    MyArray A;
    for (int i = 0; i < 8; i++)
        A.Insert(i * 2);
    A.Remove(2, 4);
    A.Print();
    A.Remove(3, 20);
    A.Print();
    MyArray B;
    MyArray C;
    for (int i = 0; i < 20; i++)
        B.Insert(rand() % 100);
    Split(B, &A, &C);
    A.Print();
    B.Print();
    C.Print();
    C.Repeat(3);
    C.Print();
    return 0;
}
/* Sample output:
MyArray size: 5 capacity: 8
  data: 0 2 10 12 14
MyArray size: 3 capacity: 8
  data: 0 2 10
MyArray size: 10 capacity: 16
  data: 33 43 29 19 11 51 43 5 93 69
MyArray size: 20 capacity: 32
  data: 33 43 62 29 0 8 52 56 56 19 11 51 43 5 8 93 30 66 69 32
MyArray size: 10 capacity: 16
  data: 62 0 8 52 56 56 8 30 66 32
MyArray size: 30 capacity: 30
  data: 62 62 62 0 0 0 8 8 8 52 52 52 56 56 56 56 56 56 8 8 8 30 30 30 66 66 66
32 32 32
*/