#include <iostream>
using namespace std;
class Student {
   private:
    int id;
    string name;

   public:
    Student() : id(0), name(""){};
    Student(int i, string n) : id(i), name(n){};
    int GetID() const { return id; };
    string GetName() const { return name; };
};
bool operator==(const Student& lhs, const Student& rhs) {
    return lhs.GetID() == rhs.GetID();
}
ostream& operator<<(ostream& os, const Student& s) {
    os << "(" << s.GetID() << ", " << s.GetName() << ")";
    return os;
}
// 1. [10 points]
// Convert ListNode and List into template struct and class respectively so
// that the code works.
template <typename T>
struct ListNode {
    T data;
    ListNode* next;
};

template <typename T>
class List {
   private:
    ListNode<T>* head;
    ListNode<T>* tail;

   public:
    List() : head(nullptr), tail(nullptr){};

    void InsertFront(T n) {
        ListNode<T>* temp = new ListNode<T>;
        temp->data = n;
        temp->next = head;
        head = temp;
        if (tail == nullptr)
            tail = temp;
    };

    void InsertBack(T n) {
        if (tail == nullptr) {
            head = tail = new ListNode<T>;
            head->data = n;
            head->next = nullptr;
        } else {
            tail->next = new ListNode<T>;
            tail->next->data = n;
            tail->next->next = nullptr;
            tail = tail->next;
        }
    };

    void Print() {
        for (ListNode<T>* lptr = head; lptr != nullptr; lptr = lptr->next) {
            cout << lptr->data << " ";
        }
        cout << endl;
    };
    // 2. [10 points]
    // Write a function Remove that accepts an input X of the same type that
    // is stored in the list, and removes all list nodes containing an item
    // identical to the input X. (Use the == operator to test for equality.)
    void Remove(T n) {
        if (head == nullptr || tail == nullptr) {  // List is of length 0
            return;
        }
        if (head == tail && head->data == n) {  // List is of length 1 and that one object is the right one
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        if (head->data == n) {  // First element is the right one, so I don't need to worry about previous node
            ListNode<T>* tmp = head->next;
            delete head;
            head = tmp;
            Remove(n);
            return;
        }
        for (ListNode<T>* lptr = head; lptr->next != nullptr; lptr = lptr->next) {  // Normal scenario, need to keep track of previous
            if (lptr->next->data == n) {
                if (lptr->next != tail) {
                    ListNode<T>* tmp = lptr->next;
                    lptr->next = lptr->next->next;
                    delete tmp;
                    Remove(n);
                    return;
                } else {
                    ListNode<T>* tmp = lptr->next;
                    lptr->next = lptr->next->next;
                    delete tmp;
                    tail = lptr;
                    Remove(n);
                    return;
                }
            }
        }
    };
};
int main() {
    List<int> L;

    L.Remove(2);
    L.Print();
    L.InsertBack(2);
    L.Print();
    L.Remove(2);
    L.Print();
    L.InsertFront(3);
    L.InsertFront(8);
    L.Print();
    L.Remove(8);
    L.Print();
    L.InsertBack(5);
    L.InsertFront(20);
    L.Print();
    L.Remove(5);
    L.Print();
    L.InsertBack(17);
    L.Print();
    L.Remove(3);
    L.Print();
    L.Remove(20);
    L.Print();
    L.InsertBack(1);
    L.Print();
    L.InsertBack(2);
    L.Print();

    L.Remove(17);
    L.Print();
    List<Student> LS;
    Student S1(1, "Frank");
    Student S2(2, "George");
    Student S3(3, "Henry");
    Student S4(4, "Irene");
    Student S5(5, "Jennifer");
    LS.InsertFront(S4);
    LS.InsertBack(S3);
    LS.InsertBack(S1);
    LS.InsertBack(S2);
    LS.InsertFront(S5);
    LS.Remove(S3);
    LS.Print();

    return 0;
}
/*
Sample output:
2
8 3
3
20 3 5
20 3
20 3 17
20 17
17
17 1
17 1 2
1 2
(5, Jennifer) (4, Irene) (1, Frank) (2, George)
*/