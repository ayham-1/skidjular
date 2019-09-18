#include "dispatcher.h"

Dispatcher::Dispatcher(std::vector<std::string> args) {
    this->m_parsedArgs = args;
}
Dispatcher::~Dispatcher(void) {}

auto Dispatcher::dispatch()->disfunc_ret {
    return disfunc_ret_fail;
}

auto Dispatcher::addArgument(std::vector<std::string> argument, disfunc func)->void {
    // Find already added nodes.
    unsigned int cnt = 1; // always skip name.
    std::shared_ptr<TreeNode<disfunc>> parent_node = this->m_argumentMap.getTree();
    for (unsigned int i = cnt; i < argument.size(); i++) {
        // Search for the next keyword in the childs of the most found node.
        for (auto child : parent_node->s_childs)
            if (child->s_name == argument[cnt]) {
                // Found the searched node.
                cnt++; // Incerment the found argument count variable.
                parent_node = child; // Set the parent to the current child node.
            }
    }

    // Check if the arguemnt is already there.
    if (cnt+1 == argument.size()) {
        std::cout << "Warning: Adding already added argument.\n";
        return;
    }

    // Create the new nodes except the last one.
    for (unsigned int i = cnt; i < (argument.size()-cnt)-1; i++) {
        TreeNode<disfunc> node;
        node.s_name = argument[i];
        node.s_parent = parent_node;
        parent_node = node;
        this->m_argumentMap.addNode(node);
    }
    // Create the last new node.
    { // Force variable to be local to a scope.
        std::shared_ptr<TreeNode<disfunc>> node = std::make_shared<TreeNode<disfunc>>(TreeNode<disfunc>());
        node->s_name = argument[argument.size()-1];
        node->s_data = func;
        node->s_parent = parent_node;
    }
}
