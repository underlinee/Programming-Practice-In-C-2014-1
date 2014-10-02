#include "memberManagementSystem.h"
#include "redBlackFunctions.h"

int main(void)
{
	int userInput = mainMenu;
	rootPointer RP = { NULL, NULL };
	member * leafNull;

	leafNull = (member *)malloc(sizeof(member)* 1);
	leafNull->color = black;
	
	leafNull = makeTree(&RP, leafNull);

	PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	while (1)
	{
		fflush(stdin);
		switch (userInput){
		case (mainMenu) :
			userInput = printMain();
			break;
		case (printMemberListInIdOrder) :
			system("cls"); //id 순으로 회원보기
			userInput = printList(RP.rootNode, leafNull);
			break;
		case (registerNewMember) : //회원등록하기
			system("cls");
			userInput = addData(&RP, leafNull);
			break;
		case (searchMember) : //회원검색하기
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (deleteMember) : //삭제하기
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (memberInfoModif) : //수정하기
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (saveMemberList) : //저장하기
			system("cls");
			userInput = saveData(&RP, leafNull);
			break;
		case (quitProgram) : //종료하기 전에 저장여부 확인
			system("cls");
			userInput = askSave(&RP,leafNull);
			return 0;
		case (creditPage) : //credit
			system("cls");
			userInput = credit();
			PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
			break;
		case (printMemberListInNameOrder) : //이름순으로 회원보기
			system("cls");
			userInput = printList(RP.rootNodeN, leafNull);
			break;
		}
	}

	return 0;
}

