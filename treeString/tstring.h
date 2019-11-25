#ifndef _TSTRING_H_
#define _TSTRING_H_
#include <string>
#include <iostream>

struct TNode;

struct TString {
	TString(const std::string &);
	TString(const TString & );        // copy constructor
	TString(TNode *root);
    ~TString();

    // Concatenate two TStrings, the returned TString should not have any
    // connection to the TStrings used to create it, that is no future changes
    // to the operands should effect the returned TString and vice versa
    TString operator+( const TString & ) const;

    // Index operator. 
    // NOTE: returns a char& so the user can modify the char
    // in that index of the string. This should be taken into consideration
    // when deciding what data to use in your class.
    // Requires index < size of string represented by our TString.
    char &operator[] (const unsigned int index);

    // Insert the string denoted by the std::string into this TString at the
    // location immediately following index.
    // Requires index < size of string represented by our TString.
    void insert(const std::string &, const unsigned int index);
    
    TNode *root;
    size_t length;
    // If you need to add any fields they MUST go after this line.
    // Do not change the order of the fields above.
};

// Print the string represented by our TString.
std::ostream& operator<<(std::ostream& out, const TString &t);
#endif


