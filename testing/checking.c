#include <stdio.h>
#include <string.h>

char* convert(char* dt)  {
    char c='h';
    strncat(dt, &c, 1);
    strncat(dt, &c, 1);
    strncat(dt, &c, 1);
    //printf("%s\n", dt);
    //strcpy(dt, "dt variable");
    return dt;
}

void mani(const char* message) {
    for(int i=0; *(message+i) != '\0'; i++) {
        //*(message+i) = 'H';
        printf("%c", *(message + i));
    }
    printf("\n");
}

void change(char* message) {
    char c = 'H';
    strncat(message, &c, 1);
    strncat(message, &c, 1);
    strncat(message, &c, 1);

}
/*

void mirrorTree(Node node) {   //  ---- O(n)
    if(node == NULL)
        return;
    else
    {
        mirrorTree(node->left);
        mirrorTree(node->right);
        
        Node temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}

void encryption(char* data, char* message, int type) {
	if(sizeof(data) == 0){
		printf("ERROR : No data found\n");
		strcpy(message, "");
        return;
	}
    
    stage1Encrypt(data, type);
	BinaryTree tree = createBT();
	createLevelTree(tree, data);
	swapChild(tree->root, 0);
    strcpy(message, "");
    preOrderTraversal(tree->root, message);
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
	swapChild(tree->root, 0);
    //mirrorTree(tree);
    levelTraversal(tree, lvlOrder);
    stage2Decrypt(lvlOrder, type);
}

*/

int main() {
    /*
    char data[128], data1[128];
    int len;
    printf("Enter a string: ");
    fgets(data, sizeof(data), stdin);
    len = strlen(data);
    printf("%d\n", len);
    data[strcspn(data, "\n")] = '\0';
    len = strlen(data);
    printf("%d\n", len);
    //strcpy(data, convert());
    mani(data);
    printf("last- %s\n", data);
    change(data1);
    printf("last- %s\n", data1);
*/
        /*
    *(message + i-1) = (((int)(*(message + i-1)) + (i-1)) - 32)%95 + 32;
    *(message + i-1) = (((int)(*(message + i-1)) - (i-1) + 3 * 95) - 32)%95 + 32;
        */
    
    //printf("Enter a string: ");
    //fgets(data, sizeof(data), stdin);
    //data[strcspn(data, "\n")] = '\0';
    //strcpy(message, data);
    //createLevelTree(BT, data);
    //levelTraversal(BT, message);
    //printf("levelTraversal: %s\n", message);
    //swapAlter(BT);
    //mirrorTree(BT);
    //levelTraversal(BT, message);
    /*
    encrypt(message, 1);
    printf("Encrypted Message type 1: %s\n", message);
    decrypt(message,1);   
    printf("decrypted Message type 1: %s\n", message);
    encrypt(message, 2);
    printf("Encrypted Message type 2: %s\n", message);
    decrypt(message,2);   
    printf("decrypted Message type 2: %s\n", message);
    encrypt(message, 3);
    printf("Encrypted Message type 3: %s\n", message);
    decrypt(message,3);   
    printf("decrypted Message type 3: %s\n", message);


	BinaryTree tree = createBT();
	createLevelTree(tree, message);
    swapChild(tree->root, 0);
    //swapAlter(tree);
    //mirrorTree(tree);
    //mirrorTree(tree->root);
    levelTraversal(tree, message);


    BinaryTree tree = createBT();
	createLevelTree(tree, message);
    swapChild(tree->root, 0);
    //swapAlter(tree);
    //mirrorTree(tree);
    //mirrorTree(tree->root);
    //print(*tree);
    levelTraversal(tree, message);

     */
    long int ch;
    char t = 't';
    ch = (long int)t; 
    long int shift;
    int i = 256;
    shift = ((ch - (i-1) + 20 * 95) - 32)%95 + 32;
    //printf("%ld", shift);
    char m = (char)(shift);
    printf("t=%c\nch = %ld\nm = %c\nshift = %ld\n", t,ch,  m, shift);
    return 0;
}
