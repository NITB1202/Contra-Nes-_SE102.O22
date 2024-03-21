#include "BinaryTree.h"
#include "ObjectIDDefine.h"
#include "Game.h"
#include <fstream>
#include <sstream>
#include <algorithm>

bool CheckIntersect(RECT rect1, RECT rect2)
{
	bool overlapX = (rect1.left < rect2.right) && (rect1.right > rect2.left);
	bool overlapY = (rect1.top > rect2.bottom) && (rect1.bottom < rect2.top);

	return overlapX && overlapY;
}

BinaryTree::BinaryTree(string objPath, LPMAP m, int type)
{
	Game* game = Game::GetInstance();

	if (type == HORIZONTAL_BINARYTREE)
	{
		scrBound = game->GetBackBufferWidth();
		mapBound = m->GetWidth();
	}
	else
	{
		scrBound = game->GetBackBufferHeight();
		mapBound = m->GetHeight();
	}

	ifstream fileObj(objPath);

	if (!fileObj.is_open())
		return;

	string line;
	map<int, LPGAMEOBJECT> objList;

	while (getline(fileObj, line))
	{
		stringstream ss(line);
		int type, ID, state;
		float x, y;
		
		ss >> type;
		ss >> ID;
		ss >> x; 
		ss >> y;
		ss >> state;

		LPGAMEOBJECT obj = InitObj(type);
		obj->SetPosition(x, y);
		obj->SetState(state);
		objList.insert({ ID,obj });

		if (IsMovingObject(type))
			movingObj.insert({ ID,obj });
	}

	root = new TreeNode(0, mapBound);
	
	CreateTree(objList);

	fileObj.close();
}

void BinaryTree::Insert(TreeNode* node, int ID, LPGAMEOBJECT object)
{
	float start, end;
	node->GetBound(start, end);
	float mid = (start + end) / 2;

	if ((mid - start) < scrBound) // can't split anymore
	{
		node->InsertObj(ID, object);
		return;
	}

	if (start <= object->GetX() && object->GetX() <= mid)
	{
		if (node->left == NULL)
			node->left = new TreeNode(start, mid);
		Insert(node->left,ID, object);
	}
	
	if (mid <= object->GetX() && object->GetX() <= end)
	{
		if (node->right == NULL)
			node->right = new TreeNode(mid, end);
		Insert(node->right, ID, object);
	}
}

void BinaryTree::CreateTree(map<int, LPGAMEOBJECT> objList)
{
	for (auto it = objList.begin(); it != objList.end(); it++)
		Insert(root, it->first,it->second);
}

TreeNode* BinaryTree::FindMinNodeContainBound(float x)
{
	bool con = true;
	TreeNode* node = root;

	while (con)
	{
		con = false;

		if (node->left != NULL && node->left->InBound(x))
		{
			node = node->left;
			con = true;
		}

		if (node->right != NULL && node->right->InBound(x))
		{
			node = node->right;
			con = true;
		}
	}

	return node;
}

map<int, LPGAMEOBJECT> BinaryTree::GetObjectInBound(RECT bound)
{
	TreeNode* startNode = FindMinNodeContainBound(bound.left);
	TreeNode* endNode = FindMinNodeContainBound(bound.right);
	map<int,LPGAMEOBJECT> objectList;

	if (startNode->IsLeaf() || endNode->IsLeaf())
	{
		if (startNode == endNode)
			objectList = startNode->GetObj();
		else
		{
			map<int, LPGAMEOBJECT> leftObj = startNode->GetObj();
			map<int, LPGAMEOBJECT> rightObj = endNode->GetObj();
			objectList.insert(leftObj.begin(), leftObj.end());
			objectList.insert(rightObj.begin(), rightObj.end());
		}
	}
	return objectList;
}

void BinaryTree::Update(DWORD dt)
{
	//remove and re-insert for moving object
	for (auto it = movingObj.begin(); it != movingObj.end(); ++it)
	{
		it->second->Update(dt);
		Remove(it->first, it->second);
		Insert(root,it->first,it->second);
	}

	currentObj = GetObjectInBound(Camera::GetInstance()->GetBound());

	for (auto it = currentObj.begin(); it != currentObj.end(); ++it)
	{
		if (movingObj.find(it->first) == movingObj.end())
			it->second->Update(dt);
	}
}

void BinaryTree::Render()
{
	for (auto it = currentObj.begin(); it != currentObj.end(); ++it)
		it->second->Render();
}

void BinaryTree::Remove(int ID,LPGAMEOBJECT obj)
{
	RECT bound = obj->GetCollisionBound();

	TreeNode* startNode = FindMinNodeContainBound(bound.left);
	TreeNode* endNode = FindMinNodeContainBound(bound.right);

	startNode->Remove(ID);
	endNode->Remove(ID);
}
