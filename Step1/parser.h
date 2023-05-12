#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    Tokenizer *tknzr;
    
    TreeNode *parseFormula(); // parse non-terminal Formula in the grammar
    TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
    TreeNode *parseTerm(); // parse non-terminal Term in the grammar
  public:
    int i = 0;
    std::vector<Token> tkVect;
    FormulaParser(std::string ln);
    TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
    int findClosingParen(std::vector<Token> vectTok, int openPos);
};

// Parser for the Assignment
class AssignmentParser {
    Tokenizer *tknzr;
  public:
    AssignmentParser(std::string ln);
    std::map<std::string, bool> parseAssignment();
};

#endif
