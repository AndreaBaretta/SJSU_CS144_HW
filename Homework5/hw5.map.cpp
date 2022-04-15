// You can only include the following libraries:
// iostream, unordered_map, fstream, algorithm, vector
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
// In addition, you can also use substr and stod in <string>
using namespace std;
// You may write helper comparator functions here.
bool RestaurantItemNameComparator(const pair<string, double>& a, const pair<string, double>& b) {
    return a.first < b.first;
}

bool RestaurantItemAmountComparator(const pair<string, double>& a, const pair<string, double>& b) {
    return a.second > b.second;
}

// Do not add any member functions or variables.
class Restaurant {
   private:
    unordered_map<string, double> sales;

   public:
    Restaurant() {};
    // 1. (10 points)
    // Read the given text file. Each line in the input file
    // is a food name and amount of the sale (including $ sign).
    // Food name and amount are separated by space.
    // Example input file is hw5.input.txt.
    // Read the input file and keep one entry per food item in the member
    // variable sales. The key is the food name, and the value is to total
    // value of sales.
    void ReadFile(string fname) {
        ifstream file;
        file.open(fname);

        string key;
        string value_string;
        while (!file.eof()) {
            file >> key;
            // cout << "Key: " << key << "." << endl;
            file >> value_string;
            value_string.erase(0, 1);
            const double value = stod(value_string);
            // cout << "Value: " << value << "." << endl;

            if (sales.size() == 0) {
                sales.insert({key, value});
            } else if (sales.find(key) == sales.end()) {
                sales.insert({key, value});
            } else {
                sales.insert_or_assign(key, value + sales.at(key));
            }
        }
        file.close();
    };
    // 2. (5 points)
    // Print the total sales by name of the food item, in alphabetical order.
    // First print "Total by name".
    // Then for each food item, print one line. The line contains the food name,
    // space, and then the total value of sales.
    // Hint: Transfer from sales to vector, and sort vector.
    void PrintByName() {
        vector<pair<string, double>> vec(sales.size());
        vec.assign(sales.begin(), sales.end());
        cout << "Total by name:" << endl;
        sort(vec.begin(), vec.end(), RestaurantItemNameComparator);
        for (const pair<string, double> p : vec) {
            cout << p.first << " $" << p.second << endl; 
        }
    };
    // 3. (5 points)
    // Print the total sales in order of total sales amount.
    // First print "Total by amount".
    // Then for each food item, print one line. The line contains the food name,
    // space, and then the total value of sales.
    void PrintByAmount() {
        vector<pair<string, double>> vec(sales.size());
        vec.assign(sales.begin(), sales.end());
        cout << "Total by name:" << endl;
        sort(vec.begin(), vec.end(), RestaurantItemAmountComparator);
        for (const pair<string, double> p : vec) {
            cout << p.first << " $" << p.second << endl; 
        }
    };
};
// Do not change main() function.
int main() {
    Restaurant R;
    R.ReadFile("hw5.input.txt");
    R.PrintByName();
    cout << endl;
    R.PrintByAmount();
    return 0;
}
/*
Sample output:
Total by name:
Chips $70.45
Cookie $19.28
Fries $3.99
Hamburger $112.14
Hotdog $20.9
Pizza $309.48
Sandwich $54.82
Soup $105.15
Taco $62.09

Total by amount:
Pizza $309.48
Hamburger $112.14
Soup $105.15
Chips $70.45
Taco $62.09
Sandwich $54.82
Hotdog $20.9
Cookie $19.28
Fries $3.99
*/