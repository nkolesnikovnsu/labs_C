#include <stdio.h>
#include <mm_malloc.h>
 
typedef struct _AVLtree{
    int key;
    unsigned char height;
    struct _AVLtree *left;
    struct _AVLtree *right;
}AVLtree;
 
unsigned char findHeight(AVLtree * t) {
    return t ? t -> height : 0;
}
 
int balFactor(AVLtree * t){
    return findHeight(t->right) - findHeight(t->left);
}
 
void fixHeight(AVLtree * t){
    int hl = findHeight(t -> left);
    int hr = findHeight(t -> right);
    t -> height = (unsigned char)((hr > hl ? hr : hl) + 1);
}
 
AVLtree * rotateRight(AVLtree *p){
    AVLtree * q = p -> left;
    p -> left = q -> right;
    q -> right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}
 
AVLtree * rotateLeft(AVLtree *q){
    AVLtree *p = q -> right;
    q -> right = p -> left;
    p -> left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}
 
AVLtree * balance(AVLtree *p){
    fixHeight(p);
    if (balFactor(p) == 2){
        if(balFactor(p -> right) < 0)
            p -> right = rotateRight(p -> right);
        p = rotateLeft(p);
    }
    if (balFactor(p) == -2){
        if(balFactor(p -> left) > 0)
            p -> left = rotateLeft(p -> left);
        p = rotateRight(p);
    }
    return p;
}
 
AVLtree* create(int value) {
    AVLtree* new = (AVLtree*)calloc(1, sizeof(AVLtree));
    new -> key = value;
    new -> height = 1;
    return new;
}
 
AVLtree * insert(AVLtree* root, int key) {
    if(root == NULL) return create(key);
    if(key <= root -> key){
        root -> left = insert(root -> left, key);
    } else{
        root -> right = insert(root -> right, key);
    }
    return balance(root);
}
 
void deleteTree(AVLtree* root) {
    if (root -> left) {
        deleteTree(root -> left);
    }
    if (root -> right) {
        deleteTree(root -> right);
    }
    free(root);
}
 
int main() {
    AVLtree* root = NULL;
    int element, n;
    if(scanf("%d", &n) == 0){
        printf("Bad input");
        free(root);
        return 0;
    }
    else for(int i = 0; i < n; i++){
            if(scanf("%d", &element) == 0){
                printf("Bad input");
                return 0;
            }
            root = insert(root, element);
        }
    printf("%d", findHeight(root));
    if(root){
        deleteTree(root);
    }
    return 0;
}
