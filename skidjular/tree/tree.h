#pragma once
#ifndef SKIDS_TREE_H
#define SKIDS_TREE_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>

#define TREE_DIRTY_ACCESS_MAX_CNT 3

template<typename T>
struct TreeNode {
    std::string s_name;

    std::shared_ptr<TreeNode<T>> s_parent;
    std::vector<std::shared_ptr<TreeNode<T>>> s_childs;

    T s_data;
};

template<typename T>
class Tree {
    public:
        Tree(void);
        ~Tree(void);

        auto addNode(std::string parent_name, std::string node_name, T data)->bool;
        auto addNode(TreeNode<T> node)->bool;

        auto remNode(TreeNode<T> node)->bool;
        auto remNode(int index)->bool;
        auto remNode(std::string name)->bool;

        auto searchTree(std::shared_ptr<TreeNode<T>> root, std::string name)->std::shared_ptr<TreeNode<T>>;

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
