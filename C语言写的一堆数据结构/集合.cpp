#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//链表的结构体
typedef struct LinkedList {
	int val;
	LinkedList* next;
}LinkedList;

//用链表实现栈
typedef struct stack {
	LinkedList* table;
	int top; // 感觉这个没啥用
}Stack;


//用链表实现双端队列
typedef struct Deque {
	LinkedList* table;
	int rear;
}Deque;

typedef struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
}TreeNode;


//LinkedList
LinkedList* InitLinkedList() {
	LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
	node->next = NULL;
	node->val = -1;
	return node;
}	

void addLinkedList(LinkedList* head,int val) {
	if (head->next == NULL && head->val == -1) {
		head->val = val;
		return;
	}
	
	LinkedList* cur = head;
	while (cur->next) cur = cur->next;
	LinkedList* temp = InitLinkedList();
	temp->val = val;
	cur->next = temp;
}

bool EmptyLinkedList(LinkedList* head) {
	if (head->next == NULL && head->val == -1) return true;
	else return false;
}

int popLinkedList(LinkedList* head) {
	if (!EmptyLinkedList(head)) {
		printf("current list is empty, do nothing");
		return -1;
	}

	if (head->next == NULL && head->val != -1) {
		int num = head->val;
		head->val = -1;
		return num;
	}

	LinkedList* cur = head;
	while (cur->next->next)cur = cur->next;
	int num = cur->next->val;
	LinkedList* temp = cur->next;
	cur->next = NULL;
	free(temp);
	return num;
}

void DisLinkedList(LinkedList* head) {
	
	if (EmptyLinkedList(head)) printf("the list is empty.\n");
	else {
		LinkedList* cur = head;
		while (cur->next) { 
			printf("%d\n", cur->val);
			cur = cur->next; 
		}
		printf("%d\n", cur->val);
	}
}

//Stack
Stack* InitStack() {
	Stack* stk = (Stack*)malloc(sizeof(Stack));
	stk->table = InitLinkedList();
	stk->top = -1;
	return stk;
}

bool EmptyStack(Stack* stk) {
	return (stk->top == -1);
}

void pushStack(Stack* stk,int val) {
	if (EmptyLinkedList(stk->table)) {
		stk->table->val = val;
		stk->top++;
	}
	else {
		LinkedList* cur = stk->table;
		addLinkedList(cur, val);
		stk->top++;
	}
}

int popStack(Stack* stk) {
	if (EmptyLinkedList(stk->table)) {
		printf("the stack is empty");
		return -1;
	}
	else {
		LinkedList* cur = stk->table;
		if (cur->next == NULL) {
			int num = cur->val;
			cur->val = -1;
			stk->top--;
			return num;
		}
		else {
			while (cur->next->next)cur = cur->next;
			LinkedList* temp = cur->next;
			cur->next = NULL;
			int num = temp->val;
			free(temp);
			stk->top--;
			return num;
		}
	}
}

void DisStack(Stack* stk) {
	if (EmptyLinkedList(stk->table)) {
		printf("the stack is empty.\n");
		return;
	}
	else {
		LinkedList* cur = stk->table;
		while (cur->next) {
			printf("%d\n", cur->val);
			cur = cur->next;
		}
		printf("%d\n", cur->val);
	}
}

int getItemStack(Stack* stk,int item) {
	if (item > stk->top) {
		printf("item out of the range.\n");
		return -1;
	}
	if (EmptyLinkedList(stk->table)) {
		printf("the stack is empty.\n");
		return -1;
	}
	else {
		LinkedList* cur = stk->table;
		for (int i = 0; i < item ;i++) {
			cur = cur->next;
		}
		return cur->val;
	}
}

//queue
Deque* InitDeque() {
	Deque* que = (Deque*)malloc(sizeof(Deque));
	que->table = InitLinkedList();
	que->rear = -1;
	return que;
}

bool EmptyDeque(Deque* que) {
	return (que->rear == -1);
}

void addDeque(Deque* que, int val) {
	if (EmptyDeque(que)) {
		que->table->val = val;
		que->rear++;
	}
	else {
		LinkedList* cur = que->table;
		addLinkedList(cur, val);
		que->rear++;
	}
}

//取出尾元素
int popDeque(Deque* que) {
	if (EmptyDeque(que)) {
		printf("que is empty");
		return -1;
	}
	if (!EmptyDeque(que) && que->table->next == NULL) {
		int num = que->table->val;
		que->table->val = -1;
		que->rear--;
		return num;
	}
	else {
		LinkedList* cur = que->table;
		while (cur->next->next) {
			cur = cur->next;
		}
		LinkedList* temp = cur->next;
		cur->next = NULL;
		int num = temp->val;
		free(temp);
		que->rear--;
		return num;
	}
}

//poll：取出头元素
int poll(Deque* que) {
	if (EmptyDeque(que)) {
		printf("the queue is empty");
		return -1;
	}
	else {
		if (!EmptyDeque(que) && que->table->next == NULL) {
			int num = que->table->val;
			que->table->val = -1;
			return num;
		}
		LinkedList* temp = que->table;
		int num = temp->val;
		que->table = que->table->next;
		free(temp);
		return num;
	}
}

//TreeNode:
//-----------------------------------------------------------------


typedef struct TLinkedList {
	TreeNode* tree;
	TLinkedList* next;
}TLinkedList;

typedef struct Tstack {
	TLinkedList* table;
	int top; // 感觉这个没啥用
}Tstack;

typedef struct Tdeque {
	TLinkedList* table;
	int rear;
}Tdeque;



TLinkedList* InitTLinkedList() {
	TLinkedList* node = (TLinkedList*)malloc(sizeof(TLinkedList));
	node->next = NULL;
	node->tree = NULL;
	return node;
}

bool EmptyTLinkedList(TLinkedList* Thead) {
	if (Thead->next == NULL && !Thead->tree) return true;
	else return false;
}

void addTLinkedList(TLinkedList* head, TreeNode* val) {
	if (EmptyTLinkedList(head)) {
		head->tree = val;
	}
	else {
		TLinkedList* cur = head;
		while (cur->next)cur = cur->next;
		TLinkedList* node = InitTLinkedList();
		node->tree = val;
		cur->next = node;
	}
}

TreeNode* popT(TLinkedList* head) {
	if (EmptyTLinkedList(head)) {
		printf("the list is empty and return NULL\n");
		return NULL;
	}
	else if (head->next == NULL && head->tree) {
		TreeNode* node = head->tree;
		head->tree = NULL;
		return node;
	}
	else {
		TLinkedList* cur = head;
		while (cur->next->next)cur = cur->next;
		TLinkedList* temp = cur->next;
		cur->next = NULL;
		TreeNode* node = temp->tree;
		free(temp);
		return node;
	}
}


Tdeque* InitTdeque() {
	Tdeque* que = (Tdeque*)malloc(sizeof(Tdeque));
	que->table = InitTLinkedList();
	que->rear = -1;
	return que;
}

bool EmptyTDeque(Tdeque* que) {
	return (que->rear == -1);
}

void pushTdeque(Tdeque* que, TreeNode* val) {
	if (EmptyTDeque(que)) {
		/*que->table = InitTLinkedList();*/
		que->table->tree = val;
		que->rear++;
	}
	else {
		TLinkedList* cur = que->table;
		addTLinkedList(cur, val);
		que->rear++;
	}
}

TreeNode* popTdeque(Tdeque* que) {
	if (EmptyTDeque(que)) {
		printf("the que is empty\n");
		return NULL;
	}
	else {
		if (que->rear == 1) {
			TreeNode* temp = que->table->tree;
			que->table->tree = NULL;
			que->rear--;
			return temp;
		}
		else {
			TLinkedList* cur = que->table;
			while (cur->next->next) {
				cur = cur->next;
			}
			TLinkedList* temp = cur->next;
			TreeNode* node = temp->tree;
			cur->next = NULL;
			free(temp);
			return node;
		}
	}
}

TreeNode* pollTdeque(Tdeque* que) {
	if (EmptyTDeque(que)) {
		printf("the que is empty.\n");
		return NULL;
	}
	else {
		if (que->rear == 0) {
			TreeNode* one = que->table->tree;
			que->table->tree = NULL;
			que->rear--;
			return one;
		}
		else {
			TLinkedList* temp = que->table;
			TreeNode* one = temp->tree;
			que->table = que->table->next;
			que->rear--;
			free(temp);
			return one;
		}
	}
}

int getTdequeLength(Tdeque* que) {
	return que->rear + 1;
}

Tstack* InitTstack() {
	Tstack* Tstk = (Tstack*)malloc(sizeof(Tstack));
	Tstk->table = InitTLinkedList();
	Tstk->top = -1;
	return Tstk;
}

bool EmptyTstack(Tstack* Tstk) {
	return (Tstk->top == -1);
}

void pushTStack(Tstack* stk, TreeNode* tree) {
	if (EmptyTstack(stk)) {
		stk->table->tree = tree;
		stk->top++;
	}
	else {
		TLinkedList* cur = stk->table;
		addTLinkedList(cur, tree);
		stk->top++;
	}
}

TreeNode* popTstack(Tstack* stk) {
	if (EmptyTstack(stk)) {
		printf("the stack is empty.\n");
		return NULL;
	}
	else {
		if (stk->table->next == NULL && stk->table->tree != NULL) {
			TreeNode* temp = stk->table->tree;
			stk->table->tree = NULL;
			stk->top--;
			return temp;
		}
		else {
			TLinkedList* cur = stk->table;
			while (cur->next->next) {
				cur = cur->next;
			}
			TLinkedList* temp = cur->next;
			cur->next = NULL;
			TreeNode* node = temp->tree;
			free(temp);
			stk->top--;
			return node;
		}
	}
}


TreeNode* InitTreeNode() {
	TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode));
	tree->left = NULL;
	tree->right = NULL;
	tree->val = -1;
	return tree;
}


void addManyNode(TreeNode* tree) {

}


//-----------------front------------------------
void FrontOreder(TreeNode* tree) {
	if (tree == NULL)return;
	printf("%d ", tree->val);
	FrontOreder(tree->left);
	FrontOreder(tree->right);
}

void FrontOrederWithStack(TreeNode* tree) {
	if (tree == NULL) return;
	Tstack* stk = InitTstack();
	pushTStack(stk, tree);
	while (!EmptyTstack(stk)) {
		TreeNode* cur = popTstack(stk);
		printf("%d ", cur->val);
		if(cur->right)pushTStack(stk, cur->right);
		if(cur->left)pushTStack(stk, cur->left);
	}
}
//-----------------front------------------------

void layerOrder(TreeNode* tree) {
	if (tree == NULL) return;
	Tdeque* que = InitTdeque();
	pushTdeque(que,tree);
	while (!EmptyTDeque(que)) {
		int len = getTdequeLength(que);
		for (int i = 0; i < len; i++) {
			TreeNode* node = pollTdeque(que);
			printf("%d ", node->val);
			if (node->left) pushTdeque(que, node->left);
			if (node->right) pushTdeque(que, node->right);
		}
	}

}

int main(void) {
	/*LinkedList* head = InitLinkedList();
	addLinkedList(head, 21);
	addLinkedList(head, 42);
	addLinkedList(head, 521);
	DisLinkedList(head);
	printf("%d ", popLinkedList(head));
	DisLinkedList(head);*/
	//以上是链表的基本测试

	/*Stack* stk = InitStack();
	pushStack(stk, 21);
	pushStack(stk, 42);
	pushStack(stk,521);
	pushStack(stk, 21);
	DisStack(stk);
	printf("%d,%d\n",popStack(stk),stk->top);
	printf("%d,%d\n", popStack(stk), stk->top);
	printf("%d,%d\n", popStack(stk), stk->top);
	printf("%d,%d\n", popStack(stk), stk->top);
	printf("%d,%d\n", popStack(stk), stk->top);
	printf("%d,%d\n", popStack(stk), stk->top);*/

	//above is test on stack class
	/*Deque* que = InitDeque();
	addDeque(que, 21);
	addDeque(que, 42);
	addDeque(que, 521);
	int a=popDeque(que);
	int b = poll(que);*/
	//above is test on deque

	/*TreeNode* tree = InitTreeNode();
	tree->val = 18;
	tree->left = InitTreeNode();
	tree->left->val = 21;
	tree->left->left = InitTreeNode();
	tree->left->left->val = 54;
	tree->left->right = InitTreeNode();
	tree->left->right->val = 36;
	tree->right = InitTreeNode();
	tree->right->val = 42;
	tree->right->right = InitTreeNode();
	tree->right->right->val = 21;
	FrontOrederWithStack(tree);
	printf("\n");
	FrontOreder(tree);
	printf("\n");
	layerOrder(tree);*/
	//above is the test on tree with thery impletments(stack and deque)
	
	return 0;
}
