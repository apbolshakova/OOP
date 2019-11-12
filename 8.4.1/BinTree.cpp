#include <iostream>
#include <string>
#include <exception>
#include <conio.h>

class InorderTreeNode;
class PreorderTreeNode;
class PostorderTreeNode;

class BinTreeNode
{
public:
	int val;
	BinTreeNode* left;
	BinTreeNode* right;
	BinTreeNode(int val = 0) : val(val)
	{
		left = nullptr;
		right = nullptr;
	}
	~BinTreeNode()
	{
		if (left) delete left;
		if (right) delete right;
	}
	void addNode(int val, BinTreeNode *x);
};

void BinTreeNode::addNode(int val, BinTreeNode *x = nullptr)
{
	if (!x) x = this;
	if (val < x->val)
	{
		if (x->left) addNode(val, x->left);
		else x->left = new BinTreeNode(val);
	}
	else
	{
		if (x->right) addNode(val, x->right);
		else x->right = new BinTreeNode(val);
	}
}

void traverse(InorderTreeNode *node, int& count, int& val);
void traverse(PostorderTreeNode *node, int& count, int& val);
void traverse(PreorderTreeNode *node, int& count, int& val);

class InorderTreeNode : public BinTreeNode
{
public:
	InorderTreeNode(int val) : BinTreeNode(val) {};
	int &operator[](int count)
	{
		count++;
		InorderTreeNode* root = this;
		int val = -1;
		traverse(root, count, val);
		return val;
	}
};

void traverse(InorderTreeNode *node, int& count, int& val)
{
	InorderTreeNode* left = static_cast<InorderTreeNode *>(node->left);
	InorderTreeNode* right = static_cast<InorderTreeNode *>(node->right);
	
	if (left) traverse(left, count, val);
	if (!count) return;

	count--;
	if (!count)
	{
		val = node->val;
		return;
	}

	if (right) traverse(right, count, val);
}

std::ostream& operator<< (std::ostream &ostr, InorderTreeNode* node)
{
	InorderTreeNode* left = static_cast<InorderTreeNode *>(node->left);
	InorderTreeNode* right = static_cast<InorderTreeNode *>(node->right);
	if (left) ostr << left;
	ostr << " " << node->val;
	if (right) ostr << right;
	return ostr;
}

class PostorderTreeNode : public BinTreeNode
{
public:
	PostorderTreeNode(int val) : BinTreeNode(val) {}
	int &operator[](int count)
	{
		count++;
		PostorderTreeNode* root = this;
		int val = -1;
		traverse(root, count, val);
		return val;
	}
};

void traverse(PostorderTreeNode *node, int& count, int& val)
{
	PostorderTreeNode* left = static_cast<PostorderTreeNode *>(node->left);
	PostorderTreeNode* right = static_cast<PostorderTreeNode *>(node->right);

	if (left) traverse(left, count, val);
	if (!count) return;

	if (right) traverse(right, count, val);
	if (!count) return;

	count--;
	if (!count) val = node->val;
}

std::ostream& operator<< (std::ostream &ostr, PostorderTreeNode* node)
{
	PostorderTreeNode* left = static_cast<PostorderTreeNode *>(node->left);
	PostorderTreeNode* right = static_cast<PostorderTreeNode *>(node->right);
	if (left) ostr << left;
	if (right) ostr << right;
	return ostr << " " << node->val;
}

class PreorderTreeNode : public BinTreeNode
{
public:
	PreorderTreeNode(int val) : BinTreeNode(val) {}
	int &operator[](int count)
	{
		count++;
		PreorderTreeNode* root = this;
		int val = -1;
		traverse(root, count, val);
		return val;
	}
};

void traverse(PreorderTreeNode *node, int& count, int& val)
{
	PostorderTreeNode* left = static_cast<PostorderTreeNode *>(node->left);
	PostorderTreeNode* right = static_cast<PostorderTreeNode *>(node->right);

	count--;
	if (!count) val = node->val;
	
	if (left) traverse(left, count, val);
	if (!count) return;

	if (right) traverse(right, count, val);
}

std::ostream& operator<< (std::ostream &ostr, PreorderTreeNode* node)
{
	PreorderTreeNode* left = static_cast<PreorderTreeNode *>(node->left);
	PreorderTreeNode* right = static_cast<PreorderTreeNode *>(node->right);
	ostr << " " << node->val;
	if (left) ostr << left;
	if (right) ostr << right;
	return ostr;
}

void removeHandledVals(std::string &input)
{
	if (input.find(" ") != std::string::npos) input.erase(0, input.find(" ") + 1);
	else input.clear();
}

int main()
{
	std::string input = "";
	std::getline(std::cin, input, '\n');
	int val;
	try { val = std::stoi(input); }
	catch (...)
	{
		std::cout << "Invalid input";
		_getch();
		return 0;

	}
	BinTreeNode* root = new BinTreeNode(val);
	removeHandledVals(input);
	while (!input.empty())
	{
		try { val = std::stoi(input); }
		catch (...) { break; }
		val = std::stoi(input);
		root->addNode(val);
		removeHandledVals(input);
	}

	std::cout << "Inorder:" << static_cast<InorderTreeNode *>(root) << std::endl;
	std::cout << "Postorder:" << static_cast<PostorderTreeNode *>(root) << std::endl;
	std::cout << "Preorder:" << static_cast<PreorderTreeNode *>(root) << std::endl;

	std::cout << "Second from inorder: " << (*static_cast<InorderTreeNode *>(root))[1] << std::endl;
	std::cout << "Second from postorder: " << (*static_cast<PostorderTreeNode *>(root))[1] << std::endl;
	std::cout << "Second from preorder: " << (*static_cast<PreorderTreeNode *>(root))[1] << std::endl;

	_getch();
	return 0;
}