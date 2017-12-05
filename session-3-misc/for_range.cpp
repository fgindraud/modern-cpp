#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main() {
    vector<int> v{2, 3, 1, 6, 7, 1};

    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << ' ';
    }
    cout << '\n';

    // set<int> s{1, 3, 7, 5};

    // for (set<int>::iterator it = s.begin(); it != s.end(); ++it) {
    //     cout << *it << ' ';
    // }
    // cout << '\n';

    // for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    //     cout << *it << ' ';
    // }
    // cout << '\n';

    // for (const int element : s) {
    //     cout << element << ' ';
    // }
    // cout << '\n';

    // for (auto element : s) {
    //     cout << element << ' ';
    // }
    // cout << '\n';

    // map<string, int> m{make_pair("a", 1), make_pair("b", 3), make_pair("c", 17)};

    // for (auto p : m) {
    //     cout << '(' << p.first << ", " << p.second << ") ";
    // }
    // cout << '\n';

    // for (auto i : {1, 2, 3, 17}) {
    //     cout << i << ' ';
    // }
    // cout << '\n';
}
