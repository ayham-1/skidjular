#include "tree.h"

template<typename T>
Tree<T>::Tree(void) {}
template<typename T>
Tree<T>::~Tree(void) {
   this->deleteTree(this->m_treeRoot);
}

template<typename T>
auto Tree<T>::addNode(std::string parent_name, std::string node_name, T data)->bool {
    std::shared_ptr<TreeNode<T>> result = std::make_shared<TreeNode<T>>(TreeNode<T>());
    // Fill data for new node.
    result->s_name = node_name;
    result->s_data = data;

    // Check if new node is a root node.
    if (parent_name == "") {
        if (this->m_treeRoot) 
            if (!this->deleteTree(this->m_treeRoot))
                std::cout << "Couldn't delete tree, possible memory leaks!\n";
        this->m_treeRoot = result;
    }
    else {
        // Find parent for new node.
        result->s_parent = this->searchTree(this->getTree(), parent_name);

        // Add new node as child of parent node, if and only if it's not a root node.
        result->s_parent->s_childs.push_back(result);
    }

    // Add new Node to node array.
    this->m_treeNodes.push_back(result);

    return true;
}
template<typename T>
auto Tree<T>::addNode(TreeNode<T> node)->bool {
    // Add new Node to node array.
    std::shared_ptr<TreeNode<T>> result = std::make_shared<TreeNode<T>>(node);
    this->m_treeNodes.push_back(result);

    // Add new Node to nodeId map.
    this->m_treeIDMap.insert(std::make_pair(result->s_name, (int)(m_treeNodes.size()-1)));

    // Check if new node is a root node.
    if (result->s_name == "") {
        if (this->m_treeRoot) 
            if (!this->deleteTree(this->m_treeRoot))
                std::cout << "Could not delete tree, possible memory leaks!\n";
        this->m_treeRoot = result;
    }
    else
        // Add new node as child of parent node, if and only if it's not a root node.
        result->s_parent->s_childs.push_back(result);

    return true;
}

template<typename T>
auto Tree<T>::remNode(TreeNode<T> node)->bool {
    return this->deleteTree(this->searchTree(this->getTree(), node.s_name));
}
template<typename T>
auto Tree<T>::remNode(int index)->bool {
    return this->deleteTree(this->m_treeNodes[index]);
}
template<typename T>
auto Tree<T>::remNode(std::string name)->bool {
    return this->deleteTree(this->searchTree(this->getTree(), name));
}

template<typename T>
auto Tree<T>::getTree(void)->std::shared_ptr<TreeNode<T>> {return this->m_treeRoot;}

template<typename T>
auto Tree<T>::searchTree(std::shared_ptr<TreeNode<T>> root, std::string name)->std::shared_ptr<TreeNode<T>> {
    // Check if root is null.
    if (root == nullptr) return nullptr;
    // Check if passed node is the searched node.
    if (root->s_name == name)
        return root;
    // Check if one of the childs is the searched node.
    for (auto item : root->s_childs) {
        auto result = this->searchTree(item, name);
        if (result->s_name == name)
            return result;
    }
    return std::make_shared<TreeNode<T>>(TreeNode<T>());
}

template<typename T>
auto Tree<T>::deleteTree(std::shared_ptr<TreeNode<T>> root)->bool {
    // Don't delete if it is nullptr
    if (root == nullptr) return false;

    // Delete it's childs first.
    for (auto item : root->s_childs)
        if (!this->deleteTree(item))
            std::cout << "Couldn't delete node. Memory Leaks may occur!";

    // Remove parent link, if and only if it is not a root node.
    if (root->s_parent != nullptr)
        for (unsigned int i = 0; i < root->s_parent->s_childs.size(); i++)
            if (root->s_parent->s_childs[i] == root)
                root->s_parent->s_childs.erase(std::begin(root->s_parent->s_childs)+i);

    // Find node and remove it from node array.
    for (unsigned int i = 0; i < this->m_treeNodes.size(); i++)
        if (this->m_treeNodes[i] == root)
            this->m_treeNodes.erase(std::begin(this->m_treeNodes)+i);

    // Delete current node.
    root.reset();

    return true;
}

template<typename T>
auto Tree<T>::printTree(std::shared_ptr<TreeNode<T>> root)->void {
    this->printTree(root, 0);
}

template<typename T>
auto Tree<T>::printTree(std::shared_ptr<TreeNode<T>> root, int deep)->void {
    // Print root.
    if (!root->s_parent)
        std::cout << "→ " << root->s_name << "\n";
    else { 
        for (int i = 0; i < deep; i++)
            std::cout << "   ";
        std::cout << "↳ " << root->s_name << "\n";
    }

    // Print it's childs.
    for (auto item : root->s_childs)
        this->printTree(item, deep+1);
}
