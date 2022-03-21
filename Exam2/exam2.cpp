// Answer each question by writing code in the body.
// Example usage is in the main function.
// Note: The example usage does not exhaustively test each function.
//       Your code should work for all cases, not just the example usage.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class List;

class ListNode {
   private:
    int data;
    ListNode* next;
    ListNode* prev;

   public:
    ListNode(int d, ListNode* n, ListNode* p) : data(d), next(n), prev(p){};
    void SetPrev(ListNode* p) { prev = p; };
    void SetNext(ListNode* n) { next = n; };
    friend class List;
};

class List {
   private:
    ListNode* head;

   public:
    List() : head(nullptr){};

    void InsertFront(int n) {
        ListNode* temp = new ListNode(n, head, nullptr);
        if (head != nullptr)
            head->prev = temp;
        head = temp;
    };

    // Q1. [4 points]
    // Write operator[]. Return the nth ListNode. The 0th ListNode is head.
    ListNode* operator[](int n) {
        ListNode* ret = head;
        for (int i = 0; i < n; ++i) {
            ret = ret->next;
        }
        return ret;
    };

    // Q2. [6 points]
    // Write a member function Remove to remove the given ListNode from the
    // list.
    void Remove(ListNode* node) {
        ListNode* tmp = head;
        while (tmp != node && tmp != nullptr) {
            tmp = tmp->next;
        }
        if (tmp == head && head->next == nullptr) {
            delete head;
            head = nullptr;
        } else if (tmp == head) {
            // cout << "Removing head (in method)" << endl;
            // cout << "Head data: " << head->data << endl;
            // cout << "prev data: " << head->next->data << endl;
            // Print();
            head->next->SetPrev(nullptr);
            // cout << "SetPrev" << endl;
            head = tmp->next;
            delete tmp;
            // cout << "Deleted" << endl;
            // cout << "Done removing head (in method)" << endl;
            // Print();
        } else if (tmp != nullptr) {  // We did find it
            if (tmp->next == nullptr) {
                tmp->prev->SetNext(nullptr);
                delete tmp;
            } else {
                tmp->prev->SetNext(tmp->next);
                tmp->next->SetPrev(tmp->prev);
                delete tmp;
            }
        }
    };

    // Q3. [8 points]
    // Write the member function Sort that when called will rearrange
    // the ListNodes such that the list is sorted from greatest to least.
    // Do not make new ListNodes.
    // Do not change the data of the ListNodes.
    // Just rearrange by setting prev and next pointers of the ListNodes
    // and also set head to point to the greatest ListNode.
    // Efficiency is not important. O(n^2) algorithm is OK.

    void SwapConsecutive(int i) {
        ListNode* i_node = (*this)[i];
        ListNode* j_node = (*this)[i + 1];

        ListNode* i_node_next =
            i_node->next;  // Save next and previous pointers to temporary
                           // variables
        ListNode* i_node_prev = i_node->prev;

        ListNode* j_node_next = j_node->next;  // Same with j
        ListNode* j_node_prev = j_node->prev;

        // i_node_next->SetPrev(j_node);  // Set neighboring nodes
        // if (i_node_prev != nullptr) {
        //     i_node_prev->SetNext(j_node);
        // }
        // j_node->SetNext(i_node_next);  // Set the node itself
        // j_node->SetPrev(i_node_prev);

        // if (j_node_next != nullptr) {
        //     j_node_next->SetPrev(i_node);  // Set neighboring nodes
        // }
        // j_node_prev->SetNext(i_node);
        // i_node->SetNext(j_node_next);  // Set the node itself
        // i_node->SetPrev(j_node_prev);

        if (i == 0) {
            i_node->SetNext(j_node_next);
            i_node->SetPrev(j_node);
            j_node->SetNext(i_node);
            j_node->SetPrev(nullptr);
            head = j_node;
        } else if (i+1 == GetLength()) {
            j_node->SetNext(i_node);
            j_node->SetPrev(i_node_prev);
            i_node->SetNext(nullptr);
            i_node->SetPrev(j_node);
        } else {
            if (i_node_prev != nullptr) {
                i_node_prev->SetNext(j_node);
            }
            j_node->SetPrev(i_node_prev);
            if (j_node_next != nullptr) {
                j_node_next->SetPrev(i_node);
            }
            i_node->SetNext(j_node_next);

            j_node->SetNext(i_node);
            i_node->SetPrev(j_node);
        }

        // ListNode* i_node = (*this)[i];
        // ListNode* j_node = (*this)[i+1];

        // if (i == 0) {
        //     i
        // }
    }

    int GetLength() {
        int l = 0;
        ListNode* tmp = head;
        while (tmp != nullptr) {
            tmp = tmp->next;
            ++l;
        }
        return l;
    }

    void Sort() {
        bool sorted = false;
        bool c = true;
        const int l = GetLength();

        cout << "l: " << l << endl;

        if (l == 0 || l == 1) {
            return;
        }



        while (!sorted) {
            sorted = true;
            for (int i = 0; i < l - 1; ++i) {
                cout << "i: " << i << endl;
                if ((*this)[i]->data < (*this)[i + 1]->data) {
                    SwapConsecutive(i);
                    // cout << "Result: " << endl;
                    Print();
                    sorted = false;
                    break;
                }
            }
        }
        cout << "ended sort" << endl;
    };

    void Print() {
        for (ListNode* lptr = head; lptr != nullptr; lptr = lptr->next) {
            cout << lptr->data << " ";
        }
        cout << endl;
    };
};

// Q4: [6 points]
// Write the function ArrangeAlphabetical that receives a string s,
// and returns another string with the same characters as s,
// but with the letters arranged alphabetically.
string ArrangeAlphabetical(string& s) {
    string arranged = string(s);

    const size_t l = arranged.size();
    bool sorted = false;
    while (!sorted) {
        for (int i = 0; i < l - 1; ++i) {
            char m = arranged[i];
            char n = arranged[i + 1];
            arranged[i] = n;
            arranged[i + 1] = m;
            break;
        }
        sorted = true;
    }
    return arranged;
}

// Q5: [6 points]
// Change this class into a template class
// so that val can be float, int or string.
// Doubling a string means repeating that string.
// You may write other functions so that this works.
template <typename T>
class Doubler {
   private:
    T val;

   public:
    Doubler(T v) : val(v){};
    void Double() { val = val + val; };
    void Print() { cout << val << endl; };
};

int main() {
    cout << "Testing Remove" << endl;

    List L;
    L.InsertFront(1);
    L.InsertFront(2);
    L.InsertFront(3);
    L.InsertFront(4);
    L.InsertFront(5);
    L.InsertFront(6);
    L.InsertFront(7);
    L.InsertFront(8);
    L.InsertFront(9);
    L.Print();

    L.Remove(L[3]);
    L.Print();

    L.Remove(L[5]);
    L.Print();

    // cout << "Adding 10" << endl;
    L.InsertFront(10);
    // L.Print(); // CUSTOM
    L.Remove(L[0]);
    // L.Print(); // CUSTOM
    L.InsertFront(11);
    // L.Print();
    // cout << "Removing L[7]" << endl;
    L.Remove(L[7]);
    L.Print();

    cout << endl << "Testing Sort" << endl;
    List L2;
    L2.InsertFront(11);
    L2.InsertFront(6);
    L2.InsertFront(1);
    L2.InsertFront(5);
    L2.InsertFront(10);
    L2.InsertFront(2);
    L2.InsertFront(7);
    L2.InsertFront(8);
    L2.InsertFront(0);
    L2.Print();  // Custom
    L2.SwapConsecutive(0);
    L2.Print();
    L2.Sort();
    L2.Print();

    cout << endl << "Testing ArrangeAlphabetical" << endl;
    string s = "different";
    string s2 = ArrangeAlphabetical(s);
    cout << s2 << endl;

    string s3 = s + s + s;
    cout << s3 << endl;

    cout << endl << "Testing Doubler" << endl;

    Doubler<float> DF(4.2);
    DF.Double();
    DF.Double();
    DF.Print();

    Doubler<string> DF2("hello");
    DF2.Double();
    DF2.Print();

    return 0;
}

/*
Testing Remove
9 8 7 6 5 4 3 2 1
9 8 7 5 4 3 2 1
9 8 7 5 4 2 1
11 9 8 7 5 4 2

Testing Sort
11 10 8 7 6 5 2 1 0

Testing ArrangeAlphabetical
deeffinrt
differentdifferentdifferent

Testing Doubler
16.8
hellohello
*/
