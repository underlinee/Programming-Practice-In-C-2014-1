#include "memberManagementSystem.h"
#include "redBlackFunctions.h"


member * addNode(void)
{
	member * node = 0;
	node = (member *)malloc(sizeof(member)* 1);
	node->father = NULL;
	node->color = red;
	return node;
}

void attachTree(member * node, rootPointer * RP, member *leafNull)
{
	node->father = searchMyFather(node, RP->rootNode, leafNull);
	node->color = red;
	
	if (node->father == NULL){
	}
	else if ((node->father)->id > node->id)
	{
		(node->father)->left = node;
	}
	else if ((node->father)->id < node->id)
	{
		(node->father)->right = node;
	}

}

void redBlackTree(member * node, rootPointer * RP, member * leafNull)
{
	node->color = red;
	insert_case1(node, RP, leafNull);
}

void insert_case1(member * node, rootPointer * RP, member *leafNull)
{
	//case 1 : 트리에 아무것도 없다. 아빠노드가 널이다. 따라서  node가 루트다.
	if (node->father == NULL)
	{
		node->color = black;
		RP->rootNode = node;
	}
	else
	{
		insert_case2(node, RP, leafNull);
	}
}


void insert_case2(member * node, rootPointer * RP, member *leafNull)
{
	if (node->father->color == black)
	{

	}
	else
	{
		insert_case3(node, RP, leafNull);
	}

}

void insert_case3(member * node, rootPointer * RP, member * leafNull)
{
	//case 3 : 아빠노드가 빨간색이고 삼촌노드도 빨간색
	member * uncle;
	uncle = searchMyUncle(node);
	if (uncle->color == red && uncle != NULL)
	{
		node->father->color = black;
		uncle->color = black;
		node->father->father->color = red;
		redBlackTree(node->father->father, RP, leafNull);
	}
	else
	{
		insert_case4(node, RP, leafNull);
	}

}

void insert_case4(member * node, rootPointer * RP, member * leafNull)
{
	//case 4 : 아빠가 붉은색, 삼촌이 검정색
	if ((node == node->father->right) && (node->father->father == NULL || node->father == node->father->father->left))
	{
		rotateLeft(node->father, node->father->father, RP);
		node = node->left;
	}
	else if ((node == node->father->left) && (node->father->father == NULL || node->father == node->father->father->right))
	{
		rotateRight(node->father, node->father->father, RP);
		node = node->right;
	}
	insert_case5(node, RP, leafNull);

}

void insert_case5(member * node, rootPointer * RP, member * leafNull)
{
	node->father->color = black;
	node->father->father->color = red;

	if (node == node->father->left)
	{
		rotateRight(node->father->father, node->father->father->father, RP);
	}
	else
	{
		rotateLeft(node->father->father, node->father->father->father, RP);
	}
}

void rotateRight(member* father, member * grandF, rootPointer * RP)
{
	member * node = father->left;
	member * rightChildOfNode = node->right;

	if (grandF != NULL)
	{
		if (node->id > grandF->id)
			grandF->right = node;
		else
			grandF->left = node;
	}

	else{
		RP->rootNode = node;
	}
	node->right = father;
	father->left = rightChildOfNode;

	node->father = grandF;
	father->father = node;
	rightChildOfNode->father = father;

}


void rotateLeft(member* father, member * grandF, rootPointer * RP)
{
	member * node = father->right;
	member * leftChildOfNode = node->left;

	if (grandF != NULL)
	{
		if (node->id < grandF->id)
			grandF->left = node;
		else
			grandF->right = node;
	}


	else{
		RP->rootNode = node;
	}

	node->left = father;
	father->right = leftChildOfNode;

	node->father = grandF;
	father->father = node;
	leftChildOfNode->father = father;
}

member * searchMyFather(member * node, member * compare, member * leafNull)
{
	if (compare == NULL)
	{
		return NULL;
	}

	else if (node->id < compare->id)
	{
		if (compare->left == leafNull)
		{
			return compare;
		}
		else
		{
			return searchMyFather(node, compare->left, leafNull);
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
			return searchMyFather(node, compare->right, leafNull);
		}


	}
}

member * searchMyUncle(member * node)
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
