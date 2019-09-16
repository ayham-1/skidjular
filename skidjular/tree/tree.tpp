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
        // TODO: check return of delete function.
        if (this->m_treeRoot) this->deleteTree(this->m_treeRoot);
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

    // Add new Node to nodeID map.
    this->m_treeIDMap.insert(std::make_pair(result->s_name, (int)(m_treeNodes.size()-1)));
    
    return true;
}
template<typename T>
auto Tree<T>::addNode(TreeNode<T> node)->bool {
    std::shared_ptr<TreeNode<T>> result = std::make_shared<TreeNode<T>>(node);
    // Add new Node to node array.
    this->m_treeNodes.push_back(result);

    // Add new Node to nodeId map.
    this->m_treeIDMap.insert(std::make_pair(result->s_name, (int)(m_treeNodes.size()-1)));

    // Check if new node is a root node.
    if (result->s_name == "") {
        // TODO: check return of delete function.
        if (this->m_treeRoot) this->deleteTree(this->m_treeRoot);
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
    if (this->m_treeIDMapDirty) {
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
    }
    else
        return this->m_treeNodes[this->m_treeIDMap[name]];

    return std::make_shared<TreeNode<T>>(TreeNode<T>());
}

template<typename T>
auto Tree<T>::deleteTree(std::shared_ptr<TreeNode<T>> root)->bool {
    // Delete it's childs first.
    for (auto item : root->s_childs)
        if (item && !this->deleteTree(item))
            std::cout << "Couldn't delete node. Memory Leaks may occur!";

    // Delete current node.
    // TODO: Find how-to do it here.
    
    // Find node and remove it from node array.
    for (unsigned int i = 0; i < this->m_treeNodes.size(); i++)
        if (this->m_treeNodes[i]->s_name == root->s_name) {
            this->m_treeNodes.erase(std::begin(this->m_treeNodes)+i);
            this->m_treeIDMapDirty = true;
        }
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
