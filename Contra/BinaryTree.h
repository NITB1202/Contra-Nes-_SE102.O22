#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
#include "Map.h"

#define HORIZONTAL_BINARYTREE 111
#define VERTICAL_BINARYTREE 112

using namespace std;

class TreeNode
{
public:

	vector<LPGAMEOBJECT> object;
	
	int start;
	int end;

	TreeNode* left = NULL;
	TreeNode* right = NULL;

	TreeNode(int s, int e)
	{
		start = s;
		end = e;
	}

	bool InBound(float x) { return start <= x && x <= end; }
	void InsertObj(LPGAMEOBJECT obj) { object.push_back(obj); }
	vector<LPGAMEOBJECT> GetObj() { return object; }
	void GetBound(float& s,float& e) 
	{
		s = start;
		e = end;
	}
};

class BinaryTree
{
	int type;

	int mapBound;
	int scrBound;

	TreeNode* root;
	vector<LPGAMEOBJECT> currentObj;

	void CreateTree(vector<LPGAMEOBJECT> objList);
	void Insert(TreeNode* node, LPGAMEOBJECT object);
	TreeNode* FindNode(float start, float end);
	void GetObjectInSubTree(TreeNode* node, vector<LPGAMEOBJECT>& object);

public:

	BinaryTree(string objPath, LPMAP map, int type = HORIZONTAL_BINARYTREE);
	vector<LPGAMEOBJECT> GetObjectInBound(RECT bound);
	void Update(DWORD dt);
	void Render();
};
typedef BinaryTree* LPBINARYTREE;
