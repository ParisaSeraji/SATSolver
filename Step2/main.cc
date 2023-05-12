#include "tseitinTransformer.h"
#include "satSolver.h"
#include <iostream>
#include <string>
#include <map>
#include "parser.h"
//#include "parser.cc"
#include "treeNode.h"

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    // your code starts here
    std::getline(std::cin, line);
    if (std::cin.eof()) break; // terminate gracefully encountering eof
    try {
      int scPos = line.find(";");
      if (scPos != -1) throw "Error: invalid input";
    } catch (const char *e) {
      std::cout << e << std::endl;
      continue;
    }
    FormulaParser fParser{line};
    TreeNode *treeRoot = nullptr;
    try {
      treeRoot = fParser.getTreeRoot();
      //std::map<std::string, bool> assignment = aParser.parseAssignment();
      //bool result = treeRoot->evaluate(assignment);
      TseitinTransformer transformer(treeRoot);
      std::vector<std::vector<int>> cnf;
      cnf = transformer.transform();
      //std::string cnfRes = transformer.cnfString();
      //std::cout << cnfRes << std::endl;
      unsigned int varNum = transformer.getVarNum();
      bool miniSatResult = satCallingMiniSat(varNum, cnf);
      std::cout << (miniSatResult ? "sat" : "unsat") << std::endl;
      //std::cout << miniSatResult << std::endl;
    } catch (const char *e) {
      delete treeRoot;
      std::cout << e << std::endl;
      continue;
    }
    delete treeRoot;
  }
}
