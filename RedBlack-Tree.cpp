#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	int color; // 1-red, 0-black
	node *parent;
	node *right;
	node *left;
}*root = NULL;

node *createNode(int data) {
	node *temp = (node*)malloc(sizeof(node));
	temp->data = data;
	temp->color = 1;
	temp->right = NULL; 
	temp->left = NULL; 
	temp->parent = NULL; 

	return temp;
}


node *rightRotate(node *temp) {
	node *x = temp->left;
	node *T2 = x->right;
	
	temp->left = T2;
	x->right = temp;
	
	if(T2 != NULL) T2->parent = temp;
	
	x->parent = temp->parent;
	temp->parent = x;
	
	return x;
}

node *leftRotate(node *temp) {
	node *x = temp->right;
	node *T2 = x->left;
	
	temp->right = T2;
	x->left = temp;
	
	if(T2 != NULL) T2->parent = temp;
	
	x->parent = temp->parent;
	temp->parent = x;
	
	return x;
}

node *insertFixUp(node *root) {
	if(root->parent == NULL || root->parent->color == 0) return root;
	
	node *parent = root->parent;
	node *grandParent = parent->parent;
	node * uncle = (parent == grandParent->left) ? grandParent->right : grandParent->left;
	
	if(uncle != NULL && uncle->color == 1){
		parent->color = 0;
		uncle->color = 0;
		grandParent->color = 1;
		return insertFixUp(grandParent);
	}
	
	if(root == parent->right && parent == grandParent->left){
		root = parent;
		root->left = leftRotate(root->left);
		parent = root->parent;
		grandParent = parent->parent;
		
	}else if(root == parent->left && parent == grandParent->right){ 
		root = parent;
		root->right = rightRotate(root->right);
		
		parent = root->parent;
		grandParent = parent->parent;
	}
	
	if(root == parent->left) return rightRotate(grandParent);
	else return leftRotate(grandParent);
	
}

node *insert(node *root, int data) {
	if (root == NULL) return createNode(data);

	if (data < root->data) {
		root->left = insert(root->left, data);
	}else if (data > root->data) {
		root->right = insert(root->right, data);
	}
	
	return insertFixUp(root);
}

void inorder(node *root) {
	if (root == NULL) return;
	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

int main() {
	int total_data = 10;
    int a[10] = { 41,22,5,51,48,29,18,21,45,3 };

    for (int i = 0; i < total_data; i++) {
        root = insert(root, a[i]);
    }
	   
	printf("Inorder Traversal of Created Tree\n");
	inorder(root);

	return 0;
}
