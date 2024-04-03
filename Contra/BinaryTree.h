#pragma once
#include "GameObject.h"
#include "MyUtility.h"
#include <string>
#include <map>

using namespace std;

#define HORIZONTAL_BINARYTREE 111
#define VERTICAL_BINARYTREE 112

class TreeNode
{
public:

	map<int, LPGAMEOBJECT> objectsInNode;
	
	RECT bound;

	TreeNode* left = NULL;
	TreeNode* right = NULL;

	TreeNode(RECT b) { bound = b;}

	bool IntersectWithBound(RECT rect) { MyUtility::CheckIntersect(bound, rect);}
	void InsertObject(int ID, LPGAMEOBJECT obj) { objectsInNode.insert({ ID,obj }); }
	map<int, LPGAMEOBJECT> GetObjectInNode() { return objectsInNode;}
	RECT GetBound() { return bound; }
	bool IsLeaf() { return left == NULL && right == NULL; }
	void RemoveObject(int ID) { objectsInNode.erase(ID); }
};

class BinaryTree
{
	int type;

	RECT mapSize;
	RECT screenSize;

	TreeNode* root;

public:

	BinaryTree(string objPath, int mapWidth, int mapHeight, int type = HORIZONTAL_BINARYTREE);

	void Insert(TreeNode* node, int ID, LPGAMEOBJECT object);
	void Remove(TreeNode* node, int ID, LPGAMEOBJECT object);
	void GetObjectInTree(TreeNode* node, RECT bound, map<int, LPGAMEOBJECT>& objectList);

	map<int, LPGAMEOBJECT> GetObjectInBound(RECT bound);

};
typedef BinaryTree* LPBINARYTREE;
