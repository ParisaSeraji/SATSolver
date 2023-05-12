#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>
#include <iostream>

// abstract superclass of the syntax tree node
class TreeNode {
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  protected:
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;
  public:
    //string  infixSTR;
    TreeNode(std::string cntt);
    std::string getContent() const;
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    void inorder(TreeNode* root);
    bool isLeaf(TreeNode* node);
    bool process(std::string op, bool left, bool right);
    bool eval(TreeNode *root, const std::map<std::string, bool> &M);

};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
};

// concrete tree node of constant type
class ConstantNode : public TreeNode {
  public:
    ConstantNode(std::string cntt);
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
};

#endif
