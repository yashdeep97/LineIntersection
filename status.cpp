#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<bits/stdc++.h>
using namespace std;
int globalinsert = 0;
struct line
{
  int sx,sy,ex,ey;
};
struct status
{
  line l;
  struct status *left;
	struct status *right;
  int height;
};
int height(struct status *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
int max(int a, int b)
{
	return (a > b)? a : b;
}
struct status* newstatus(line newl)
{
	struct status* node = (struct status*)
						malloc(sizeof(struct status));
	node->l = newl;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}
struct status *rightRotate(struct status *y)
{
	struct status *x = y->left;
	struct status *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;


	return x;
}

struct status *leftRotate(struct status *x)
{
	struct status *y = x->right;
	struct status *T2 = y->left;

	y->left = x;
	x->right = T2;


	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;
	return y;
}
int findx (line l, int y)
{
  return y*((l.ex-l.sx)/(l.ey-l.sy));
}
int getBalance(struct status *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
struct status* insert(struct status* node, line newl, int ycor)
{
  int *justinserted = &globalinsert;

	if (node == NULL)
  {
    *justinserted = 1;
    return(newstatus(newl));
  }


    if (findx(newl,ycor) < findx(node->l,ycor))
    {
      node->left  = insert(node->left, newl,ycor);
      if(*justinserted == 1)
      {
        node->right = newstatus(node->l);
        node->l = newl;
        justinserted = 0;
      }
    }
    else if (findx(newl,ycor) > findx(node->l,ycor))
    {
      // printf("Going right\n");
      node->right  = insert(node->right, newl,ycor);
      if(*justinserted == 1)
      {
        printf("copying to left leaf\n");
        node->left = newstatus(node->l);
        justinserted = 0;
      }
    }
    else
    {
      return node;
    }
    node->height = 1 + max(height(node->left),
  						height(node->right));

  	int balance = getBalance(node);
  	if (balance > 1 && findx(newl,ycor) < findx(node->left->l,ycor))
  		return rightRotate(node);

  	if (balance < -1 && findx(newl,ycor) > findx(node->right->l,ycor))
  		return leftRotate(node);

  	if (balance > 1 && findx(newl,ycor) > findx(node->left->l,ycor))
  	{
  		node->left = leftRotate(node->left);
  		return rightRotate(node);
  	}
  	if (balance < -1 && findx(newl,ycor) < findx(node->right->l,ycor))
  	{
  		node->right = rightRotate(node->right);
  		return leftRotate(node);
  	}

  	return node;
  }
  void preOrder(struct status *root)
  {
  	if(root != NULL)
  	{
  		printf("%d %d %d %d %d\n",root->l.sx, root->l.sy,root->l.ex,root->l.ey,root->height);
  		preOrder(root->left);
  		preOrder(root->right);
  	}
  }

int main()
{
  struct status *root = NULL;
  printf("Enter 1 to push 2 to pop 0 to exit\n");
  int control;
  line newl;
  scanf("%d",&control);
  int xs,ys,xe,ye,ycor;
  while(control!=0)
  {
    if(control==1)
    {
        globalinsert = 0;
        printf("Enter new event details and y\n");
        scanf("%d%d%d%d%d",&xs,&ys,&xe,&ye,&ycor);
        newl.sx = xs;
        newl.sy = ys;
        newl.ex = xe;
        newl.ey = ye;
        root = insert (root,newl,ycor);
        printf("Inserted\n");

    }
    if(control == 2)
    {
      // printf("Enter event details to delete and y\n");
      // scanf("%d%d%d%d%d",&xs,&ys,&xe,&ye,&ycor);
      // newl.sx = xs;
      // newl.sy = ys;
      // newl.ex = xe;
      // newl.ey = ye;
      // deleteNode(root, newl,ycor);
      // printf("Deleted from status \n");
    }
    preOrder(root);
    printf("Enter 1 to push 2 to pop 0 to exit\n");
    scanf("%d",&control);

  }
    return 1;
}
