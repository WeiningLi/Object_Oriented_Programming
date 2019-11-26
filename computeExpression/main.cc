#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "expression.h"
#include "derived.h"
using namespace std;

// You will need to write your own test harness

// Read and construct expression object. Returns a pointer to a heap-allocated
// object (caller must delete it).
istream &operator>>(istream &in, Expression *&e) {
  string s;
  vector<Expression*> stk;
  vector<Var>* info = new vector<Var>;
  while (in >> s) {
    istringstream ss(s);
    int n;
	bool existedVar = false;
	
	// integer object
    if (ss >> n) {
		Expression* ob = new Integer{ info, n };
		stk.emplace_back(ob);
    }
	// unary object
    else if (s == "NEG" || s == "ABS") {
		Expression* ob = new Unary{ info, s, stk[stk.size() - 1] };
		stk.pop_back();
		stk.emplace_back(ob);
    }
	// binary object
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
		Expression* ob = new Binary{ info, s, stk[stk.size() - 2], stk[stk.size() - 1] };
		stk.pop_back();
		stk.pop_back();
		stk.emplace_back(ob);
    }
	// end
    else if (s == "done") {
		e = stk.at(stk.size() - 1);
		break;
    }
	// variable object
    else {
		Expression* ob = new Variable{ info, s };
		stk.emplace_back(ob);
		existedVar = false;
		for (size_t i = 0; i < (*info).size(); ++i) {
			if ((*info)[i].name == s) existedVar = true;
		}
		if (!existedVar) {
			(*info).emplace_back(Var{ s, 0, false });
		}
    }
  }
  return in;
}

int main () {
  string s;

  Expression *e;
  cin >> e;
  string init = (*e).prettyprint();
  cout << init << endl;

  // Command interpreter
  while (cin >> s) {
    if (s == "eval") {
		try {
			int num = (*e).evaluate();
			cout << num << endl;
		}
		catch (string s) {
			cout << s << endl;
			continue;
		}
    }
	else if (s == "copy") {
		vector<Var>* copyInfo = (*e).getVarCopy();
		Expression *theCopy = (*e).makeCopy(copyInfo);
		cout << theCopy->prettyprint() << endl;
		theCopy->set(1, "x");
		cout << theCopy->prettyprint() << endl;
		try {
			int num = theCopy->evaluate();
			cout << num << endl;
			delete copyInfo;
			delete theCopy;
		}
		catch (string s) {
			cout << s << endl;
			delete copyInfo;
			delete theCopy;
			continue;
		}
	}
    else if (s == "set") {
		string name;
		int value;
		cin >> name;
		cin >> value;
		(*e).set(value, name);
    }
    else if (s == "unset") {
		string name;
		cin >> name;
		(*e).unset(name);
    }
    else if (s == "print") {
		string s = (*e).prettyprint();
		cout << s << endl;
    }
  }
  // clean varinfo 
  (*e).clean();
  // free expressions
  delete e;
}

