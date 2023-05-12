#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include "tokenizer.cc"
#include "treeNode.cc"

FormulaParser::FormulaParser(std::string F_ln) {
  tknzr = new Tokenizer(F_ln);
  tkVect = tknzr->getTokens();
}

TreeNode *FormulaParser::parseConjTerm()
{

  // your code starts here
  TreeNode *tNode1;
  
  tNode1 = FormulaParser::parseTerm();
  while(i < tkVect.size()){
    if(tkVect[i].content != "*") {
      break;
    }
    if(tkVect[i].content == "*" ){
      OperatorNode* andoperator = new OperatorNode(tkVect[i].content);
      i++;
      andoperator->updateChildren(tNode1,FormulaParser::parseConjTerm());
      return andoperator;
    }

  }
  return tNode1;
}

TreeNode *FormulaParser::parseTerm()
{
  TreeNode *tNode1;
  // your code starts here
  while(i < tkVect.size()) {
    if(tkVect[i].content == "(") {
      int closePos = FormulaParser::findClosingParen(tkVect, i);
      i++;
      tNode1 = parseFormula();
      i= closePos + 1;
      return tNode1;
    }
    if(tkVect[i].type == "constant") {
      ConstantNode* constantnode = new ConstantNode(tkVect[i].content);
      i++;
      return constantnode;
    }
    if(tkVect[i].type == "variable") {
      VariableNode* variablenode = new VariableNode(tkVect[i].content);
      i++;
      return variablenode;
    }
    if(tkVect[i].content == "-") {
      OperatorNode* operatornode = new OperatorNode(tkVect[i].content);
      i++;
      tNode1 = FormulaParser::parseTerm();
      operatornode->updateLeftChild(tNode1);
      return operatornode;
    }
  }
  
  return nullptr;
}

TreeNode *FormulaParser::parseFormula()
{
  // your code starts here
  TreeNode *tNode1;
  
  tNode1 = FormulaParser::parseConjTerm();
  while(i < tkVect.size()){
    if(tkVect[i].content != "+") {
      break;
    }
    if(tkVect[i].content == "+" ){
      OperatorNode* plusoperator = new OperatorNode(tkVect[i].content);
      i++;
      plusoperator->updateChildren(tNode1,FormulaParser::parseFormula());
      return plusoperator;
    }
  }
  return tNode1;

}

TreeNode *FormulaParser::getTreeRoot()
{
  // your code starts here
  TreeNode *root = FormulaParser::parseFormula();
  return root;
}

int FormulaParser::findClosingParen(vector<Token> vectTok, int openPos) {
  int closePos = openPos;
    int counter = 1;
    while (counter > 0) {
        string c = vectTok[++closePos].content;
        if (c == "(") {
            counter++;
        }
        else if (c == ")") {
            counter--;
        }
    }
    return closePos;
}


AssignmentParser::AssignmentParser(string A_ln) {
  tknzr = new Tokenizer(A_ln);
  }

map<string, bool> AssignmentParser::parseAssignment()
{
  map<string, bool> results;
  // your code starts here
  vector<Token> tkVect;
  tkVect = tknzr->getTokens();
  //cout<<tkVect.size()<<endl;
  int i = 0;
  while (i < tkVect.size())
  {
    if (tkVect[i].type == "variable")
    {
      string varName = tkVect[i].content;
      string content = tkVect[i + 2].content;
      if (content == "1") {
        results.insert(pair<string, bool>(varName, true));
      }
      else if( content == "0") {
        results.insert(pair<string, bool>(varName, false));
      }
    }
    i++;
  }
  return results;
}
