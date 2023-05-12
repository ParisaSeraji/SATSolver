#include "tokenizer.h"

using namespace std;

Tokenizer::Tokenizer(string str)
{
  this->str = str;
  Tokenizer::tokenizer();
}

void Tokenizer::tokenizer()
{
  string word = "", s;
  stringstream ss;

  for (auto x : str)
  {
    if (x == delim[0] || x == delim[1] || x == delim[2] || x == delim[3] || x == delim[4] || x == delim[5] || x == delim[6] || x == delim[7] || x == delim[8] || x == delim[9])
    {

      if (word != "")
      {

        resultToken.content = word;
        if (64 < int(word[0]) < 91 || 96 < int(word[0]) < 123)
        {

          resultToken.type = "variable";
        }
        if (word == "0" || word == "1")
        {

          resultToken.type = "constant";
        }
        
        resultVector.push_back(resultToken);
      }

      word = "";
      if (x == delim[1] || x == delim[2] || x == delim[3] || x == delim[4] || x == delim[5])
      {

        resultToken.type = "symbol";
        ss << x;
        s = ss.str();

        resultToken.content = s;
        ss.clear();
        ss.str("");
        
        resultVector.push_back(resultToken);
      }
      else if (x == delim[0])
      {
        continue;
      }
      else
      {

        resultToken.type = "operator";
        ss << x;
        s = ss.str();

        resultToken.content = s;
        ss.clear();
        ss.str("");
        
        resultVector.push_back(resultToken);
      }
    }

    else
    {
      word = word + x;
    }
  }

  if (word != "")
  {

    resultToken.content = word;
    if (word == "0" || word == "1")
    {

      resultToken.type = "constant";
    }
    else
    {
      if (64 < int(word[0]) < 91 || 96 < int(word[0]) < 123)
      {

        resultToken.type = "variable";
      }
    }
    
    resultVector.push_back(resultToken);
  }

  
}

vector<Token> Tokenizer::getTokens()
{
  return this->resultVector;
}

