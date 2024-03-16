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

BinaryTree::BinaryTree(string objPath, LPMAP map, int type)
{
	Game* game = Game::GetInstance();

	if (type == HORIZONTAL_BINARYTREE)
	{
		scrBound = game->GetBackBufferWidth();
		mapBound = map->GetWidth();
	}
	else
	{
		scrBound = game->GetBackBufferHeight();
		mapBound = map->GetHeight();
	}

	ifstream fileObj(objPath);

	if (!fileObj.is_open())
		return;

	string line;
	vector<LPGAMEOBJECT> objList;

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
		obj->SetID(ID);
		obj->SetPosition(x, y);
		obj->SetState(state);
		objList.push_back(obj);
	}

	root = new TreeNode(0, mapBound);
	
	CreateTree(objList);

	fileObj.close();
}

void BinaryTree::Insert(TreeNode* node, LPGAMEOBJECT object)
{
	float start, end;
	node->GetBound(start, end);
	float mid = (start + end) / 2;

	if ((mid - start) < scrBound / 2) // can't split anymore
	{
		node->InsertObj(object);
		return;
	}

	if (start <= object->GetX() && object->GetX() <= mid)
	{
		if (node->left == NULL)
			node->left = new TreeNode(start, mid);
		Insert(node->left, object);
	}
	else
	{
		if (node->right == NULL)
			node->right = new TreeNode(mid, end);
		Insert(node->right, object);
	}
}

void BinaryTree::CreateTree(vector<LPGAMEOBJECT> objList)
{
	for (int i = 0; i < objList.size(); i++)
		Insert(root, objList[i]);
}

TreeNode* BinaryTree::FindNode(float start, float end)
{
	bool con = true;
	TreeNode* node = root;

	while (con)
	{
		con = false;

		if (node->left != NULL && node->left->InBound(start) && node->left->InBound(end))
		{
			node = node->left;
			con = true;
		}

		if (node->right != NULL && node->right->InBound(start) && node->right->InBound(end))
		{
			node = node->right;
			con = true;
		}
	}

	return node;
}

void BinaryTree::GetObjectInSubTree(TreeNode* node, vector<LPGAMEOBJECT>& objectList)
{
	if (node->left == NULL && node->right == NULL)
	{
		vector<LPGAMEOBJECT> obj = node->GetObj();
		objectList.insert(objectList.end(),obj.begin(), obj.end());
	}

	if (node->left != NULL)
		GetObjectInSubTree(node->left, objectList);

	if (node->right != NULL)
		GetObjectInSubTree(node->right, objectList);

}

vector<LPGAMEOBJECT> BinaryTree::GetObjectInBound(RECT bound)
{
	TreeNode* node = FindNode(bound.left, bound.right);
	vector<LPGAMEOBJECT> objectList;
	
	GetObjectInSubTree(node, objectList);

	//Check if the object intersect with bound, if not then delete it
	for (int i = 0; i < objectList.size(); i++)
		if (!CheckIntersect(objectList[i]->GetCollisionBound(), bound))
			objectList.erase(objectList.begin() + i);

	//Check if each object in list is unique, if not then delete it
	sort(objectList.begin(), objectList.end(), [](LPGAMEOBJECT a, LPGAMEOBJECT b) {
		return a->GetID() < b->GetID();
		});
	objectList.erase(unique(objectList.begin(), objectList.end()), objectList.end());

	return objectList;
}

void BinaryTree::Update(DWORD dt)
{
	currentObj = GetObjectInBound(Camera::GetInstance()->GetBound());

	for (int i = 0; i < currentObj.size(); i++)
		currentObj[i]->Update(dt);
}

void BinaryTree::Render()
{
	for (int i = 0; i < currentObj.size(); i++)
		currentObj[i]->Render();
}
