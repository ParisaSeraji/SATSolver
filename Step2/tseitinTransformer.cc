#include "tseitinTransformer.h"

#include <iostream>
//#include "treeNode.cc"

TseitinTransformer::TseitinTransformer(TreeNode *root) : formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode *subRoot)
{
  // your code starts here
  std::string nodeValue = subRoot->getContent();
  if (nodeValue == "*" || nodeValue == "+" || nodeValue == "-")
  {
    int opId = varIdCounter++;
    varIdTable[nodeValue] = opId;
    TreeNode *left, *right;
    int leftID, rightID;
    if (nodeValue == "-")
    {
      left = subRoot->getLeftChild();
      leftID = transSubformula(left);
      addNegEq(opId, leftID);
      return opId;
    }
    else
    {
      left = subRoot->getLeftChild();
      leftID = transSubformula(left);
      right = subRoot->getRightChild();
      rightID = transSubformula(right);
      if (nodeValue == "+")
      {
        addOrEq(opId, leftID, rightID);
      }
      else
      {
        addAndEq(opId, leftID, rightID);
      }
      return opId;
    }
  }
  else
  {
    if (varIdTable.find(nodeValue) == varIdTable.end())
    {
      varIdTable[nodeValue] = varIdCounter++;
    }
    return varIdTable[nodeValue];
  }
}

void TseitinTransformer::addNegEq(int curID, int childID)
{
  // your code starts here
  std::vector<int> v1{-curID, -childID};
  cnf.push_back(v1);

  std::vector<int> v2{curID, childID};
  cnf.push_back(v2);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID)
{
  // your code starts here
  std::vector<int> v1{-curID, leftID, rightID};
  cnf.push_back(v1);

  std::vector<int> v2{-leftID, curID};
  cnf.push_back(v2);

  std::vector<int> v3{-rightID, curID};
  cnf.push_back(v3);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID)
{
  // your code starts here
  std::vector<int> v1{-curID, leftID};
  cnf.push_back(v1);

  std::vector<int> v2{-curID, rightID};
  cnf.push_back(v2);

  std::vector<int> v3{-leftID, -rightID, curID};
  cnf.push_back(v3);
}

std::vector<std::vector<int>> TseitinTransformer::transform()
{
  // your code starts here
  cnf.clear();
  std::vector<int> v1{varIdCounter}; // varIdCounter = 1;
  cnf.push_back(v1);
  transSubformula(formulaRoot);

  return cnf;
}

std::string TseitinTransformer::cnfString() const
{
  std::string result = "";
  // your code starts here
  for (auto e : cnf)
  {
    std::vector<int>::iterator ptr;
    for (ptr = e.begin(); ptr < --(e.end()); ptr++)
    { 
      result += "(" + std::to_string(*ptr) + "+";
    }
    int i = e.size();
    --i;

    result += std::to_string(e.at(i)) + ")" + "*";
  }
  result.pop_back();
  //std::cout << result << std::endl;
  return result;
}

unsigned int TseitinTransformer::getVarNum() const
{
  // your code starts here
  return varIdCounter - 1;
}
