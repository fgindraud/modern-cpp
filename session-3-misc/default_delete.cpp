#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct StreamWrapper {
    ostream& os{cout};
    // StreamWrapper() = default;
    // StreamWrapper(const StreamWrapper&) = delete;
};

class Hello {
    StreamWrapper& sw;

public:
    Hello(StreamWrapper& sw) : sw(sw) {}

    void hello() {
        sw.os << "Hello world\n";
    }
};


int main() {
    StreamWrapper w;
    // vector<StreamWrapper> wv;
    // wv.push_back(StreamWrapper());

    // list<StreamWrapper> wl;
    // wl.emplace_front();

    Hello h(w);
    // Hello h(wv.front());

    // wv.push_back(StreamWrapper());
    // wl.emplace_front();

    h.hello();
}
