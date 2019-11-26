#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include "expression.h"
#include "derived.h"
using namespace std;

// integer methods

Integer::Integer(vector<Var>* varInfo, int loneInt) : Expression{ varInfo }, loneInt{ loneInt } {}
string Integer::prettyprint() {
	stringstream ss;
	ss << loneInt;
	return ss.str();
}

void Integer::set(int val, string name) {}

void Integer::unset(string name) {}

int Integer::evaluate() { return loneInt; }

void Integer::clean() {
	delete varInfo;
}

Integer::~Integer() {
}

vector<Var>* Integer::getVarCopy() {
	vector<Var>* copy = new vector<Var>;
	for (size_t i = 0; i < varInfo->size(); ++i) {
		(*copy).emplace_back(Var{ (*varInfo)[i].name, (*varInfo)[i].val, (*varInfo)[i].isSet });
	}
	return copy;
}

Expression* Integer::makeCopy(vector<Var>* copyInfo) {
	Expression* ob = new Integer{ copyInfo, loneInt };
	return ob;
}

// variable methods

Variable::Variable(vector<Var>* varInfo, string name) : Expression{ varInfo }, name{ name } {}
string Variable::prettyprint() {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if ((*varInfo)[i].name == name) {
			if ((*varInfo)[i].isSet) {
				stringstream ss;
				ss << (*varInfo)[i].val;
				return ss.str();
			}
			else return name;
		}
	}
}

void Variable::set(int value, string varName) {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if ((*varInfo)[i].name == varName) {
			(*varInfo)[i].isSet = true;
			(*varInfo)[i].val = value;
			break;
		}
	}
}

void Variable::unset(string varName) {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if ((*varInfo)[i].name == varName) {
			(*varInfo)[i].isSet = false;
			break;
		}
	}
}

int Variable::evaluate() {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if (!((*varInfo)[i].isSet)) {
			throw (*varInfo)[i].name + " has no value.";
		}
	}
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if (((*varInfo)[i].name == name)) {
			return (*varInfo)[i].val;
		}
	}
}

void Variable::clean() {
	delete varInfo;
}

Variable::~Variable() {}

vector<Var>* Variable::getVarCopy() {
	vector<Var>* copy = new vector<Var>;
	for (size_t i = 0; i < varInfo->size(); ++i) {
		(*copy).emplace_back(Var{ (*varInfo)[i].name, (*varInfo)[i].val, (*varInfo)[i].isSet });
	}
	return copy;
}

Expression* Variable::makeCopy(vector<Var>* copyInfo) {
	Expression* ob = new Variable{ copyInfo, name };
	return ob;
}

// unary methods

Unary::Unary(vector<Var>* varInfo, string unop, Expression *exp) : Expression{ varInfo }, unop{ unop }, exp{ exp } {}
string Unary::prettyprint() {
	if (unop == "NEG") {
		return "-" + (*exp).prettyprint();
	}
	else if (unop == "ABS") {
		return "|" + (*exp).prettyprint() + "|";
	}
}

void Unary::set(int value, string varName) {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if ((*varInfo)[i].name == varName) {
			(*varInfo)[i].isSet = true;
			(*varInfo)[i].val = value;
			break;
		}
	}
}

void Unary::unset(string varName) {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if ((*varInfo)[i].name == varName) {
			(*varInfo)[i].isSet = false;
			break;
		}
	}
}

int Unary::evaluate() {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if (!((*varInfo)[i].isSet)) {
			throw (*varInfo)[i].name + " has no value.";
		}
	}
	if (unop == "NEG") {
		return -1 * (*exp).evaluate();
	}
	else if (unop == "ABS") {
		if ((*exp).evaluate() > 0) return (*exp).evaluate();
		else return -1 * (*exp).evaluate();
	}
}

void Unary::clean() {
	delete varInfo;
}

vector<Var>* Unary::getVarCopy() {
	vector<Var>* copy = new vector<Var>;
	for (size_t i = 0; i < varInfo->size(); ++i) {
		(*copy).emplace_back(Var{ (*varInfo)[i].name, (*varInfo)[i].val, (*varInfo)[i].isSet });
	}
	return copy;
}

Unary::~Unary() { 
	delete exp;
}

Expression* Unary::makeCopy(vector<Var>* copyInfo) {
	Expression* ob = new Unary{ copyInfo, unop, (*exp).makeCopy(copyInfo) };
	return ob;
}

// binary methods

Binary::Binary(vector<Var>* varInfo, string binop, Expression *leftExp, Expression *rightExp) : Expression{ varInfo }, binop{ binop }, leftExp{ leftExp }, rightExp{ rightExp } {}
string Binary::prettyprint() {
	return "(" + (*leftExp).prettyprint() + " " + binop + " " + (*rightExp).prettyprint() + ")";
}

void Binary::set(int value, string varName) {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if ((*varInfo)[i].name == varName) {
			(*varInfo)[i].isSet = true;
			(*varInfo)[i].val = value;
			break;
		}
	}
}

void Binary::unset(string varName) {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if ((*varInfo)[i].name == varName) {
			(*varInfo)[i].isSet = false;
			break;
		}
	}
}

int Binary::evaluate() {
	for (size_t i = 0; i < (*varInfo).size(); ++i) {
		if (!((*varInfo)[i].isSet)) {
			throw (*varInfo)[i].name + " has no value.";
		}
	}
	if (binop == "+") {
		return (*leftExp).evaluate() + (*rightExp).evaluate();
	}
	else if (binop == "-") {
		return (*leftExp).evaluate() - (*rightExp).evaluate();
	}
	else if (binop == "*") {
		return (*leftExp).evaluate() * (*rightExp).evaluate();
	}
	else if (binop == "/") {
		return (*leftExp).evaluate() / (*rightExp).evaluate();
	}
}

void Binary::clean() {
	delete varInfo;
}

Binary::~Binary() { 
	delete leftExp;
	delete rightExp;
}

vector<Var>* Binary::getVarCopy() {
	vector<Var>* copy = new vector<Var>;
	for (size_t i = 0; i < varInfo->size(); ++i) {
		(*copy).emplace_back(Var{ (*varInfo)[i].name, (*varInfo)[i].val, (*varInfo)[i].isSet });
	}
	return copy;
}

Expression* Binary::makeCopy(vector<Var>* copyInfo) {
	Expression* ob = new Binary{ copyInfo, binop, (*leftExp).makeCopy(copyInfo), (*rightExp).makeCopy(copyInfo) };
	return ob;
}

