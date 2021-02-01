#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef struct qin* Qin;

struct qin {
    int idx, size;
    Qin next;
};

typedef struct qtree* qTree;
struct qtree {
    Qin front, rear;
};

struct qtree createqTree() {
    qTree q = (qTree)malloc(sizeof(struct qtree));
    q->front = q->rear = NULL;
    return *q;
}

Qin createQin(int idx, int size) {
    Qin newNode = (Qin)malloc(sizeof(struct qin));
    newNode->idx = idx;
    newNode->size = size;
    newNode->next = NULL;
    return newNode;
}

void enqueueQin(qTree q, int i, int size) { 
    Qin temp = createQin(i, size); 
 
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        return;
    } 
  
    q->rear->next = temp; 
    q->rear = temp; 
}

Qin deQueueQin(qTree q) { 
    if (q->front == NULL) 
        return NULL; 
  
    Qin temp = q->front; 
    q->front = q->front->next; 
  
    if (q->front == NULL) 
        q->rear = NULL; 
    
    return temp;
    //free(temp); 
}
/*
def level_to_pre(arr,ind,new_arr):
    if ind>=len(arr): return new_arr #nodes at ind don't exist
    new_arr.append(arr[ind]) #append to back of the array
    new_arr = level_to_pre(arr,ind*2+1,new_arr) #recursive call to left
    new_arr = level_to_pre(arr,ind*2+2,new_arr) #recursive call to right
    return new_arr
*/

void level_to_pre(char* message, int ind, char* new_arr) {
    if (ind >= strlen(message)) {
        return;//return new_arr;
    } 
	strncat(new_arr, &message[ind], 1); 
    level_to_pre(message, ind*2 + 1, new_arr); 
    level_to_pre(message, ind*2 + 2, new_arr);
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
    struct qtree q = createqTree();
    enqueueQin(&q, 0, len);
    while(q.front != NULL) {
        Qin tmp = deQueueQin(&q);
        int iroot = tmp->idx;
        int size = tmp->size; 
        if(iroot >= len || size == 0) {
            continue;
        } else {
		    strncat(ans, &message[iroot], 1); 
        }
        int lf = left_tree_size(size); 
        enqueueQin(&q, iroot+1, lf);
        enqueueQin(&q, iroot+1+lf, size-lf-1);
    } 
}

int main() {
    char message[900] = "HelW olldor";//"Jf_%puupov|";
    char test[900], test2[900];
    //int a[900], idx;
    //int len = strlen(message);
    //int am  = left_tree_size(6);
    //printf("len= %d\nleft= %d\n", len, am);
    //return 0;
    level_to_pre(message, 0, test);
    printf("preTraversal: %s\n", test);
    preToLevel(test, test2);
    printf("lvlTraversal: %s\n", test2);
    return 0;
}
