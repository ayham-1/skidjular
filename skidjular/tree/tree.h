#pragma once
#ifndef SKIDS_TREE_H
#define SKIDS_TREE_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>

template<typename T>
struct TreeNode {
    std::string s_name;

    std::shared_ptr<TreeNode<T>> s_parent;
    std::vector<std::shared_ptr<TreeNode<T>>> s_childs;

    T s_data;

    bool operator==(const TreeNode<T>& left) {
        if (this->s_name == left.s_name) 
            if (this->s_parent == left.s_parent)
                if (this->s_childs == left.s_childs)
                    if (this->s_data == left.s_data)
                        return true;
        return false;
    }
};

template<typename T>
class Tree {
    public:
        Tree(void);
        ~Tree(void);

        auto addNode(std::string parent_name, std::string node_name, T data)->bool;
        auto addNode(TreeNode<T> node)->bool;
        auto addNode(std::shared_ptr<TreeNode<T>> node)->bool;

        auto remNode(TreeNode<T> node)->bool;
        auto remNode(int index)->bool;
        auto remNode(std::string name)->bool;

        auto searchTree(std::shared_ptr<TreeNode<T>> root, std::string name)->std::shared_ptr<TreeNode<T>>;
        auto searchTree(std::shared_ptr<TreeNode<T>> root, TreeNode<T> node)->std::shared_ptr<TreeNode<T>>;

        auto getTree(void)->std::shared_ptr<TreeNode<T>>;

        auto printTree(std::shared_ptr<TreeNode<T>> root)->void;

        auto tidyTree(void)->void;
    private:
        auto deleteTree(std::shared_ptr<TreeNode<T>> root)->bool;
        auto printTree(std::shared_ptr<TreeNode<T>> root, int deep)->void;
    private:
        std::shared_ptr<TreeNode<T>> m_treeRoot;
        std::vector<std::shared_ptr<TreeNode<T>>> m_treeNodes;
};

#include "tree.tpp"

#endif
