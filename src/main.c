#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MIN(x, y) x < y ? x : y

typedef struct node* Node;
typedef struct qnode* Qnode;
typedef struct queue* Queue;
typedef struct binarytree* BinaryTree;
typedef struct travnode* TravNode;
typedef struct travQ* TravQ;

struct node {
    char data;
    Node left;
    Node right;
};

Node createNode(char data) {
    Node newNode = (Node)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct qnode {
    Node ptr;
    Qnode next;
};

struct queue {
    Qnode front, rear;
};

struct queue createQueue() {
    Queue q = (Queue)malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return *q;
}

Qnode createQnode(Node ptr) {
    Qnode newNode = (Qnode)malloc(sizeof(struct qnode));
    newNode->ptr = ptr;
    newNode->next = NULL;
    return newNode;
}

void enQueue(Queue q, Node n) { 
    Qnode temp = createQnode(n); 
 
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
    } 
  
    q->rear->next = temp; 
    q->rear = temp; 
}

void deQueue(Queue q) { 
    if (q->front == NULL) 
        return; 
  
    Qnode temp = q->front; 
    q->front = q->front->next; 
  
    if (q->front == NULL) 
        q->rear = NULL; 
  
    free(temp); 
}

struct binarytree {
    Node root;
    struct queue q, tq;
};

BinaryTree createBT() {
    BinaryTree newBT = (BinaryTree)malloc(sizeof(struct binarytree));
    newBT->root = NULL;
    newBT->q = createQueue();
    newBT->tq = createQueue();
    return newBT;
}

void addTreeNode(BinaryTree bt, char data) {  // ---- O(1)
    Node tmp = createNode(data);
    if(bt->root == NULL) {
        bt->root = tmp;
    }
    else if (bt->q.front->ptr->left == NULL) {
        bt->q.front->ptr->left = tmp; 
    }

    else {
        bt->q.front->ptr->right = tmp;
        deQueue(&bt->q);
    }
    enQueue(&bt->q, tmp);
}

void createLevelTree(BinaryTree bt, char* message) {   // ---- O(n)
    for(int i=0; *(message+i) != '\0'; i++) {
        addTreeNode(bt, *(message + i));
    }
}

void swapChild(Node temp, int level) {     // ---- O(n)
    char data;
	if(temp->right != NULL){
        if(level % 2 != 0) {
        data = temp->left->data;
        temp->left->data = temp->right->data;
        temp->right->data = data;
        }
		swapChild(temp->left, level+1);
        swapChild(temp->right, level+1);
    }
	return;
}

void levelTraversal(BinaryTree bt, char* message) {  // ---- O(n) 
    strcpy(message, "");
	enQueue(&bt->tq, bt->root);
	while(bt->tq.front != NULL) {
		strncat(message, &bt->tq.front->ptr->data, 1); 
        if(bt->tq.front->ptr->left != NULL) {
            enQueue(&bt->tq, bt->tq.front->ptr->left);
        }
        if(bt->tq.front->ptr->right != NULL) {
            enQueue(&bt->tq, bt->tq.front->ptr->right);
        }
        deQueue(&bt->tq);
	}
}

void preOrderTraversal(Node nodeOrg, char* message) {  // ---- O(n) 
    if(nodeOrg == NULL) {
        return;
    }
    strncat(message, &nodeOrg->data, 1);
    preOrderTraversal(nodeOrg->left, message);
    preOrderTraversal(nodeOrg->right, message);
}

struct travnode {
    int idx, size;
    TravNode next;
};

struct travQ {
    TravNode front, rear;
};

struct travQ createTravQ() {
    TravQ q = (TravQ)malloc(sizeof(struct travQ));
    q->front = q->rear = NULL;
    return *q;
}

TravNode createTnode(int idx, int size) {
    TravNode newNode = (TravNode)malloc(sizeof(struct travnode));
    newNode->idx = idx;
    newNode->size = size;
    newNode->next = NULL;
    return newNode;
}

void enqueueTnode(TravQ q, int i, int size) { 
    TravNode temp = createTnode(i, size); 
 
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        return;
    } 
  
    q->rear->next = temp; 
    q->rear = temp; 
}

TravNode dequeueTnode(TravQ q) { 
    if (q->front == NULL) 
        return NULL; 
  
    TravNode temp = q->front; 
    q->front = q->front->next; 
  
    if (q->front == NULL) 
        q->rear = NULL; 
    
    return temp;
}

int leftTreeSize(int n) {
    if(n <= 1) return 0;
    
    int ans, l, lastLvlNodes;
    l = (int)log2(n+1);
    ans = pow(2, l-1);
    lastLvlNodes = MIN((n - pow(2, l) + 1), ans);
    return ans + lastLvlNodes - 1;
}

void preToLevel(char *message, char *ans) {  // ---- O(n)
    strcpy(ans, "");
    int len = strlen(message);
    struct travQ q = createTravQ();
    enqueueTnode(&q, 0, len);
    while(q.front != NULL) {
        TravNode tmp = dequeueTnode(&q);
        int iroot = tmp->idx;
        int size = tmp->size; 
        if(iroot >= len || size == 0) {
            continue;
        } else {
		    strncat(ans, &message[iroot], 1); 
        }
        int lf = leftTreeSize(size); 
        enqueueTnode(&q, iroot+1, lf);
        enqueueTnode(&q, iroot+1+lf, size-lf-1);
    } 
}


/////////////////////// Encryption And Decryption ////////////////////////////

void stage1Encrypt(char* message, int type) { //  ---- O(n)
    int ch, shift;
    if(type == 1) {
        for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                shift = ((ch + (i-1)) - 32)%95 + 32;
                *(message + i-1) = (char)shift;
            } 
            else {
                shift = ((ch + (i+1)) - 32)%95 + 32;
                *(message + i-1) = (char)shift; 
            }
        }
    } 
    else if(type == 2) {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                shift = ((ch + (i-1)) - 32)%95 + 32;
                *(message + i-1) = (char)shift;
            } 
            else {
                shift = ((ch + (i+2)) - 32)%95 + 32;
                *(message + i-1) = (char)shift;
            }
        }
    }
    else {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                shift = ((ch + (i-3)) - 32)%95 + 32;
                *(message + i-1) = (char)shift;
            } 
            else {
                shift = ((ch + (i+2)) - 32)%95 + 32;
                *(message + i-1) = (char)shift;
            }
        }
    }
}

void stage2Encrypt(char* data, char* message) { // ---- O(n)
	BinaryTree tree = createBT();
	createLevelTree(tree, data);
	swapChild(tree->root, 0);
    strcpy(message, "");
    preOrderTraversal(tree->root, message);
}

void encrypt(char* data, char* message, int type) { // ---- O(n)
	if(sizeof(data) == 0){
		printf("ERROR : No data found\n");
		strcpy(message, "");
	}
	stage1Encrypt(data, type);
    stage2Encrypt(data, message);
}

void stage1Decrypt(char* data, char* message) { // ---- O(n)
    preToLevel(data, message);
    BinaryTree tree = createBT();
    createLevelTree(tree, message);
	swapChild(tree->root, 0);
    levelTraversal(tree, message);
}

void stage2Decrypt(char* message, int type) {  // ---- O(n)
    int ch, shift;
    if(type == 1) {
        for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                shift = ((ch - (i-1) + 20 * 95) - 32)%95 + 32;
                *(message + i-1) = (char)(shift);
            } 
            else {
                shift = ((ch - (i+1) + 20 * 95) - 32)%95 + 32;
                *(message + i-1) = (char)(shift);
            }
        }
    } 
    else if(type == 2) {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                shift = ((ch - (i-1) + 20 * 95) - 32)%95 + 32;
                *(message + i-1) = (char)(shift);
            } 
            else {
                shift = ((ch - (i+2) + 20 * 95) - 32)%95 + 32;
                *(message + i-1) = (char)(shift);
            }
        }
    }
    else {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                shift = ((ch - (i-3) + 20 * 95) - 32)%95 + 32;
                *(message + i-1) = (char)(shift);
            } 
            else {
                shift = ((ch - (i+2) + 20 * 95) - 32)%95 + 32;
                *(message + i-1) = (char)(shift);
            }
        }
    }
}

void decrypt(char* data, char* message, int type) { // ---- O(n)
	if(sizeof(data) == 0){
		printf("ERROR : No data found\n");
		strcpy(message, "");
	}
	stage1Decrypt(data, message);
	stage2Decrypt(message, type);
}

int main() {
    char data[900], message[900];
    int ch, type;

    while(1) {

        printf("\n\n-----------MENU-------------\n\n");
        printf("1.Encryption\n");
        printf("2.Decryption\n");
        printf("3.Exit\n\n");
        printf("Enter the choice: ");
        scanf("%d", &ch);
        fflush(stdin);

        switch (ch) {
        case 1:
            {
                strcpy(data, "");
                printf("\n----Encryption----\n");
                printf("Enter a string: ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                printf("\nEnter the type of encryption (1-3): ");
                scanf("%d", &type);
                fflush(stdin);
                encrypt(data, message, type);
                printf("\n\nEncrypted Message: %s\n", message);
                break;
            }
        case 2:
            {
                strcpy(data, "");
                printf("\n----Decryption----\n");
                printf("Enter Encrypted string: ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                printf("\nEnter the encrypted type (1-3): ");
                scanf("%d", &type);
                fflush(stdin);
                decrypt(data, message, type);
                printf("\n\nDecrypted Message: %s\n", message);
                break;

            }
        case 3:
            {
                exit(0);
            }
        default:
            {
                printf("Invalid choice... Try Again!\n");
            }
        }
    }
    return 0;
}
