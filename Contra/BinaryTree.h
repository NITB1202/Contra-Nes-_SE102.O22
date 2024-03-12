#pragma once
#include "GameObject.h"

class TreeNode
{
public:

	vector<LPGAMEOBJECT> objects;
	
	int start;
	int end;

	TreeNode* left = NULL;
	TreeNode* right = NULL;

	TreeNode(int s, int e)
	{
		start = s;
		end = e;
	}

	bool InBound(int x) { return start <= x && x <= end; }
	void SetObj(LPGAMEOBJECT obj) { objects.push_back(obj); }

};

class BinaryTree
{

	int mapWidth;
	int scrWidth;

	TreeNode* root;

	TreeNode* CreateTree(float start, float end);
	void Travel(TreeNode* parent, LPGAMEOBJECT obj);

public:

	BinaryTree();
	void Init(vector<LPGAMEOBJECT> objList);
	vector<LPGAMEOBJECT> GetInScreenObject();

};
