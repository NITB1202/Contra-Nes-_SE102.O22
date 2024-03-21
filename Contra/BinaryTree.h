#pragma once
#include <string>
#include <map>
#include "GameObject.h"
#include "Map.h"


#define HORIZONTAL_BINARYTREE 111
#define VERTICAL_BINARYTREE 112

using namespace std;

class TreeNode
{
public:

	map<int, LPGAMEOBJECT> objectInNode;
	
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
	void InsertObj(int ID, LPGAMEOBJECT obj) { objectInNode.insert({ ID,obj }); }
	map<int, LPGAMEOBJECT> GetObj() { return objectInNode;}
	void GetBound(float& s,float& e) 
	{
		s = start;
		e = end;
	}
	bool IsLeaf() { return left == NULL && right == NULL; }
	void Remove(int ID) { objectInNode.erase(ID); }
};

class BinaryTree
{
	int type;

	int mapBound;
	int scrBound;

	TreeNode* root;
	map<int, LPGAMEOBJECT> currentObj;
	map<int, LPGAMEOBJECT> movingObj;

	void CreateTree(map<int, LPGAMEOBJECT> objList);
	void Insert(TreeNode* node, int ID, LPGAMEOBJECT object);
	TreeNode* FindMinNodeContainBound(float x);
	void Remove(int ID, LPGAMEOBJECT obj);
public:

	BinaryTree(string objPath, LPMAP map, int type = HORIZONTAL_BINARYTREE);
	map<int, LPGAMEOBJECT> GetObjectInBound(RECT bound);
	void Update(DWORD dt);
	void Render();
};
typedef BinaryTree* LPBINARYTREE;
