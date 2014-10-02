#include "memberManagementSystem.h"

/* ����� Ʈ�� - id�� ����*/
void redBlackTree(member *, rootPointer *, member *);
void insert_case1(member *, rootPointer *, member *);
void insert_case2(member *, rootPointer *, member *);
void insert_case3(member *, rootPointer *, member *);
void insert_case4(member *, rootPointer *, member *);
void insert_case5(member *, rootPointer *, member *);
void rotateRight(member*, member *, rootPointer *);
void rotateLeft(member*, member *, rootPointer *);
member * searchMyFather(member *, member*, member *);
member * searchMyUncle(member *);

/*����� Ʈ�� - name���� ����*/
void redBlackTreeN(member *, rootPointer *, member *);
void insertN_case1(member *, rootPointer *, member *);
void insertN_case2(member *, rootPointer *, member *);
void insertN_case3(member *, rootPointer *, member *);
void insertN_case4(member *, rootPointer *, member *);
void insertN_case5(member *, rootPointer *, member *);
void rotateRightN(member*, member *, rootPointer *);
void rotateLeftN(member*, member *, rootPointer *);
member * searchMyFatherN(member *, member*, member *);
member * searchMyUncleN(member *);

/*����� Ʈ�� - �����ϱ�*/
member * findSuccessor(member *, member *);
member * findLeftSuccessor(member *, member *);
member * findRightSuccessor(member *, member *);
void replaceNode(member *, rootPointer *, member *);
member * searchMySibling(member *);
void deleteNode_step1(member *, rootPointer *, member *);
void deleteNode_step2(member *, rootPointer *, member *);
void deleteNode_step3(member *, rootPointer *, member *);
void deleteNode_step4(member *, rootPointer *, member *);
