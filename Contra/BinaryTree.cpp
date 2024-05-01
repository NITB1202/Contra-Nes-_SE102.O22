#include "BinaryTree.h"
#include "Game.h"
#include <fstream>
#include <sstream>

BinaryTree::BinaryTree(string objectPath, int mapWidth, int mapHeight, int type)
{
	Game* game = Game::GetInstance();
	mapSize = { 0, mapHeight, mapWidth, 0 };

	this->type = type;

	ifstream fileObj(objectPath);

	if (!fileObj.is_open())
		return;

	root = new TreeNode(mapSize);

	string line;

	while (getline(fileObj, line))
	{
		stringstream ss(line);
		int type, ID, state, width, height;
		float x, y;

		ss >> type;
		ss >> ID;
		ss >> x;
		ss >> y;
		ss >> width;
		ss >> height;
		ss >> state;

		LPGAMEOBJECT object = MyUtility::InitObj(type);
		
		y = mapHeight - y;
		object->SetPosition(x, y);
		object->SetWidthHeight(width, height);
		object->SetState(state);

		Insert(root, ID, object);
	}

	fileObj.close();
}

void SplitBoundHorizontal(RECT sourceRect, RECT& leftRect, RECT& rightRect)
{
	int mid = (sourceRect.left + sourceRect.right) / 2;
	leftRect = { sourceRect.left, sourceRect.top, mid, sourceRect.bottom };
	rightRect = { mid, sourceRect.top, sourceRect.right, sourceRect.bottom };
}

void SplitBoundVertical(RECT sourceRect, RECT& leftRect, RECT& rightRect)
{
	int mid = (sourceRect.top + sourceRect.bottom) / 2;
	leftRect = { sourceRect.left, mid, sourceRect.right, sourceRect.bottom };
	rightRect = { sourceRect.left, sourceRect.top, sourceRect.right, mid };
}

void BinaryTree::Insert(TreeNode* node, int ID, LPGAMEOBJECT object)
{
	RECT currentBound = node->GetBound();
	
	//Node size < screen size /2 -> stop 
	if (MyUtility::CalculateArea(node->GetBound()) < MyUtility::CalculateArea(Camera::GetInstance()->GetBound()))
	{
		node->InsertObject(ID, object);
		return;
	}

	RECT leftBound, rightBound;

	if (type == HORIZONTAL_BINARYTREE)
		SplitBoundHorizontal(currentBound, leftBound, rightBound);
	else
		SplitBoundVertical(currentBound, leftBound, rightBound);

 	if (MyUtility::CheckIntersect(leftBound,object->GetCollisionBound()))
	{
		if (node->left == NULL)
			node->left = new TreeNode(leftBound);
		Insert(node->left,ID, object);
	}
	
	if (MyUtility::CheckIntersect(rightBound, object->GetCollisionBound()))
	{
		if (node->right == NULL)
			node->right = new TreeNode(rightBound);
		Insert(node->right, ID, object);
	}
}

void BinaryTree::GetObjectInTree(TreeNode* node, RECT bound, map<int, LPGAMEOBJECT>& objectList)
{
	if (node->IsLeaf())
	{
		map<int, LPGAMEOBJECT> objectInNode = node->GetObjectInNode();
		objectList.insert(objectInNode.begin(), objectInNode.end());
		return;
	}

	if (node->left != NULL && MyUtility::CheckIntersect(node->left->GetBound(), bound))
		GetObjectInTree(node->left, bound, objectList);

	if (node->right != NULL && MyUtility::CheckIntersect(node->right->GetBound(), bound))
		GetObjectInTree(node->right, bound, objectList);
}

void BinaryTree::Remove(TreeNode* node, int ID, LPGAMEOBJECT object)
{
	if (node->IsLeaf())
	{
		node->RemoveObject(ID);

		if (node->GetObjectInNode().empty())
			delete node;

		return;
	}

	if (node->left != NULL && MyUtility::CheckIntersect(node->left->GetBound(), object->GetCollisionBound()))
		Remove(node->left, ID, object);

	if (node->right != NULL && MyUtility::CheckIntersect(node->right->GetBound(), object->GetCollisionBound()))
		Remove(node->right, ID, object);
}

void BinaryTree::RemoveObjectInTree(int ID, LPGAMEOBJECT object)
{
	Remove(root, ID, object);
}

map<int, LPGAMEOBJECT> BinaryTree::GetObjectInBound(RECT bound)
{
	map<int, LPGAMEOBJECT> objectList;
	GetObjectInTree(root, bound, objectList);
	return objectList;
}

void BinaryTree::ClearTree(TreeNode* root)
{
	if (root != NULL)
	{
		ClearTree(root->left);
		ClearTree(root->right);
		delete root;
	}
}

BinaryTree::~BinaryTree()
{
	ClearTree(root);
}
