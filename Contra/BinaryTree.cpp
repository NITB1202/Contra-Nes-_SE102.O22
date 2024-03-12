#include "BinaryTree.h"
#include "Game.h"

BinaryTree::BinaryTree()
{
	Game* game = Game::GetInstance();
	int scrWidth = game->GetBackBufferWidth();
	int mapWidth = game->GetCurrentScene().GetMapWidth();
}

TreeNode* BinaryTree::CreateTree(float start, float end)
{
	if (end - start < scrWidth / 2)
		return nullptr;

	root = new TreeNode(start, end);

	float mid = (start + end) / 2;

	root->left = CreateTree(start, mid);
	root->right = CreateTree(mid, end);

	return root;
}

void BinaryTree::Travel(TreeNode* parent, LPGAMEOBJECT obj)
{
	if (parent->left == NULL && parent->right == NULL)
	{
		parent->SetObj(obj);
		return;
	}

	if (parent->left->InBound(obj->GetX()))
		Travel(parent->left, obj);

	if (parent->right->InBound(obj->GetX()))
		Travel(parent->right, obj);

}

void BinaryTree::Init(vector<LPGAMEOBJECT> objList)
{

	CreateTree(0, mapWidth);

	for (int i = 0; i < objList.size(); i++)
		Travel(root, objList[i]);

}

vector<LPGAMEOBJECT> BinaryTree::GetInScreenObject()
{
	float start = Camera::GetInstance()->getX();
	float end = start + Camera::GetInstance()->getWidth();
	float mid = (start + end) / 2;
	vector<LPGAMEOBJECT> arr;
	
	return arr;
}