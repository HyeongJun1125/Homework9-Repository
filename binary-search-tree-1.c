/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node **h);

/* functions that you have to implement */
void inorderTraversal(Node *ptr);			/* recursive inorder traversal */
void preorderTraversal(Node *ptr);			/* recursive preorder traversal */
void postorderTraversal(Node *ptr);			/* recursive postorder traversal */
int insert(Node *head, int key);			/* insert a node to the tree */
int deleteLeafNode(Node *head, int key);	/* delete the leaf node for the key */
Node *searchRecursive(Node *ptr, int key);	/* search the node for the key */
Node *searchIterative(Node *head, int key); /* search the node for the key */
int freeBST(Node *head);					/* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	printf("\n2021041069 조형준");
	char command;
	int key;
	Node *head = NULL;
	Node *ptr = NULL; /* temp */

	do
	{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z':
		case 'Z':
			initializeBST(&head);
			break;
		case 'q':
		case 'Q':
			freeBST(head);
			break;
		case 'n':
		case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f':
		case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's':
		case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i':
		case 'I':
			inorderTraversal(head->left);
			break;
		case 'p':
		case 'P':
			preorderTraversal(head->left);
			break;
		case 't':
		case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node **h)
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node *)malloc(sizeof(Node));
	(*h)->left = NULL; /* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node *ptr) // 중위 순회
{
	// ptr : head->left
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left);  // 트리와 동일하게 왼쪽 먼저
		printf("[%d] ", ptr->key);	  // 중앙 노드
		inorderTraversal(ptr->right); // 오른쪽 자식 노드
	}
}

void preorderTraversal(Node *ptr) // 전위 순회
{
	if (ptr != NULL)
	{
		printf("[%d] ", ptr->key);	   // 중앙 노드
		preorderTraversal(ptr->left);  // 왼쪽 자식 노드
		preorderTraversal(ptr->right); // 오른쪽 자식 노드
	}
}

void postorderTraversal(Node *ptr) // 후위 순회
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);	// 왼쪽 자식 노드
		postorderTraversal(ptr->right); // 오른쪽 자식 노드
		printf("[%d] ", ptr->key);		// 중앙 노드
	}
}

int insert(Node *head, int key) // 삽입
{
	Node *newNode = (Node *)malloc(sizeof(Node)); // 추가할 노드를 새로 동적 할당
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	Node *prev = NULL;
	Node *ptr = head->left; // 찐 root는 head->left

	if (ptr == NULL)
	{
		// ***** ptr=newNode를 해서 안된 이유 :
		// ptr은 head->left를 가리키는 노드와 같은 값을 가리키지만
		// ptr이 newNode를 가리킬 뿐 head와는 독립시행이므로
		head->left = newNode;
		return 0;
	}

	while (ptr) // 가리키는 값이 존재하는 동안
	{
		prev = ptr;
		if (newNode->key < ptr->key)	  // ptr의 값보다 작으면
			ptr = ptr->left;			  // 왼쪽으로
		else if (newNode->key > ptr->key) // ptr의 값보다 크다면
			ptr = ptr->right;			  // 오른쪽으로
		else							  // 이미 들어있는 값과 동일하다면
			return 0;					  // 종료
	}
	// 탐색을 종료했을 때 ptr : NULL, prev : 마지막 노드
	if (newNode->key < prev->key) // 마지막 노드의 값보다 작다면
		prev->left = newNode;	  // 왼쪽 자식 노드로 이어주고
	else						  // 크다면
		prev->right = newNode;	  // 오른쪽 자식 노드에 이어줌
	return 0;
}

int deleteLeafNode(Node *head, int key) // 끝 노드의 삭제
{
	Node *ptr = head->left;
	Node *prev = NULL;

	if (ptr == NULL) // head에 값이 존재하지 않을 경우
		return 0;

	while (ptr && ptr->key != key) // head에 값이 존재하며 key값을 발견할 때까지 반복.
	{
		prev = ptr;
		if (key < ptr->key)	  // head에서부터 key가 가리키는 key보다 작으면
			ptr = ptr->left;  // 왼쪽으로 이동
		else				  // 그렇지 않으면 (클 경우)
			ptr = ptr->right; // 오른쪽으로 이동
	}

	// 탐색이 종료되도록 값을 찾지 못하거나, key값을 찾았을 경우로 Case 분리.

	// ***** ptr == NULL 인 조건문이 key값을 찾은 경우보다 먼저 나와야 하는 이유 :
	// ptr->key == key인 경우 만약 ptr==NULL이면 오류 발생.
	// 따라서 반드시 선행되어야 함.

	if (ptr == NULL) // 값을 찾지 못했을 경우
	{
		printf("The node [%d] does not exist\n", key);
		return 0;
	}

	// 어차피 Two case라 위에서 걸러지지 않으면
	//  ptr->key == key인 상태이므로
	// 굳이 if를 안써도 되지만 가독성을 위해 삽입.

	if (ptr->key == key) // 값을 찾았을 경우
	{
		if (ptr->left != NULL || ptr->right != NULL) // 자식이 있으면
		{
			printf("The node [%d] is not a leaf node\n", key); // 끝 노드가 아니므로 삭제 불가
			return 0;
		}
		else // 자식이 없는 경우
		{
			if (prev->left == ptr) // 이전 노드의 왼쪽 자식이 ptr이면
				prev->left = NULL; // 이전 노드의 왼쪽 자식을 NULL로
			else
				prev->right = NULL; // 이전 노드의 오른쪽 자식을 NULL로
			free(ptr);				// ptr을 해제

			//*** 그냥 free(ptr)만을 해도 괜찮지만
			// prev가 여전히 left와 right를 가리키게 되므로
			// prev에서 좌우 좌식을 가리키지 않게 하고 ptr을 해제.
		}
	}
	return 0;
}

// 전중후위 탐색과 동일하게 재귀적인 방법
Node *searchRecursive(Node *ptr, int key)
{
	if (ptr == NULL)
		return NULL;
	if (key == ptr->key) // 찾았을 경우
		return ptr;		 // 반환
	else if (key < ptr->key)
		return searchRecursive(ptr->left, key); // 찾을 때까지 왼쪽으로
	else
		return searchRecursive(ptr->right, key); // 찾을 때까지 오른쪽으로
}

Node *searchIterative(Node *head, int key)
{
	Node *ptr = head->left;
	while (ptr) // 값이 존재하는 동안 반복
	{
		if (key < ptr->key)
			ptr = ptr->left;
		else if (key > ptr->key)
			ptr = ptr->right;
		else
			return ptr;
	}
	// 존재하지 않을 경우
	return NULL;
}

int freeBST(Node *head) // 트리의 동적 할당 해제
{
	Node *ptr = head->left;
	if (ptr != NULL)
	{
		freeBST(ptr->left);	 // 왼쪽 서브트리를 삭제
		freeBST(ptr->right); // 오른쪽 서브트리를 삭제
		free(ptr);			 // 현재 노드를 삭제
	}
	free(head); // head를 삭제
	return 0;
}
