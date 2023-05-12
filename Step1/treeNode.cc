#include "treeNode.h"

using namespace std;

TreeNode::TreeNode(std::string cntt)
{
  this->content = cntt;
}

std::string TreeNode::getContent() const
{
  // your code starts here
  return content;
}

TreeNode *TreeNode::getLeftChild() const
{
  // your code starts here
  return this->leftChild;
}
TreeNode *TreeNode::getRightChild() const
{
  // your code starts here
  return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild)
{
  // your code starts here
  this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild)
{
  // your code starts here
  this->leftChild = lChild;
  this->rightChild = rChild;
}
void TreeNode::inorder(TreeNode *root)
{
  if (root == nullptr)
  {
    return;
  }
  inorder(root->getLeftChild());
  //std::cout << root->getContent() << endl;
  inorder(root->getRightChild());
  
}

bool TreeNode::isLeaf(TreeNode *node)
{
  TreeNode *left = node->getLeftChild();
  TreeNode *right = node->getRightChild();
  return left == nullptr && right == nullptr;
}

bool TreeNode::process(string op, bool left, bool right)
{
  
  if (op == "+")
  {
    return left || right;
  }
  if (op == "-")
  {
    return !left;
  }
  if (op == "*")
  {
    return left && right;
  }

  return false;
}

bool TreeNode::eval(TreeNode *root, const map<string, bool> &M)
{
  if (root == nullptr)
  {
    return false;
  }

  // the leaves of a binary expression tree are operands
  string content = root->getContent();
  if (root->isLeaf(root))
  {

    bool bContent;
    if (content == "1" || content == "0")
    {
      return ((content == "1") ? true : false);
    }
    else
    {
      for (auto pair : M)
      {
        if (pair.first == content)
        {
          bContent = pair.second;
        }
      }
      return bContent;
    }
  }
  TreeNode *lChild = root->TreeNode::getLeftChild(), *rChild = root->TreeNode::getRightChild();
  bool x = eval(lChild, M);
  bool y = eval(rChild, M);

  return process(content, x, y);
}

OperatorNode::OperatorNode(std::string cntt) : TreeNode{cntt} {}

ConstantNode::ConstantNode(std::string cntt) : TreeNode{cntt} {}

VariableNode::VariableNode(std::string cntt) : TreeNode{cntt} {}
