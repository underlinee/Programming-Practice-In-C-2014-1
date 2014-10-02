#include "memberManagementSystem.h"
#include "redBlackFunctions.h"

/* 5. 회원 검색하기 */


int selectSearch(rootPointer* RP, member * leafNull)
{
	HANDLE hConsole;
	int userInput = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	searchUI(0);

	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);

	while (1)
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			userInput = searchUI(1);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			userInput = searchUI(-1);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			Sleep(200);
			searchUI(-80);
			getchar();
			break;
		}
	}

	if (userInput == 0 || userInput == 1 || userInput == 2)
	{
		userInput = find(RP, leafNull, userInput);
		return userInput;
	}
	else
	{
		return -1;
	}
}


int find(rootPointer* RP, member * leafNull, int userPick)
{
	HANDLE hConsole;
	member* searchPerson = addNode();
	member * searchResultSameName[basicStringSize] = { NULL, };
	int userInput = -1;
	int i = 0;
	char * upperDeco = "○─────────────────────────────○";
	char name[32];
	char phone[32];
	int idInput = 0;
	char * selectOneToDelete = "삭제할 회원을 선택해주세요 : ";
	char * selectOneToModify = "수정할 회원을 선택해주세요 : ";
	int userSelect = 0;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);


	system("cls");
	printf("\n\n\n\n\n\n");
	centerJustIndent(40, hConsole);
	
	switch (userPick){
	case(0) :
		printf("name: ");
		fflush(stdin);
		fgets(name, mem_tStringSize, stdin);
		removeNewLine(name);
		fflush(stdin);
		break;
	case(1) :
		printf("ID: ");
		fflush(stdin);
		scanf("%d", &idInput);
		fflush(stdin);
		break;
	case(2) :
		printf("phone: ");
		fflush(stdin);
		fgets(phone, mem_tStringSize, stdin);
		removeNewLine(phone);
		fflush(stdin);
		break;
	}
	fflush(stdin);
	printf("\n\n");

	switch (userPick){
	case(0):
		searchPerson = searchName(name, RP->rootNodeN, leafNull);
		sameNameCheck(searchPerson, leafNull, searchResultSameName,i);
		break;
	case(1):
		searchPerson = searchId(idInput, RP->rootNode, leafNull);
		break;
	case(2) :
		searchPerson = searchPhone(phone, RP->rootNode, leafNull);
	}
	
	if (searchPerson == leafNull || searchPerson == NULL) //회원검색했을 때 결과가 없는경우
	{
		centerJustIndent(40, hConsole);
		SetConsoleTextAttribute(hConsole, 14);
		printf("error: cannot find the name.\n");
		userInput = functionKeyInput_WhenSearchResultVoid();
		switch (userInput){
		case (2) : //F1 : 회원검색 다시하기
			return userInput;
		case (-1) : //F10 : 메인메뉴
			return userInput;
		}
	}

	
	if (searchResultSameName[0] != NULL)
	{
		showSameMember(searchPerson,0);
		for (; searchResultSameName[i] != NULL; i++)
		{
			printf("\n");
			showSameMember(searchResultSameName[i],i+1);
		}
	}

	else
	{
		showMember(searchPerson);
	}

	


	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	switch (userInput){
	case (0) : //F1 : 회원보기
		system("cls");
		return userInput;
	case (1) : //F2 : 회원등록
		system("cls");
		userInput = addData(RP, leafNull);
		return userInput;
	case (2) :  //F5 : 회원검색
		system("cls");
		userInput = selectSearch(RP, leafNull);
		return userInput;
	case (6) : //F3 : 회원삭제
		if (searchResultSameName[0] != NULL)
		{
			while (1){
				centerJustIndent(strlen(selectOneToDelete), hConsole);
				SetConsoleTextAttribute(hConsole, 252);
				printf("%s", selectOneToDelete);
				scanf("%d", &userSelect);
				fflush(stdin);


				if (userSelect == 0) { break; }
				else if (userSelect >= 1 && userSelect <= i){
					searchPerson = searchResultSameName[userSelect - 1];
					break;
				}
				else{
					centerJustIndent(strlen("잘못된 번호입니다. 다시입력하세요!"), hConsole);
					printf("잘못된 번호입니다. 다시입력하세요!\n");
					continue;
				}
			}
		}
		if (searchResultSameName[0] != NULL)
		{
			for (int j = 0; searchResultSameName[j] != NULL; j++)
					{
						searchResultSameName[j] = NULL;
					}

				SetConsoleTextAttribute(hConsole, 13);
		}

		userInput = deleteUI(searchPerson, RP, leafNull);
		return userInput;
	case (7) : //F4 : 회원정보수정
	{
		if (searchResultSameName[0] != NULL)
		{
			while (1){
				centerJustIndent(strlen(selectOneToModify), hConsole);
				SetConsoleTextAttribute(hConsole, 252);
				printf("%s", selectOneToModify);
				scanf("%d", &userSelect);
				fflush(stdin);

				if (userSelect == 0) { break; }
				else if (1 <= userSelect && userSelect <= i){
					searchPerson = searchResultSameName[userSelect - 1];
					break;
				}
				else{
					centerJustIndent(strlen("잘못된 번호입니다. 다시입력하세요!"), hConsole);
					printf("잘못된 번호입니다. 다시입력하세요!\n");
					continue;
				}
			}
			if (searchResultSameName[0] != NULL)
			{
				for (int j = 0; searchResultSameName[j] != NULL; j++)
				{
					searchResultSameName[j] = NULL;
				}
				SetConsoleTextAttribute(hConsole, 13);
			}
		}
	}
		userInput = modify(searchPerson, RP, leafNull);
		return userInput;
	case (-1) : //F10 : 메인메뉴
		return userInput;
	}
	return -1;
}


int sameNameCheck(member * searchPerson, member * leafNull, member ** searchResultSameName, int i)
{
	
	if (searchPerson == leafNull)
	{
		return 0;
	}
	else
	{
		if (strcmp(searchPerson->left->name,searchPerson->name) == 0)
		{
			searchResultSameName[i] = searchPerson->left;
			i++;
			i = sameNameCheck(searchPerson->left, leafNull, searchResultSameName,i);
		}

		if (strcmp(searchPerson->right->name,searchPerson->name) == 0)
		{
			searchResultSameName[i] = searchPerson->right;
			i++;
			i = sameNameCheck(searchPerson->right, leafNull, searchResultSameName,i);
		}
		return i;
	}
}


void nodeCpy(member * original, member * destination)
{
	destination->id = original->id;
	strcpy(destination->name, original->name);
	strcpy(destination->phone, original->phone);
	strcpy(destination->address, original->address);
}

void removeNewLine(char * str)
{
	str[strlen(str)-1] = '\0';
}

int modify(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	int userInput = -1;
	member * tmp;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	userInput = selectModify(searchPerson, RP, leafNull);

	system("cls");
	printf("\n\n");
	showMember(searchPerson);
	printf("\n\n");

	if (userInput == 0){
		centerJustIndent(60, hConsole);
		printf("name: ");
		fflush(stdin);
		fgets(searchPerson->name, mem_tStringSize, stdin);
		removeNewLine(searchPerson->name);
		fflush(stdin);
		nameCheck(searchPerson);
		
		if (searchPerson->treeType == idTree)
		{
			replaceNode(searchPerson->otherTreePointer, RP, leafNull);
			searchPerson->otherTreePointer = addNode();
			nodeCpy(searchPerson, searchPerson->otherTreePointer);
			searchPerson->otherTreePointer->treeType = nameTree;
			searchPerson->otherTreePointer->otherTreePointer = searchPerson;
			searchPerson->otherTreePointer->left = leafNull;
			searchPerson->otherTreePointer->right = leafNull;
			attachTreeN(searchPerson->otherTreePointer, RP, leafNull);
			redBlackTreeN(searchPerson->otherTreePointer, RP, leafNull);
		}
		else
		{
			strcpy(searchPerson->otherTreePointer->name, searchPerson->name);
			tmp = searchPerson->otherTreePointer;
			replaceNode(searchPerson, RP, leafNull);
			tmp->otherTreePointer = addNode();
			tmp->otherTreePointer->treeType = nameTree;
			tmp->otherTreePointer->otherTreePointer = tmp;
			nodeCpy(tmp, tmp->otherTreePointer);
			tmp->otherTreePointer->left = leafNull;
			tmp->otherTreePointer->right = leafNull;
			searchPerson = tmp->otherTreePointer;
			attachTreeN(tmp->otherTreePointer, RP, leafNull);
			redBlackTreeN(tmp->otherTreePointer, RP, leafNull);
		}
	}

	else if (userInput == 1){
		centerJustIndent(60, hConsole);
		fflush(stdin);
		printf("address: ");
		fgets(searchPerson->address, mem_tStringSize, stdin);
		removeNewLine(searchPerson->address);
		fflush(stdin);
		strcpy(searchPerson->otherTreePointer->address, searchPerson->address);
	}
	else{
		centerJustIndent(60, hConsole);
		printf("phone: ");
		fflush(stdin);
		fgets(searchPerson->phone, mem_tStringSize, stdin);
		removeNewLine(searchPerson->phone);
		fflush(stdin);
		phoneCheck_modify(searchPerson);
		strcpy(searchPerson->otherTreePointer->phone, searchPerson->phone);
	}

	printf("\n");
	centerJustIndent(60, hConsole);
	printf("data has been successfully changed!!\n\n");

	showMember(searchPerson);

	fflush(stdin);
	userInput = functionKeyInput();
	fflush(stdin);

	switch (userInput){
	case (0) : //F1 : 회원보기
		system("cls");
		return userInput;
	case (1) : //F2 : 회원등록
		system("cls");
		userInput = addData(RP, leafNull);
		return userInput;
	case (2) :  //F5 : 회원검색
		system("cls");
		userInput = selectSearch(RP, leafNull);
		return userInput;
	case (6) : //F3 : 회원삭제
		userInput = deleteUI(searchPerson, RP, leafNull);
		return userInput;
	case (7) : //F4 : 회원정보수정
		userInput = modify(searchPerson, RP, leafNull);
		return userInput;
	case (-1) : //F10 : 메인메뉴
		return userInput;
	}
	return -1;
}





int searchUI(int upOrDown)
{
	HANDLE hConsole;
	static int now = 0;
	char * menu1 = "search by name";
	char * menu2 = "search by ID";
	char * menu3 = "search by phone";
	char * menu4 = "return to main menu";
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	now += upOrDown;

	if (now <= -1)
	{
		now = 0;
		system("cls");
	}
	else if (now >= 4)
	{
		now = 3;
		system("cls");
	}

	system("cls");
	printf("\n\n\n\n\n");

	if (now == 0){
		centerJustIndent(strlen(menu1), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu1);
	}
	else{
		centerJustIndent(strlen(menu1), hConsole);
		printf("%s\n\n", menu1);
	}
	if (now == 1){
		centerJustIndent(strlen(menu2), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu2);
		SetConsoleTextAttribute(hConsole, 14);
	}
	else{
		centerJustIndent(strlen(menu2), hConsole);
		SetConsoleTextAttribute(hConsole, 15);
		printf("%s\n\n", menu2);
	}
	if (now == 2){
		centerJustIndent(strlen(menu3), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu3);
		SetConsoleTextAttribute(hConsole, 14);
	}
	else{
		centerJustIndent(strlen(menu3), hConsole);
		SetConsoleTextAttribute(hConsole, 15);
		printf("%s\n\n", menu3);
	}
	if (now == 3){
		centerJustIndent(strlen(menu4), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu4);
		SetConsoleTextAttribute(hConsole, 14);
	}
	else{
		centerJustIndent(strlen(menu4), hConsole);
		SetConsoleTextAttribute(hConsole, 15);
		printf("%s\n\n", menu4);
	}
	printf("\n");

	return now;
}

member* searchPhone(char* phone, member* compare, member* leafNull)
{	
	int strcmpRemoveDashResult = strcmpRemoveDash(phone, compare->phone);
	member * result = NULL;
	if (compare->left != leafNull)
	{
		result =  searchPhone(phone, compare->left, leafNull);
		if (result) return result;
	}

	if (strcmpRemoveDashResult == 0)
		return compare;

	if (compare->right != leafNull)
	{
		result = searchPhone(phone, compare->right, leafNull);
		if (result) return result;
	}

	if (result == NULL)
		return NULL;
}

int  strcmpRemoveDash(char * source, char * compare)
{
	char sourceWithNoDash[basicStringSize];
	char compareWithNoDash[basicStringSize];
	int i = 0;

	for (; *source != '\0'; i++)
	{
		if (*source == '-')
		{
			i--;
			*source++;
		}
		else
		{
			sourceWithNoDash[i] = *source;
			*source++;
		}	
	}
	sourceWithNoDash[i] = '\0';
	i = 0;
	for (; *compare != '\0'; i++)
	{
		if (*compare == '-')
		{
			i--;
			*compare++;
		}
		else
		{
			compareWithNoDash[i] = *compare;
			*compare++;
		}
	}
	compareWithNoDash[i] = '\0';

	return strcmp(sourceWithNoDash, compareWithNoDash);
}


member * searchName(char* name, member * compare, member * leafNull)
{
	if (compare == leafNull)
	{
		return leafNull;
	}

	if (strcmp(name, compare->name)<0)
	{
		return searchName(name, compare->left, leafNull);
	}
	else if (strcmp(name, compare->name)>0)
	{
		return searchName(name, compare->right, leafNull);
	}
	else
	{
		return compare;
	}
}


member * searchId(int id, member * compare, member * leafNull)
{
	if (compare == leafNull)
	{
		return leafNull;
	}

	if (id < compare->id)
	{
		return searchId(id, compare->left, leafNull);
	}
	else if (id > compare->id)
	{
		return searchId(id, compare->right, leafNull);
	}
	else
	{
		return compare;
	}

}


/* 수정하기 */
int selectModify(member* searchPerson, rootPointer* RP, member* leafNull)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char choice = 0;
	int userInput = 0;
	char * upperDeco = "○─────────────────────────────○";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	showMember(searchPerson);

	modifyUI(0, searchPerson);
	 
	if (GetAsyncKeyState(VK_UP)) Sleep(100);
	if (GetAsyncKeyState(VK_DOWN))Sleep(100);
	if (GetAsyncKeyState(VK_RETURN))Sleep(100);

	while (1)
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			userInput = modifyUI(1, searchPerson);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			userInput = modifyUI(-1, searchPerson);
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			Sleep(200);
			modifyUI(-80,searchPerson);
			getchar();
			return userInput;
		}
	}
}

int modifyUI(int upOrDown, member* searchPerson)
{
	HANDLE hConsole;
	static int now = 0;
	char * menu1 = "name";
	char * menu2 = "address";
	char * menu3 = "phone";
	char * upperDeco = "○─────────────────────────────○";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	now += upOrDown;

	if (now <= -1)
	{
		now = 0;
		system("cls");
	}
	else if (now >= 3)
	{
		now = 2;
		system("cls");
	}

	system("cls");
	
	
	printf("\n\n\n");
	showMember(searchPerson);
	printf("\n\n\n\n");

	if (now == 0){
		centerJustIndent(strlen(menu1), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu1);
	}
	else{
		centerJustIndent(strlen(menu1), hConsole);
		printf("%s\n\n", menu1);
	}

	if (now == 1){
		centerJustIndent(strlen(menu2), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu2);
		SetConsoleTextAttribute(hConsole, 14);
	}
	else{
		centerJustIndent(strlen(menu2), hConsole);
		SetConsoleTextAttribute(hConsole, 15);
		printf("%s\n\n", menu2);
	}
	if (now == 2){
		centerJustIndent(strlen(menu3), hConsole);
		SetConsoleTextAttribute(hConsole, 252);
		printf("%s\n\n", menu3);
		SetConsoleTextAttribute(hConsole, 14);
	}
	else{
		centerJustIndent(strlen(menu3), hConsole);
		SetConsoleTextAttribute(hConsole, 15);
		printf("%s\n\n", menu3);
	}
	printf("\n");

	return now;
}

void showMember(member* searchPerson)
{
	char * upperDeco = "○─────────────────────────────○";
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("│%-9d%-9s%-25s\t%-13s│\n", searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s", upperDeco);
}


void showSameMember(member* searchPerson, int i )
{
	char * upperDeco = "───────────────────────────────";
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%d. %-9d%-9s%-25s\t%-13s\n",i, searchPerson->id, searchPerson->name, searchPerson->address, searchPerson->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s", upperDeco);
}


/* 3. 회원 삭제하기 */


int deleteUI(member* gonnaBeDeletedNode, rootPointer * RP, member * leafNull)
{
	int userInput = 0;
	HANDLE hConsole;
	char * upperDeco = "○─────────────────────────────○";
	
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("cls");
	printf("\n");

	centerJustIndent(15, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("Sure to delete??\n\n\n\n\n\n\n\n\n");

	
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n", upperDeco);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("│%-9d%-9s%-25s\t%s│\n",gonnaBeDeletedNode->id,gonnaBeDeletedNode->name,gonnaBeDeletedNode->address,gonnaBeDeletedNode->phone);
	centerJustIndent(62, hConsole);
	SetConsoleTextAttribute(hConsole, 14);
	printf("%s\n\n\n\n\n\n\n\n", upperDeco);

	centerJustIndent(32, hConsole);
	SetConsoleTextAttribute(hConsole, 252);
	printf("  cancel ESC    delete ENTER  \n");
	SetConsoleTextAttribute(hConsole, 13);
	
	while (1)
	{
		fflush(stdin);
		userInput = getch();
		if (userInput == 27) {
			userInput = -1;
			return userInput;
		}
		else if (userInput == 13) {
		
			replaceNode(gonnaBeDeletedNode->otherTreePointer, RP, leafNull);
			replaceNode(gonnaBeDeletedNode, RP, leafNull);
			
			centerJustIndent(18, hConsole);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf(".");
			Sleep(100);
			printf("Delete done!!");
			centerJustIndent(15, hConsole);
			break;
		}
		else{
			printf("\a");
			continue;
		}
	}

		userInput = functionKeyInput_WhenSearchResultVoid();
		return userInput;
}
