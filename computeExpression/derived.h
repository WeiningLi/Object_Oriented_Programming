#ifndef DERIVE_H
#define DERIVE_H
#include <iostream>
#include <vector>
#include <string>
#include "expression.h"

// integer interface
class Integer: public Expression {
	int loneInt;
public:
	Integer(std::vector<Var>*, int);
	std::string prettyprint();
	void set(int, std::string);
	void unset(std::string);
	int evaluate();
	void clean();
	~Integer();
	std::vector<Var>* getVarCopy();
	Expression* makeCopy(std::vector<Var>*);
};

// variable interface
class Variable : public Expression {
	std::string name;
public:
	Variable(std::vector<Var>*, std::string);
	std::string prettyprint();
	void set(int, std::string);
	void unset(std::string);
	int evaluate();
	void clean();
	~Variable();
	std::vector<Var>* getVarCopy();
	Expression* makeCopy(std::vector<Var>*);
};

// unary interface
class Unary : public Expression {
	std::string unop;
	Expression *exp;
public:
	Unary(std::vector<Var>*, std::string, Expression *);
	std::string prettyprint();
	void set(int, std::string);
	void unset(std::string);
	int evaluate();
	void clean();
	~Unary();
	std::vector<Var>* getVarCopy();
	Expression* makeCopy(std::vector<Var>*);
};

// binary interface
class Binary : public Expression {
	std::string binop;
	Expression *leftExp;
	Expression *rightExp;
public:
	Binary(std::vector<Var>*, std::string, Expression *, Expression *);
	std::string prettyprint();
	void set(int, std::string);
	void unset(std::string);
	int evaluate();
	void clean();
	~Binary();
	std::vector<Var>* getVarCopy();
	Expression* makeCopy(std::vector<Var>*);
};

#endif

