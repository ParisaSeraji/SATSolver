#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

#include <iostream>
#include <memory>

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf)
{
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

  // creating a vector for creating clauses of unknown literal size
  //Minisat::vec<Minisat::Lit> LitVec;
  Minisat::Lit LitVec[numVar];
  for (unsigned int i = 0; i < numVar; i++)
  {
    Minisat::Lit literal = Minisat::mkLit(solver->newVar());
    LitVec[i] = literal;
  }
  for (auto e : cnf)
  {
    int i;
    Minisat::vec<Minisat::Lit> innerVec;
    for (long unsigned int j = 0; j < e.size(); j++)
    {
      i = abs(e.at(j));
      if (e.at(j) < 0)
      {
        innerVec.push(~LitVec[i - 1]);
      }
      else
      {
        innerVec.push(LitVec[i - 1]);
      }
    }
    solver->addClause(innerVec);
  }

  bool res = solver->solve();
  //std::cout << "The result is: " << res << "\n";

  // Reset the solver object to find satisfiability
  //solver.reset(new Minisat::Solver());

  return res;
}
