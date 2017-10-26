#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v{2, 3, 1, 6, 7, 1};

    // setting all values in v to 0
    for (auto i : v) {
        i = 0;
    }

    // displaying contents
    for (auto i : v) {
        cout << i << ' ';
    }
    cout << '\n';


}
