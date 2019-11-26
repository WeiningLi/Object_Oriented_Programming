#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>
#include <string>

struct Var {
	std::string name;
	int val;
	bool isSet;
};

//abstruct

class Expression {
protected:
	std::vector<Var>* varInfo;
public:
	Expression(std::vector<Var>* varInfo);
	virtual std::vector<Var>* getVarCopy() = 0;
	virtual Expression* makeCopy(std::vector<Var>*) = 0;
	virtual std::string prettyprint() = 0;
	virtual void set(int, std::string) = 0;
	virtual void unset(std::string) = 0;
	virtual int evaluate() = 0;
	virtual void clean() = 0;
	virtual ~Expression() = 0;
};

#endif
