#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

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

void swapLevel(Node temp, int level) {     // ---- O(n)
    char data;
	if(temp->right != NULL){
		if(level % 2 == 0){
			data = temp->left->data;
            temp->left->data = temp->right->data;
            temp->right->data = data;
		}
		swapLevel(temp->left, level+1);
        swapLevel(temp->right, level+1);
	}
	return;
}

void swapAlter(BinaryTree bt) {  // ---- O(n)
	if(bt->root != NULL) {
        swapLevel(bt->root, 0);
    }
}

void mirror(Node node) {   //  ---- O(n)
    if(node == NULL)
        return;
    else
    {
        mirror(node->left);
        mirror(node->right);
        
        Node temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}

void mirrorTree(BinaryTree bt){  // ---- O(n)
	if(bt->root != NULL) {
		mirror(bt->root);
    }
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

void recur(Node temp, int space) { // ---- O(n) 
    if(temp->right != NULL){
        recur(temp->right, space + 1);
    }
    for(int i=0;i<space;i++)
        printf("\t");
    printf("%c\n", temp->data);

    if(temp->left != NULL){
        recur(temp->left, space + 1);
    }

    return;
}

void print(struct binarytree bt) {  // ---- O(n)
    recur(bt.root, 0);
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

int left_tree_size(int n) {
    if(n <= 1) return 0;
    
    int ans, l, last_level_nodes;
    l = (int)log2(n+1);
    ans = pow(2, l-1);
    last_level_nodes = MIN((n - pow(2, l) + 1), ans);
    return ans + last_level_nodes - 1;
}

void preToLevel(char *message, char *ans) {
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
        int lf = left_tree_size(size); 
        enqueueTnode(&q, iroot+1, lf);
        enqueueTnode(&q, iroot+1+lf, size-lf-1);
    } 
}

/////////////////////// Encryption And Decryption ////////////////////////////

void firstLevelEncrypt(char* message, int type) {  //  ---- O(n)
    int ch;
    if(type == 1) {
        for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                *(message + i-1) = ((ch + (i-1)) - 32)%95 + 32;
            } 
            else {
                *(message + i-1) = ((ch + (i+1)) - 32)%95 + 32;
            }
        }
    } 
    else if(type == 2) {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                *(message + i-1) = ((ch + (i-1)) - 32)%95 + 32;
            } 
            else {
                *(message + i-1) = ((ch + (i+2)) - 32)%95 + 32;
            }
        }
    }
    else {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                *(message + i-1) = ((ch + (i-8)) - 32)%95 + 32;
            } 
            else {
                *(message + i-1) = ((ch + (i+5)) - 32)%95 + 32;
            }
        }
    }
}

void secondLevelEncrypt(char* message) { // ---- O(n)
	BinaryTree tree = createBT();
	createLevelTree(tree, message);
	swapAlter(tree);
    mirrorTree(tree);
    levelTraversal(tree, message);
}

void encrypt(char* message, int type) { // ---- O(n)
	if(sizeof(message) == 0){
		printf("ERROR : No data found\n");
		strcpy(message, "");
	}
	firstLevelEncrypt(message, type);
	secondLevelEncrypt(message);
}

void encryption(char* data, char* message, int type) {
	if(sizeof(data) == 0){
		printf("ERROR : No data found\n");
		strcpy(message, "");
        return;
	}
    
	firstLevelEncrypt(data, type);
	BinaryTree tree = createBT();
	createLevelTree(tree, data);
	swapAlter(tree);
    strcpy(message, "");
    preOrderTraversal(tree->root, message);
}


void firstLevelDecrypt(char* message) { // ---- O(n)
	BinaryTree tree = createBT();
	createLevelTree(tree, message);
	swapAlter(tree);
    mirrorTree(tree);
    levelTraversal(tree, message);
}

void secondLevelDecrypt(char* message, int type) {  // ---- O(n)
    int ch;
    if(type == 1) {
        for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                *(message + i-1) = ((ch - (i-1) + 12 * 95) - 32)%95 + 32;
            } 
            else {
                *(message + i-1) = ((ch - (i+1) + 12 * 95) - 32)%95 + 32;
            }
        }
    } 
    else if(type == 2) {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                *(message + i-1) = ((ch - (i-1) + 12 * 95) - 32)%95 + 32;
            } 
            else {
                *(message + i-1) = ((ch - (i+2) + 12 * 95) - 32)%95 + 32;
            }
        }
    }
    else {
         for(int i=1; i <= strlen(message); i++){
            ch = (int)(*(message + i-1));
            if(i%2 == 0) {
                *(message + i-1) = ((ch - (i-8) + 12 * 95) - 32)%95 + 32;
            } 
            else {
                *(message + i-1) = ((ch - (i+5) + 12 * 95) - 32)%95 + 32;
            }
        }
    }
}

void decrypt(char* message, int type) { // ---- O(n)
	if(sizeof(message) == 0){
		printf("ERROR : No data found\n");
		strcpy(message, "");
	}
	firstLevelDecrypt(message);
	secondLevelDecrypt(message, type);
}

void decryption(char* message, char* lvlOrder, int type) {
	if(sizeof(message) == 0){
		printf("ERROR : No data found\n");
		strcpy(message, "");
        return;
	}

    preToLevel(message, lvlOrder);
    BinaryTree tree = createBT();
    createLevelTree(tree, lvlOrder);
    swapAlter(tree);
    //mirrorTree(tree);
    levelTraversal(tree, lvlOrder);
    secondLevelDecrypt(lvlOrder, type);
}

int main() {
    char data[900], message[900];
    int ch, type;

    while(1) {

        printf("\n\n-----------MENU-------------\n\n");
        printf("1.Encryption\n");
        printf("2.Decryption\n");
        printf("3.Exit\n");
        printf("4.Check\n");
        printf("5.Check1\n\n");
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
                //strcpy(message, data);
                printf("Enter the type of encryption(1-3): ");
                scanf("%d", &type);
                fflush(stdin);
                //encrypt(message, type);
                encryption(data, message, type);
                printf("\nEncrypted Message: %s\n", message);
                break;
            }
        case 2:
            {
                strcpy(data, "");
                printf("\n----Decryption----\n");
                printf("Enter Encrypted string: ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                //strcpy(message, data);
                printf("Enter the encrypted type(1-3): ");
                scanf("%d", &type);
                fflush(stdin);
                //int len = strlen(data);
                //printf("%s -- %d\n", data, len);
                //char test[900];
                //preToLevel(data, test);
                //printf("lvlTraversal: %s\n", test);
                //break;
                //decrypt(message, type);
                decryption(data, message, type);
                printf("\nDecrypted Message: %s\n", message);
                break;

            }
        case 3:
            {
                exit(0);
            }
        case 4:
            {
                strcpy(data, "");
               // BinaryTree BT = createBT();
                printf("\n----Encryption----\n");
                printf("Enter a string: ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                //strcpy(message, "");
                //createLevelTree(BT, data);
                //preOrderTraversal(BT->root, message);
                //printf("preTraversal: %s\n", message);
                /*
                strcpy(message, "");
                inOrderTraversal(BT->root, message);
                printf("inTraversal: %s\n", message);
                strcpy(message, "");
                preOrderTraversal(BT->root, message);
                inOrderTraversal(BT->root, message);
                printf("JoinTraversal: %s\n", message);
                int len = strlen(message);
                printf("JoinTraversal Len: %d\n", len);
                char inord[300], preord[300];
                split(message, inord, preord);
                printf("preTraversal: %s\n", preord);
                printf("inTraversal: %s\n", inord);
                */
                char test[900];
                preToLevel(data, test);
                printf("lvlTraversal: %s\n", test);
                break;
            }
        case 5:
            {
                strcpy(data, "");
                BinaryTree BT = createBT();
                printf("\n----Encryption----\n");
                printf("Enter a string: ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                createLevelTree(BT, data);
                strcpy(message, "");
                preOrderTraversal(BT->root, message);
                strcpy(message, "");
                printf("preTraversal: %s\n", message);
                break;
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
