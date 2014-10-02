#include "memberManagementSystem.h"
#include "redBlackFunctions.h"

void attachTreeN(member * node, rootPointer * RP, member *leafNull)
{
	node->father = searchMyFatherN(node, RP->rootNodeN, leafNull);
	node->color = red;

	if (node->father == NULL){
		RP->rootNodeN = node;
		return;
	}

	if (strcmp((node->father)->name, node->name) == 0){
		(node->father)->right = node;
	}
	else if (strcmp((node->father)->name, node->name)>0)
	{
		(node->father)->left = node;
	}
	else if (strcmp((node->father)->name, node->name) < 0)
	{
		(node->father)->right = node;
	}

}

void redBlackTreeN(member * node, rootPointer* RP, member * leafNull)
{
	insertN_case1(node, RP, leafNull);
}

void insertN_case1(member * node, rootPointer * RP, member *leafNull)
{
	//case 1 : 트리에 아무것도 없다. 아빠노드가 널이다. 따라서  node가 루트다.
	if (node->father == NULL)
	{
		node->color = black;
		RP->rootNodeN = node;
	}
	else
	{
		insertN_case2(node, RP, leafNull);
	}
}


void insertN_case2(member * node, rootPointer * RP, member *leafNull)
{
	if (node->father->color == black)
	{

	}
	else
	{
		insertN_case3(node, RP, leafNull);
	}

}

void insertN_case3(member * node, rootPointer * RP, member * leafNull)
{
	//case 3 : 아빠노드가 빨간색이고 삼촌노드도 빨간색
	member * uncle;
	uncle = searchMyUncleN(node);
	if (uncle != NULL && uncle != leafNull && uncle->color == red)
	{
		node->father->color = black;
		uncle->color = black;
		if (node->father->father != NULL)
		{
			node->father->father->color = red;
			redBlackTreeN(node->father->father, RP, leafNull);
		}
	}
	else
	{
		insertN_case4(node, RP, leafNull);
	}

}

void insertN_case4(member * node, rootPointer * RP, member * leafNull)
{
	//case 4 : 아빠가 붉은색, 삼촌이 검정색
	if ((node == node->father->right) && (node->father->father == NULL || node->father == node->father->father->left))
	{
		rotateLeftN(node->father, node->father->father, RP);
		node = node->left;
	}
	else if ((node == node->father->left) && (node->father->father == NULL || node->father == node->father->father->right))
	{
		rotateRightN(node->father, node->father->father, RP);
		node = node->right;
	}
	insertN_case5(node, RP, leafNull);

}

void insertN_case5(member * node, rootPointer * RP, member * leafNull)
{
	node->father->color = black;
	if (node->father->father != NULL)
	{
		node->father->father->color = red;
		if (node == node->father->left)
		{
			if (node->father->father->father != NULL)
			{
				rotateRightN(node->father->father, node->father->father->father, RP);
			}
		}
		else
		{
			if (node->father->father->father != NULL)
			{
				rotateLeftN(node->father->father, node->father->father->father, RP);
			}
		}
	}
}

void rotateRightN(member* father, member * grandF, rootPointer * RP)
{
	member * node = father->left;
	member * rightChildOfNode = node->right;

	if (grandF != NULL)
	{
		if (strcmp(node->name, grandF->name) < 0)
			grandF->left = node;
		else
			grandF->right = node;
	}
	else{
		RP->rootNodeN = node;
	}

	node->right = father;
	father->left = rightChildOfNode;

	node->father = grandF;
	father->father = node;
	rightChildOfNode->father = father;

}


void rotateLeftN(member* father, member * grandF, rootPointer * RP)
{
	member * node = father->right;
	member * leftChildOfNode = node->left;

	if (grandF != NULL)
	{
		if (strcmp(node->name, grandF->name) < 0)
			grandF->left = node;
		else
			grandF->right = node;

	}
	else{
		RP->rootNodeN = node;
	}

	node->left = father;
	father->right = leftChildOfNode;

	node->father = grandF;
	father->father = node;
	leftChildOfNode->father = father;//없어도될듯
}

member * searchMyFatherN(member * node, member * compare, member * leafNull)
{

	if (compare == NULL)
	{
		return NULL;
	}


	if (strcmp(node->name, compare->name)<0)
	{
		if (compare->left == leafNull)
		{
			return compare;
		}
		else
		{
			return searchMyFatherN(node, compare->left, leafNull);
		}
	}

	else
	{

		if (compare->right == leafNull)
		{
			return compare;
		}
		else
		{
			return searchMyFatherN(node, compare->right, leafNull);
		}
	}
}

member * searchMyUncleN(member * node)
{
	if (node->father == NULL || node->father->father == NULL)
	{
		return NULL;
	}
	else if (node->father->father->left == node->father)
	{
		return node->father->father->right;
	}
	else
	{
		return node->father->father->left;
	}
}
