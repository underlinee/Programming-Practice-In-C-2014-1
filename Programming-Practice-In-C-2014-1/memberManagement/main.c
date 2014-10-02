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
			system("cls"); //id ������ ȸ������
			userInput = printList(RP.rootNode, leafNull);
			break;
		case (registerNewMember) : //ȸ������ϱ�
			system("cls");
			userInput = addData(&RP, leafNull);
			break;
		case (searchMember) : //ȸ���˻��ϱ�
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (deleteMember) : //�����ϱ�
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (memberInfoModif) : //�����ϱ�
			system("cls");
			userInput = selectSearch(&RP, leafNull);
			break;
		case (saveMemberList) : //�����ϱ�
			system("cls");
			userInput = saveData(&RP, leafNull);
			break;
		case (quitProgram) : //�����ϱ� ���� ���忩�� Ȯ��
			system("cls");
			userInput = askSave(&RP,leafNull);
			return 0;
		case (creditPage) : //credit
			system("cls");
			userInput = credit();
			PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
			break;
		case (printMemberListInNameOrder) : //�̸������� ȸ������
			system("cls");
			userInput = printList(RP.rootNodeN, leafNull);
			break;
		}
	}

	return 0;
}

