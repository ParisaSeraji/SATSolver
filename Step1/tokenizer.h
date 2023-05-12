#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>


struct Token
{
  std::string content;
  std::string type;
};

// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
  // your code starts here
private:
  const std::string delim = " ,;:()+-=*";
  std::string str;
  Token resultToken;
  std::vector<Token> resultVector;

public:
  Tokenizer(std::string std);
  void tokenizer();
  std::vector<Token> getTokens(); // returns the token being processed
};

#endif
