#include "memberManagementSystem.h"
#include "redBlackFunctions.h"



member * findSuccessor(member * node, member * leafNull)
{
	//successor가 될 브랜치의 왼쪽노드와 브랜치의 오른쪽노드를 선정하고, 둘중에 하나가 red일경우 return, 둘다 red가 아닐경우 left node를 return
	member * candidateL;
	member * candidateR;

	if (node->left == leafNull)
		candidateL = node;
	else
		candidateL = findLeftSuccessor(node->left, leafNull);

	if (node->right == leafNull)
		candidateR = node;
	else
		candidateR = findRightSuccessor(node->right, leafNull);



	if (candidateL->color == red)
		return candidateL;

	else if (candidateR->color == red)
		return candidateR;

	else
		return candidateL;

}


member * findLeftSuccessor(member * node, member *leafNull)
{
	if (node->right == leafNull)
		return node;

	else
		findLeftSuccessor(node->right, leafNull);

}

member * findRightSuccessor(member * node, member *leafNull)
{
	if (node->left == leafNull)
		return node;

	else
		findRightSuccessor(node->left, leafNull);
}

void replaceNode(member * node, rootPointer * RP, member * leafNull)
{
	member * successor = findSuccessor(node, leafNull);

	/****************************************************************************************************************************************************************/

	///successor를 선출하여 삭제할 node 를 successor로 대치시킬 때 발생하는 경우의 수
	///00. successor가 red일 경우 : 삭제할 node를 successor로 대치시키고 delete end

	///01. successor가 black일 경우
	///01-0.successor의 자식이 없을 경우 : deleteStep 진행
	///01-1.successor의 자식이 있을 경우 : successor를 successor의 자식으로 대치시키고 successor의 자식의 색을 successor로 바꾼 후 delete end


	///c.f. 예외case : successor가 root일 경우 : free(root)

	/****************************************************************************************************************************************************************/

	//c.f. successor가 root인경우 : 트리에 root노드 단 하나만 존재하는 경우, root를 free, delete끝
	if (successor == RP->rootNode || successor == RP->rootNodeN)
	{
		if (successor->treeType == idTree)
			RP->rootNode = NULL;
		else
			RP->rootNodeN = NULL;
		
		free(successor);
	}

	//00. successor가 red일 경우
	if (successor->color == red)
	{
		if (successor->father->right == successor) //successor가 left branch에서 선출 되었을 때
		{
			//successor아빠의 오른쪽을 널로 바꾸고 successor의 칼라를 삭제할 노드의 색으로 변경후 삭제할 노드에 successor의 내용을 삽입, successor는 free, delete끝
			successor->father->right = leafNull;
			successor->color = node->color;
			node->id = successor->id;
			strcpy(node->address, successor->address);
			strcpy(node->phone, successor->phone);
			strcpy(node->name, successor->name);
			free(successor);
		}

		else //successor가 right branch에서 선출 되었을 때
		{
			//successor아빠의 오른쪽을 널로 바꾸고 successor의 칼라를 삭제할 노드의 색으로 변경후 삭제할 노드에 successor의 내용을 삽입, successor는 free, delete끝
			successor->father->left = leafNull;

			node->id = successor->id;
			strcpy(node->address, successor->address);
			strcpy(node->phone, successor->phone);
			strcpy(node->name, successor->name);

			free(successor);
		}
	}

	//01. successor가 black일 경우
	else
	{
		//삭제할 node의 내용을 succeessor로 대체
		node->id = successor->id;
		strcpy(node->address, successor->address);
		strcpy(node->phone, successor->phone);
		strcpy(node->name, successor->name);

		//01-00. successor가 자식노드가 없을때, succeessor delete시작
		if (successor->left == leafNull && successor->right == leafNull)
		{
			deleteNode_step1(successor, RP, leafNull);
		
			if (successor->father->left == successor)
			{
				successor->father->left = leafNull;
				free(successor);
			}
			else
			{
				successor->father->right = leafNull;
				free(successor);
			}
		}

		//01-01. successor가 자식노드가 있을 때, successor자리에 successor의 자식노드를 위치 (successor의 자식노드는 반드시 붉은색이어야 하고, 자식은 1개 일수밖에 없음), successor 자식노드 색깔 검정으로 칠하고  delete끝
		else
		{
			if (successor->id < node->id)//successor가 왼쪽 branch에서 선출 되었을 때
			{
				successor->id = successor->left->id;
				strcpy(successor->address, successor->left->address);
				strcpy(successor->phone, successor->left->phone);
				strcpy(successor->name, successor->left->name);
				free(successor->left);
				successor->left = leafNull;
			}
			else//successor가 오른쪽 branch에서 선출 되었을 때
			{
				successor->id = successor->right->id;
				strcpy(successor->address, successor->right->address);
				strcpy(successor->phone, successor->right->phone);
				strcpy(successor->name, successor->right->name);
				free(successor->right);
				successor->right = leafNull;
			}
		}
	}
}


member * searchMySibling(member * node)
{
	if (node->father->left == node)
	{
		return node->father->right;
	}

	else
	{
		return node->father->left;
	}
}

//case1 : sibling이 red -> 아빠를 빨간색, sibling을 검정으로 바꾸고 rotate하고 delete 종료
void deleteNode_step1(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);

	if (sibling->color == red)
	{
		node->father->color = red;
		sibling->color = black;

		if (node->father->left = node) 	//node가 아빠 왼쪽노드일때 (Successor가 오른쪽 branch에서 선출된 경우)
			switch (node->treeType) {
			case(idTree):
				rotateLeft(sibling->father, sibling->father->father, RP);
				break;
			case(nameTree):
				rotateLeftN(sibling->father, sibling->father->father, RP);
				break;
		}
		else 	//node가 아빠 오른쪽노드일때 (Successor가 왼쪽 branch에서 선출된 경우)
			switch (node->treeType) {
			case(idTree) :
				rotateRight(sibling->father, sibling->father->father, RP);
				break;
			case(nameTree) :
				rotateRightN(sibling->father, sibling->father->father, RP);
				break;
		}
	}

	else{
		deleteNode_step2(node, RP, leafNull);
	}
}

//case2 : node가 왼쪽 노드일때 : sibling의 자식이 둘다 red거나 왼쪽이 red고, 오른쪽이 black인경우 ( node가 오른쪽 노드일때는 vice versa)
void deleteNode_step2(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);

	if (node->father->left == node)
	{
		if (sibling->color == black &&  sibling->right->color == red && (sibling->left->color == red || sibling->left->color == black))
		{
			sibling->color = sibling->father->color;
			sibling->father->color = black;
			sibling->right->color = black;
			switch (node->treeType) {
			case(idTree) :
				rotateLeft(sibling->father, sibling->father->father, RP);
				break;
			case(nameTree) :
				rotateLeftN(sibling->father, sibling->father->father, RP);
				break;
			}
		}
		else
		{
			deleteNode_step3(node, RP, leafNull);
		}
	}

	else
	{
		if (sibling->color == black &&  sibling->left->color == red && (sibling->right->color == red || sibling->right->color == black))
		{
			sibling->color = sibling->father->color;
			sibling->father->color = black;
			sibling->left->color = black;
			switch (node->treeType) {
			case(idTree) :
				rotateRight(sibling->father, sibling->father->father, RP);
				break;
			case(nameTree) :
				rotateRightN(sibling->father, sibling->father->father, RP);
				break;
			}
		}
		else
		{
			deleteNode_step3(node, RP, leafNull);
		}
	}
}

//case3 : sibling의 색이 black, sibling의 child 왼쪽이 red 오른쪽이 black (successor가 왼쪽 branch에서 선출되었을 경우 vice versa)
void deleteNode_step3(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);
	if (node->father->left == node){
		if (sibling->color == black && sibling->left->color == red && sibling->right->color == black)
		{
			sibling->left->color = black;
			sibling->color = red;
			switch (node->treeType) {
			case(idTree) :
				rotateRight(sibling->father, sibling->father->father, RP);
				break;
			case(nameTree) :
				rotateRightN(sibling->father, sibling->father->father, RP);
				break;
			}
			deleteNode_step2(node, RP, leafNull);
		}
		else
		{
			deleteNode_step4(node, RP, leafNull);
		}
	}

	else {
		if (sibling->color == black && sibling->right->color == red && sibling->left->color == black)
		{
			sibling->right->color = black;
			sibling->color = red; switch (node->treeType) {
			case(idTree) :
				rotateLeft(sibling->father, sibling->father->father, RP);
				break;
			case(nameTree) :
				rotateLeftN(sibling->father, sibling->father->father, RP);
				break;
			}
			deleteNode_step2(node, RP, leafNull);
		}
		else
		{
			deleteNode_step4(node, RP, leafNull);
		}
	}

}


//case 4 : sibling의 색이 black, sibling의 양쪽 자식이 모두 black 인 경우
void deleteNode_step4(member * node, rootPointer * RP, member * leafNull)
{
	member * sibling = searchMySibling(node);

	if (sibling->color == black && sibling->left->color == black && sibling->right->color == black)
	{
		sibling->color = red;

		if (sibling->father->color == red)
			sibling->father->color = black;

		else
		{
			if (RP->rootNode == sibling->father){}
			else{
				deleteNode_step1(sibling->father, RP, leafNull);
			}
		}
	}
}