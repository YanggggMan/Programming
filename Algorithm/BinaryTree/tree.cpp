#include "tree.h"


int new_cnt = 0;
int del_cnt = 0;

Tree::TreeNode::TreeNode():data(0),left(nullptr),right(nullptr) {
}

Tree::TreeNode::TreeNode(int _data) :data(_data),left(nullptr),right(nullptr)
{
	++new_cnt;
}

Tree::TreeNode::~TreeNode() {
	if (left != nullptr)
	{
		delete left;
		left = nullptr;
	}
	if (right != nullptr)
	{
		delete right;
		right = nullptr;
	}

	//delete this;  //cause a dead loop
	++del_cnt;
}

Tree::Tree():root(nullptr),len(0)
{
}

Tree::~Tree()
{
	if (root != nullptr)
	{
		clear();
	}
}

int Tree::Build(int first) {
	if (root != nullptr)
	{
		clear();
	}

	root = new TreeNode(first);
	++len;

	return 0;
}

int Tree::Build(vector<int> _data) {
	if (_data.empty())
	{
		return -1;
	}

	Build(*(_data.begin()));
	for (auto x = _data.begin() + 1; x != _data.end() ; ++x)
	{
		Insert(*x);
	}

	return 0;
}

void Tree::clear() {
	if (root != nullptr)
	{
		delete root;
		root = nullptr;
		len = 0;
	}
}

int Tree::Insert(int _data) {
	if (!empty())
	{
		auto node = &root;
		while ((*node) != nullptr)
		{
			if ((*node)->data > _data)
			{
				node = &((*node)->left);
			}
			else
			{
				node = &((*node)->right);
			}
		}
		(*node) = new TreeNode(_data);
		++len;
		return 0;
	}
	else {
		return -1;
	}
}

int Tree::length()const {
	return len;
}

bool Tree::empty()const {
	return len == 0;
}

void Tree::midShow(TreeNode* node) {
	if (node->left != nullptr)
	{
		midShow(node->left);
	}

	cout << "TreeNode: [" << node->data << "] " << endl;

	if (node->right != nullptr)
	{
		midShow(node->right);
	}
}

void Tree::show(int _type) {
	if (empty())
	{
		cout << "Tree  empty" << endl;
		return;
	}

	if (_type == 1)
	{
		midShow(root);
		return;
	}

	if (_type == 2)
	{
		midShow_s(root);
		return;
	}

	return;
}

void show_cnt() {
	cout << "New cnt [" << new_cnt << "] " << endl;
	cout << "Del cnt [" << del_cnt << "] " << endl;
}

void Tree::midShow_s(TreeNode* node) {
	stack<pair<TreeNode*, bool> > st;
	st.push(make_pair(node, 0));

	while (!st.empty()) {
		auto tmp = st.top();
		st.pop();

		if (tmp.second == 1)
		{
			cout << "TreeNode: [" << tmp.first->data << "] " << endl;
		}

		

		if (tmp.second == 0)
		{
			if (tmp.first->right != nullptr)
			{
				st.push(make_pair(tmp.first->right, 0));
			}

			tmp.second = 1;
			st.push(tmp);

			if (tmp.first->left != nullptr)
			{
				st.push(make_pair(tmp.first->left, 0));
			}
		}

		
	}
}
