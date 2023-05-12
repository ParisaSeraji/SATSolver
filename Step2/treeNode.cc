#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::setContent(std::string newContent) {
      content = newContent;
      return content;
    }

    void TreeNode::updateLeftChild(TreeNode *lChild) { leftChild = lChild; }
    void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
      leftChild = lChild;
      rightChild = rChild;
    }

    std::string TreeNode::getContent() const { return content; }

    TreeNode *TreeNode::getLeftChild() const { return leftChild; }
    TreeNode *TreeNode::getRightChild() const { return rightChild; }

    OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

    
    
    VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

