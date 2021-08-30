//
//  main.c
//  todoList
//
//  Created by 안동규 on 2021/08/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    struct node *next;
    char title[1000];
    char content[1000];
}todo;

todo *head=NULL;

int countTodo(todo *head)
{
    int count=0;
    todo *curr=head;
    while(curr!=NULL){
        curr=curr->next;
        count++;
    }
    return count;
}

todo *creatTodo(char str1[], char str2[])
{
    int count=0;

    todo *newTodo=(todo*)malloc(sizeof(todo));
    stpcpy(newTodo->title, str1);  // 할당x 복사o 문자열은 읽기 전용에 할당된다.
    stpcpy(newTodo->content, str2);  // 이유는 content와 title이 포인터 상수이기 때문이다.
    newTodo->next=NULL;
    
    return newTodo;
}

void connectTodo(todo **head, todo *newTodo)
{
    if(*head==NULL){
        *head=newTodo;
    }
    else{
        todo *temp=*head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=newTodo;
    }
}

void insertTodo(todo **head, todo *newTodo, int index)
{
    if(index==0 || index==1){
        newTodo->next=*head;
        *head=newTodo;
    }
    else{
        todo *temp=*head;
        while(1<(--index)){
            temp=temp->next;
        }
        newTodo->next=temp->next;
        temp->next=newTodo;
    }
}

void showTodo(todo *head)
{
    todo *curr=head;
    if(curr==NULL){
        printf("\n목록이 비어있습니다.\n\n");
    }
    else{
        curr=head;
        while(curr!=NULL){
            printf("title : %s\n", curr->title);
            printf("content : %s\n\n", curr->content);
            curr=curr->next;
        }
    }
}

void writeTodo()
{
    char str1[1000];
    char str2[1000];
    char rep;
    todo *newTodo;
    
    while(1){
        fflush(stdin);
        printf("제목 : ");
        fgets(str1, 1000, stdin);
        printf("내용 : ");
        fgets(str2, 1000, stdin);
        printf("\n<입력목록 확인>\n제목 : %s\n내용 : %s\n", str1, str2);
        
        printf("\n이대로 목록을 생성할까요?(y/n) : ");
        scanf("%c", &rep);
        
        if(rep=='n')
            continue;
        else
            break;
    }
    printf("\n<반복문 탈출 후 입력목록 확인>\n제목 : %s\n내용 : %s\n", str1, str2);
    
    newTodo=creatTodo(str1, str2);
    printf("\n<노드에 할당이 잘 되었는지 입력목록 확인>\n제목 : %s\n내용 : %s\n", newTodo->title, newTodo->content);
    
    // 목록 구조체 연결
    if(head==NULL){
        printf("\n첫 목록을 생성하였습니다.\n");
        connectTodo(&head, newTodo);
    }
    else{
        int i=0;
        printf("\n몇 번째로 할 일을 추가할까요? : ");
        scanf("%d", &i);
        insertTodo(&head, newTodo, i);
    }
    
    printf("\n<구조체 연결이 잘 되었는지>현재 목록은 다음과 같습니다.\n");
    showTodo(head);
}

void deleteTodo(todo **head, int index)
{
    // 먼저 삭제할 친구를 index를 이용해서 찾고,
    todo *temp=*head;
    while(temp!=NULL && 0<(--index)){
        temp=temp->next;
    }
    // 찾은 temp를 이용해서, 그 값이 첫째값인지 아닌지에 따라, 다음 값으로 이어주자.
    if(temp==*head){
        *head=temp->next;
    }
    else{
        // 직전 노드를 찾아주자.
        todo *curr=*head;
        while(curr!=NULL && curr->next!=temp){
            curr=curr->next;
        }
        curr->next=temp->next;
    }
    free(temp);
}

int main()
{
    int answer=0;
    int count=0;
    char str1[1000];
    char str2[1000];
    
    printf("환영합니다. vsc에서 C로 만들다가 지쳐서 오셨군요.\n여기서 성공하실겁니다!\n");
    printf("\t아무키나 입력하세요\n\n");
    getchar();

    while(1)
    {
        printf("1. 현재 목록을 확인\n");
        printf("2. 할 일 추가\n");  // 중간에 추가하거나, 가장 맨 뒤에 추가하거나.
        printf("3. 할 일 삭제\n");
        printf("4. 목록 초기화\n");
        printf("5. 나가기\n");
        printf("번호를 입력해주세요(1~5) : ");
        scanf("%d", &answer);
        if(answer<1 || answer>5){
            printf("\n\n다시 입력해주세요(1~5)\n\n");
            continue;
        }
        printf("\n\n");

        switch(answer)
        {
            case 1:
                showTodo(head);
                break;
            case 2:
                writeTodo();
                break;
            case 3:
                printf("현재 목록입니다.\n");
                showTodo(head);
                count=0;
                printf("몇 번째 항목을 삭제할까요? : ");
                scanf("%d", &count);
                printf("\n");
                deleteTodo(&head, count);
                break;
            case 4:
                count=countTodo(head);
                printf("총 할일은 %d개 입니다.\n\n\n",count);
                todo *curr=head;
                while(curr!=NULL){
                    todo *currNext=curr->next;
                    printf("이번에 해제할 title : %s\n", curr->title);
                    free(curr);
                    curr=currNext;
                }
                head=NULL;
                break;
            case 5:
                exit(0);
        }
    }
    
    return 0;
}
