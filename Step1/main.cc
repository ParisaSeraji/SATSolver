#include <stack>
#include <regex>
#include "parser.h"
#include "treeNode.h"
#include "parser.cc"

using namespace std;

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const string &line, string &formulaStr, string &assignmentStr)
{
  // your code starts here
  
  vector<Token> resultTokens_F, resultTokens_A;

  Tokenizer tkFormula(formulaStr);
  resultTokens_F = tkFormula.getTokens();
  FormulaParser FParser(formulaStr);
  
  TreeNode *node = FParser.getTreeRoot();
  
  node->inorder(node);

  Tokenizer tkAssignment(assignmentStr);
  resultTokens_A = tkAssignment.getTokens();

  AssignmentParser AParser(assignmentStr);
  map<string, bool> M = AParser.parseAssignment();

  bool bResult = node->eval(node, M);
  cout << bResult << endl;
}

// Checking for the balanced parentheses:
bool ArePair(char opening, char closing)
{
  if (opening == '(' && closing == ')')
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool AreParenthesisBalanced(const string &exp)
{
  stack<char> s;
  for (int i = 0; i < exp.length(); i++)
  {
    if (exp[i] == '(')
    {
      s.push(exp[i]);
    }
    else if (exp[i] == ')')
    {
      if (s.empty() || !ArePair(s.top(), exp[i]))
      {
        return false;
      }
      else
      {
        s.pop();
      }
    }
  }
  return s.empty() ? true : false;
}


int errors(const string &line, string &formulaStr, string &assignmentStr) {
  int errNum = 0;
  int opNum = 0;
  auto it = line.find(';');
  if(it == string::npos){
    cout << "Error: invalid input!" << endl;
    errNum++;
  }
  // more than 1 ";" error
  int counter = 0;
  for(int i = 0; i < line.size(); i++) {
    if(line[i] == ';') {
      counter++;
    }
  }
  if(counter > 1) {
    cout << "Error: invalid input!" << endl;
    errNum++;
  }

  vector<Token> resultTokens_F, resultTokens_A;
  Tokenizer tkFormula(formulaStr);
  resultTokens_F = tkFormula.getTokens();

  for(int i = 0; i < resultTokens_F.size(); i++) {
    if(resultTokens_F[i].content == "*" || resultTokens_F[i].content == "+") {
      opNum++;
    }

    if(resultTokens_F[i].type == "variable") {
      if(resultTokens_F[i].content.size() > 10) {
        cout << "Error: invalid input! " << endl;
        errNum++;
      }
      string var = resultTokens_F[i].content;
      regex e7("[a-zA-Z]+[0-9]*");
      bool match7 = regex_match(var, e7);
      if(!match7) {
        cout << "Error: invalid input!" << endl;
        errNum++;
      }
      
    }

    //wrong constant in formulaStr
    regex e2("[2-9]|[0-9]{2,}");
    bool match2 = regex_match(resultTokens_F[i].content, e2);
    if(match2) {
      cout << "Error: invalid input!" << endl;
      errNum++;
    }

    //wrong inpput after * or +
    regex e5("0|1|[a-zA-Z]+[0-9]*|\\(|\\-");
    if(resultTokens_F[i].content == "*" || resultTokens_F[i].content == "+") {
      if( i == resultTokens_F.size() - 1) {
        cout << "Error: invalid input!" << endl;
        errNum++;
      }
      else if(i < (resultTokens_F.size() - 1)) {
        bool match5 = regex_match(resultTokens_F[i+1].content, e5);
        if(!match5) {
          cout << "Error: invalid input!" << endl;
          errNum++;
        }
      }
    }

    //wrong input after -
    regex e6("0|1|[a-zA-Z]+[0-9]*|\\(|\\-");
    if(resultTokens_F[i].content == "-") {
      if( i == resultTokens_F.size() - 1) {
        cout << "Error: invalid input!" << endl;
        errNum++;
      }
      else if(i < (resultTokens_F.size() - 1)) {
        bool match6 = regex_match(resultTokens_F[i+1].content, e6);
        if(!match6) {
          cout << "Error: invalid input!" << endl;
          errNum++;
        }
      }
    }


  }

  if(opNum == 0) {
    cout << "Error: invalid input!" << endl;
    errNum++;
  }

  //no assinment part
  if(assignmentStr.size() == 0) {
    for(int i = 0; i < resultTokens_F.size(); i++) {
      if(resultTokens_F[i].type == "variable") {
        cout << "Error: incomplete assignment!" << endl;
        errNum++;
      }
    }
  }
  

  Tokenizer tkAssignment(assignmentStr);
  resultTokens_A = tkAssignment.getTokens();
  for(int i = 0; i < resultTokens_A.size(); i++){
    //Variable without symbol ":" after that
    if(resultTokens_A[i].type == "variable") {
      if(resultTokens_A[i+1].content != ":") {
        cout << "Error: invalid input!" << endl;
        errNum++;
      }
    }

    //symbol ":" without constant after that
    if(resultTokens_A[i].type == "symbol") {
      if(resultTokens_A[i].content == ":") {
        if(resultTokens_A[i+1].type != "constant") {
          cout << "Error: incomplete assignment!" << endl;
          errNum++;
        }
      }
    }

    //wrong constant in assignmentStr
    regex e3("[2-9]|[0-9]{2,}");
    bool match3 = regex_match(resultTokens_A[i].content, e3);
    if(match3) {
      cout << "Error: invalid input!" << endl;
      errNum++;
    }

    //assinments without separating symbol","
    if(i+1 < (resultTokens_A.size() - 1)) {
      if(resultTokens_A[i].type == "constant" && resultTokens_A[i+1].content != ",") {
        cout << "Error: invalid input!" << endl;
        errNum++;
      }
    }  

    //assinments without separating symbol","
    if(resultTokens_A[i].type == "variable") {
      string var = resultTokens_A[i].content;
      regex e4("[0-9]+[a-zA-Z0-9]+|[0-9]");
      bool match4 = regex_match(var, e4);
      if(match4) {
        cout << "Error: invalid input!" << endl;
        errNum++;
      }
    }
    
    //contradicting assignment
    int c = 1;
    if(resultTokens_A[i].type == "variable") {
      for(int j = i + 1; j < resultTokens_A.size(); j++){
        if(resultTokens_A[j].content == resultTokens_A[i].content && resultTokens_A[j+2].content != resultTokens_A[i+2].content){
          c++;
        }
      }
    }
    if(c > 1) {
      cout << "Error: contradicting assignment!" << endl;
      errNum++;
    }


  }

  return errNum;
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main()
{
  while (cin) // continuously asking for new inputs from standard input
  {
    string line;          // store each input line
    string formulaStr;    // store the formula string
    string assignmentStr; // store the assignment string
    int err = 0;
    getline(cin, line);
    stringstream ss(line);
    getline(ss, formulaStr, ';');
    
    getline(ss, assignmentStr);
    

    if (!AreParenthesisBalanced(line))
    {
      cout << "Error: invalid input!" << endl;
      err++;
    }

    err += errors(line, formulaStr, assignmentStr);
    
    if(err == 0) {
      parseLine(line, formulaStr, assignmentStr);
    }
    
  }

  return 0;
}
