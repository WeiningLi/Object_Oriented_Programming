#ifndef _TNODE_H_
#define _TNODE_H_
struct TNode {
    std::string data;
    TNode *left, *right;
    // Size of the string represented by this node's left subtree, plus its own
    // string's data size.
    size_t size;
    // If you need to add any fields they MUST go after this line.
    // Do not change the order of the fields above.
	TNode(std::string data, size_t size, TNode *left, TNode *right);
	TNode(const TNode & other);
	~TNode();
	TNode & operator= (const TNode & other);
};
#endif


