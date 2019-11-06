#include <iostream>
#include <string>
#include <exception>
#include <conio.h>

enum Side {UNKNOWN, LEFT, RIGHT};

class BinTreeNode
{
	BinTreeNode* left;
	BinTreeNode* right;
public:
	int val;
	BinTreeNode(int val = 0) : val(val) { left = nullptr; right = nullptr; }
	~BinTreeNode();
	BinTreeNode* getLeftChild() { return left; }
	BinTreeNode* getRightChild() { return right; }
	void addNode(int i, Side side);
};

void BinTreeNode::addNode(int val, Side side = UNKNOWN)
{
	if (side == LEFT) BinTreeNode::left = new BinTreeNode(val);
	if (side == RIGHT) BinTreeNode::right = new BinTreeNode(val);
}

BinTreeNode::~BinTreeNode()
{
	if (BinTreeNode::left) delete BinTreeNode::left;
	if (BinTreeNode::right) delete BinTreeNode::right;
}

class InorderTreeNode : public BinTreeNode
{
public:
	InorderTreeNode(int val) : BinTreeNode(val) {}
};

std::ostream& operator<< (std::ostream &ostr, InorderTreeNode* node)
{
	InorderTreeNode* left = static_cast<InorderTreeNode *>(node->getLeftChild());
	InorderTreeNode* right = static_cast<InorderTreeNode *>(node->getRightChild());
	if (left) ostr << left;
	ostr << " " << node->val;
	if (right) ostr << right;
	return ostr;
}

class PostorderTreeNode : public BinTreeNode
{
public:
	PostorderTreeNode(int val) : BinTreeNode(val) {}
};

std::ostream& operator<< (std::ostream &ostr, PostorderTreeNode* node)
{
	PostorderTreeNode* left = static_cast<PostorderTreeNode *>(node->getLeftChild());
	PostorderTreeNode* right = static_cast<PostorderTreeNode *>(node->getRightChild());
	if (left) ostr << left;
	if (right) ostr << right;
	return ostr << " " << node->val;
}

class PreorderTreeNode : public BinTreeNode
{
public:
	PreorderTreeNode(int val) : BinTreeNode(val) {}
};

std::ostream& operator<< (std::ostream &ostr, PreorderTreeNode* node)
{
	PreorderTreeNode* left = static_cast<PreorderTreeNode *>(node->getLeftChild());
	PreorderTreeNode* right = static_cast<PreorderTreeNode *>(node->getRightChild());
	ostr << " " << node->val;
	if (left) ostr << left;
	if (right) ostr << right;
	return ostr;
}

int main()
{
	BinTreeNode *root = new BinTreeNode(1);
	root->addNode(2, LEFT);
	root->addNode(3, RIGHT);
	BinTreeNode *last = root->getLeftChild();
	last->addNode(4, LEFT);
	last->addNode(5, RIGHT);
	last = last->getRightChild();
	last->addNode(7, LEFT);
	last = root->getRightChild();
	last->addNode(6, RIGHT);

	std::cout << "Inorder:" << static_cast<InorderTreeNode *>(root) << std::endl;
	std::cout << "Postorder:" << static_cast<PostorderTreeNode *>(root) << std::endl;
	std::cout << "Preorder:" << static_cast<PreorderTreeNode *>(root) << std::endl;

	delete root;
	_getch();
	return 0;
}