#include <vector>
#include <string>
#include "expression.h"
using namespace std;

//ctor
Expression::Expression(vector<Var>* varInfo) : varInfo{ varInfo } {}

//dtor
Expression::~Expression() {}

