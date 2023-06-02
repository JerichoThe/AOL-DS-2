#include<stdio.h>
#include<stdlib.h>

struct data{
	int num;
	int height;
	
	data *left;
	data *right;
}*root = NULL;

bool found = false;

data *createData(int num){
	data *newD = (data*)malloc(sizeof(data));
	newD->num = num;
	
	newD->height = 1;
	
	newD->left = newD->right = NULL;
	return newD;
}

int max(int a, int b){
	return a>b ? a:b;
}

int getHeight(data *now){
	if(now) return now->height;
	return 0;
}

int getBalance(data *now){
	if(now) return getHeight(now->left) - getHeight(now->right);
	return 0;
}

data *rightRotate(data *now){
	data *x = now->left;
	data *T2 = x->right;
	
	now->left = T2;
	x->right = now;
	
	now->height = max(getHeight(now->left),getHeight(now->right))+1;
	x->height = max(getHeight(x->left),getHeight(x->right))+1;
	
	return x;
}

data *leftRotate(data *now){
	data *x = now->right;
	data *T2 = x->left;
	
	now->right = T2;
	x->left = now;
	
	now->height = max(getHeight(now->left),getHeight(now->right))+1;
	x->height = max(getHeight(x->left),getHeight(x->right))+1;
	
	return x;
}

data *validation(data *now){
	if(now == NULL) return now;
	
	now->height = max(getHeight(now->left),getHeight(now->right))+1;
	int balance = getBalance(now);
	
	if(balance > 1 && getBalance(now->left)>=0) return rightRotate(now);
	if(balance > 1 && getBalance(now->left)<0){
		now->left = leftRotate(now->left);
		return rightRotate(now);
	}
	if(balance < -1 && getBalance(now->right)<=0) return leftRotate(now);
	if(balance < -1 && getBalance(now->right)>0){
		now->right = rightRotate(now->right);
		return leftRotate(now);
	}
	
	return now;
}


data *insert(data *now, int num){
	if(!now) return createData(num);
	
	if(num < now->num){
		now->left = insert(now->left,num);
	}else if(num > now->num){
		now->right = insert(now->right,num);
	}

	return validation(now);
}

data *deleteNode(data *now, int num){
	if(now == NULL) return now;
	
	if(num > now->num){
		now-> right = deleteNode(now->right,num);
	} 
	else if(num < now->num){
		now->left = deleteNode(now->left,num);
	} 
	else{
		found = true;
		if(!now->left && !now->right){
			free(now);
			now = NULL;
		}else if(!now->left || !now->right){
			data *curr = now->left ? now->left : now->right;
			
			*now = *curr;
			free(curr);
			curr = NULL;
			
		}else{
			data *curr = now->left;
		    while (curr->right) {
		        curr = curr->right;
		    }
			now->num = curr->num;
			now->left = deleteNode(now->left,curr->num);
		}
	}
	
	return validation(now);
}

void deleteValidation(){
	found = false;
	int num;
	
	printf("Delete: ");
	scanf("%d",&num);
	getchar();
	root = deleteNode(root,num);
	
	if(found){
		printf("Data Found\n");
		printf("Value %d was deleted\n", num);
	}else{
		printf("Data Not Found\n");
	}
	
	
}

void preOrder(data *now){
	if(now){
		printf("%d ", now->num);
		preOrder(now->left);
		preOrder(now->right);
	}
}

void inOrder(data *now){
	if(now){
		inOrder(now->left);
		printf("%d ", now->num);
		inOrder(now->right);
	}
	
}

void postOrder(data *now){
	if(now){
		postOrder(now->left);
		postOrder(now->right);
		printf("%d ", now->num);
	}
}

void traverse(){
	if(root == NULL) {
		printf("No data available.\n");
		return;
	}
	
	printf("PreOrder: ");
	preOrder(root);
	printf("\n");
	
	printf("InOrder: ");
	inOrder(root);
	printf("\n");
	
	printf("PostOrder: ");
	postOrder(root);
	printf("\n");
}

void menu(){
	system("cls");
	printf("1. Insertion\n");
	printf("2. Deletion\n");
	printf("3. Transversal\n");
	printf("4. Exit\n");
	printf("Choose:");
}

int main(){
	int input,num;
	while(true){
		menu();
		scanf("%d",&input);
		getchar();
		switch(input){
			case 1:
				printf("Insert: ");
				scanf("%d",&num);
				getchar();
				root = insert(root,num);
				break;
			case 2:
				deleteValidation();
				getchar();
				break;
			case 3:
				traverse();
				getchar();
				break;
			case 4:
				printf("Thankyou");
				exit(0);
		}
	}
}
