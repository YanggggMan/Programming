#pragma once
#include <iostream>
#include<vector>
#include <stack>
using namespace std;

extern int new_cnt;
extern int del_cnt;


class Tree
{
private:
	struct TreeNode
	{
		int data;
		TreeNode *left;
		TreeNode *right;

		TreeNode();
		TreeNode(int);
		~TreeNode();
	};

public:
	typedef TreeNode* pNode;

	Tree();
	~Tree();

	int Build(int first);
	int Build(vector<int>);
	int Insert();
	int Insert(int _data);
	int Remove(TreeNode *);
	int find(int _data);
	int length()const;
	void clear();
	bool empty()const;
	void show(int type);
	void midShow(TreeNode*);
	void midShow_s(TreeNode*);
private:
	TreeNode* root;
	size_t len;
};

void show_cnt();