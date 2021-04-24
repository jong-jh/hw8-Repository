/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("----2018038051 정종현----\n\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;
	listNode* prev = NULL;
	
	while(p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* p=h->rlink;
	listNode* temp=(listNode*)malloc(sizeof(listNode));	//노드 생성
	temp->key=key;

	if(p==h){//list가 비어있다면
		temp->rlink=h;
		temp->llink=h;
		h->rlink=temp;
		h->llink=temp;
		return 1;
	}
	while(1){
		if(p->rlink==h){//list의 마지막이라면
			temp->llink=p;
			temp->rlink=h;

			p->rlink=temp;
			h->llink=temp;
			break;
		}
		else p=p->rlink;
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode *p=h->rlink;
	
	if(p==h){//list 가 비어있다면 다음을 출력
		printf("list is empty now. \n");
		return 0;
	}
	
	while(1){
		if(p->rlink==h){
			p->rlink->llink=p->llink;
			p->llink->rlink=p->rlink;//마지막이기 때문에 h를 가리킴. (p->llink->rlink=h)
			free(p);
			break;
		}
		else p=p->rlink;
	}

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* temp=(listNode*)malloc(sizeof(listNode));	//노드 생성
	temp->key=key;

	if(h->rlink==h){//list가 비어있다면
		temp->rlink=h;
		temp->llink=h;
		h->rlink=temp;
		h->llink=temp;
		return 1;
	}

	temp->llink=h;
	temp->rlink=h->rlink;
	h->rlink=temp;
	temp->rlink->llink=temp;	//temp가 가리키는 노드의 llink는 temp를 가리킨다.

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode *p=h->rlink;
	
	if(p==h){//list 가 비어있다면 다음을 출력
		printf("list is empty now. \n");
		return 0;
	}

	p->llink->rlink=p->rlink;
	p->rlink->llink=p->llink;
	free(p);

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode *lead=h->rlink;
	listNode *trail=NULL;

	while(lead!=h){
		trail=lead->llink;		//trail에 lead의llink값을 저장
		lead->llink=lead->rlink;//llink값을 rlink값으로 바꿈
		lead->rlink=trail;		///rlink 값을 llink값으로 바꿈 -> 순서가 바뀜

		lead=lead->llink;	//다음노드로 이동
	}

	h->llink=h->rlink;
	h->rlink=trail->llink;

	return 1;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
	listNode *p=h->rlink;
	listNode* temp=(listNode*)malloc(sizeof(listNode));	//노드 생성
	temp->key=key;

	if(h->rlink==h){//list가 비어있다면
		temp->rlink=h;
		temp->llink=h;
		h->rlink=temp;
		h->llink=temp;
		return 1;
	}
	while(1){
		if(key<=h->rlink->key){		//temp가 맨 앞 쪽에 와야할 때
			temp->rlink=h->rlink;	//temp rlink 를 헤더노드가 가리키던 노드와 연결
			temp->llink=h;			//llink를 h에 연결 (첫 번 째 이므로)
			h->rlink->llink=temp;	//밀린 노드의 llink를 temp에 연결
			h->rlink=temp;			//헤더 노드 교체
			break;
		}

		if(p->rlink==h){	//temp의 key값이 가장 마지막에 올 때 (가장 클 때)
			temp->rlink=h;
			temp->llink=p;
			p->rlink=temp;
			h->llink=temp;
			break;
		}
		else if(key<=p->rlink->key){//temp가 list의 노드 사이에 들어올 때
			temp->llink=p;	//temp를 list에 연결
			temp->rlink=p->rlink;
			
			p->rlink->llink=temp;	//기존의 양 옆 노드들을 temp와 연결
			p->rlink=temp;
			break;
		}
		else if(key>p->rlink->key)	p=p->rlink;	//temp 의key가 다음 값 보다 더 크면 이동
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode *p=h->rlink;
	
	if(p==h){//list 가 비어있다면 다음을 출력
		printf("list is empty now. \n");
		return 0;
	}
	
	while(1){
		if(p->key==key){//값을 찾을 경우
			p->rlink->llink=p->llink;	//해당 노드를 삭제
			p->llink->rlink=p->rlink;
			free(p);
			break;
		}
		else{ p=p->rlink;	//다음 노드로 이동
			if(p==h) {printf("Key is not in list!\n"); break;}//값이 없다면 다음을 출력
			}
	}

	return 0;
}


