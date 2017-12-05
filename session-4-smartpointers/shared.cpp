#include <iostream>
#include <memory>
#include <vector>

class DAGNode {
    // using ptr_type = std::shared_ptr<DAGNode>;
    using ptr_type = DAGNode*;

    std::vector<ptr_type> children;

  public:
    ptr_type new_child() {
        // children.push_back(std::make_shared<DAGNode>());
        children.push_back(new DAGNode());
        return children.back();
    }

    void connect_to(ptr_type ptr) { children.push_back(ptr); }
};

int main() {
    DAGNode origin;
    auto first_child = origin.new_child();
    auto second_child = origin.new_child();
    auto grandchild = first_child->new_child();
    second_child->connect_to(grandchild);
}
