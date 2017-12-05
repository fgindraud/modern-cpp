#include <iostream>
#include <map>
#include <vector>

using namespace std;

void display_vec(vector<int> v) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << '\n';
}

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(4);
    v.push_back(11);
    v.push_back(7);

    // vector<int> v{1, 4, 11, 12, 3, 4, 5, 1, 7, 23, 12};
    display_vec(v);

    // map<int, string> m = {{2, "aa"}, {5, "youpi"}, {98, "youpla"}};

    // for (auto it = m.begin(); it != m.end(); it++) {
    //     cout << it->first << "/" << it->second << "  ";
    // }
    // cout << '\n';

    // vector<int> v2(12, 2);
    // vector<int> v2{12, 2};
    // vector<int> v2 = {12, 2};
    // display_vec(v2);
}

// class DefaultValue {
//     int i{7};
//     DefaultValue() {}
//     DefaultValue(int i) : i(i) {}
// };
