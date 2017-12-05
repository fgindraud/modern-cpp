#include <iostream>
#include <memory>
#include <vector>

class DAGNode {
    // std::vector<DAGNode*> children;
    std::vector<std::shared_ptr<DAGNode>> children;

  public:
    std::shared_ptr<DAGNode> new_child() {
        // DAGNode* new_child() {
        children.push_back(std::make_shared<DAGNode>());
        // children.push_back(new DAGNode());
        return children.back();
    }

    void connect_to(std::shared_ptr<DAGNode> ptr) { children.push_back(ptr); }
};

int main() {
    DAGNode origin;
    auto first_child = origin.new_child();
    auto second_child = origin.new_child();
    auto grandchild = first_child->new_child();
    second_child->connect_to(grandchild);
}
