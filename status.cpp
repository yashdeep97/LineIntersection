#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<bits/stdc++.h>
#include <GLFW/glfw3.h>

using namespace std;

int globalinsert = 0;
struct line
{
  GLfloat sx,sy,ex,ey;
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

GLfloat findx (line l, GLfloat y)
{
  return ((y-l.ey)*((l.ex-l.sx)/(l.ey-l.sy)))+l.ex;
}

int getBalance(struct status *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

struct status* insert(struct status* node, line newl, GLfloat ycor)
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
        *justinserted = 0;
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
        *justinserted = 0;
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

  struct status * minValueNode(struct status* node)
  {
      struct status* current = node;


      while (current->left != NULL)
          current = current->left;

      return current;
  }

  struct status* deleteNode(struct status* root, line newl, GLfloat ycor)
  {

      if (root == NULL)
          return root;

      if ( findx(newl,ycor) < findx(root->l,ycor))
          root->left = deleteNode(root->left, newl,ycor);


      else if( findx(newl,ycor) > findx(root->l,ycor))
          root->right = deleteNode(root->right, newl,ycor);

      else
      {
          // node with only one child or no child
          if( (root->left == NULL) || (root->right == NULL) )
          {
              struct status *temp = root->left ? root->left :
                                               root->right;

              if (temp == NULL)
              {
                  temp = root;
                  root = NULL;
              }
              else
               *root = *temp;
              free(temp);
          }
          else
          {

              struct status* temp = minValueNode(root->right);

              // Copy the inorder successor's data to this node
              root->l = temp->l;
              // Delete the inorder successor
              root->right = deleteNode(root->right, temp->l, ycor);
          }
      }

      if (root == NULL)
        return root;


      root->height = 1 + max(height(root->left),
                             height(root->right));


      int balance = getBalance(root);


      if (balance > 1 && getBalance(root->left) >= 0)
          return rightRotate(root);

      if (balance > 1 && getBalance(root->left) < 0)
      {
          root->left =  leftRotate(root->left);
          return rightRotate(root);
      }

      if (balance < -1 && getBalance(root->right) <= 0)
          return leftRotate(root);

      if (balance < -1 && getBalance(root->right) > 0)
      {
          root->right = rightRotate(root->right);
          return leftRotate(root);
      }

      return root;
  }

  void preOrder(struct status *root)
  {
  	if(root != NULL)
  	{
  		printf("%f %f %f %f %d\n", root->l.sx, root->l.sy,root->l.ex,root->l.ey,root->height);
  		preOrder(root->left);
  		preOrder(root->right);
  	}
  }

  // Get the left neighbor of a particular line segment from the status tree for STEP 12
  void getLeftNeighbor(struct status* node, line l, GLfloat ycor, struct line* lastRight){
    if(node->height == 1){
      if(lastRight->sx == -1){
        if(findx(node->l,ycor-0.1) < findx(l,ycor-0.1)){
          *lastRight = node->l;
        }
      }
      return;
    }
    if ((findx(l,ycor-0.1) - 0.1) < findx(node->l,ycor-0.1))
    {
      getLeftNeighbor(node->left, l, ycor, lastRight);
    }
    else if ((findx(l,ycor-0.1) - 0.1) > findx(node->l, ycor-0.1))
    {
      *lastRight = node->l;
      getLeftNeighbor(node->right, l, ycor, lastRight);
    }
  }

  // Get the left neighbor of a particular line segment from the status tree for STEP 15
  void getRightNeighbor(struct status* node, line l, GLfloat ycor, struct line* lastLeft){
    if(node->height == 1){
      if (lastLeft->sx == -1) {
        if(findx(node->l,ycor-0.1) > findx(l,ycor-0.1)){
          *lastLeft = node->l;
        }
      }
      return;
    }
    if ((findx(l,ycor-0.1) + 0.1) < findx(node->l,ycor-0.1))
    {
      *lastLeft = node->l;
      getRightNeighbor(node->left, l, ycor, lastLeft);
    }
    else if ((findx(l,ycor-0.1) + 0.1) > findx(node->l, ycor-0.1))
    {
      getRightNeighbor(node->right, l, ycor, lastLeft);
    }
  }

  // Get left and right neighboring segments of a point, STEP 9
  // lastLeft is the right neighbor and lastRight is the left neighbor for the point 
  void getNeighbors(struct status* node, GLfloat xcor, GLfloat ycor, struct line* lastRight, struct line* lastLeft){
    if(node->height == 1){
      if(lastRight->sx == -1){
        if(findx(node->l,ycor-0.1) < xcor){
          *lastRight = node->l;
        }
      }
      if (lastLeft->sx == -1) {
        if(findx(node->l,ycor-0.1) > xcor){
          *lastLeft = node->l;
        }
      }
      
      return;
    }
    if (xcor < findx(node->l,ycor-0.1))
    {
      printf("go left");
      *lastLeft = node->l;
      getNeighbors(node->left, xcor, ycor, lastRight, lastLeft);
    }
    else if (xcor > findx(node->l, ycor-0.1))
    {
      printf("go right");
      *lastRight = node->l;
      getNeighbors(node->right, xcor, ycor, lastRight, lastLeft);
    }
  }

int main()
{
  struct status *root = NULL;
  printf("Enter 1 to push 2 to pop 0 to exit\n");
  int control;
  line newl;
  scanf("%d",&control);
  GLfloat xs,ys,xe,ye,ycor;
  while(control!=0)
  {
    if(control==1)
    {
        globalinsert = 0;
        printf("Enter new line segment details and y\n");
        scanf("%f%f%f%f%f",&xs,&ys,&xe,&ye,&ycor);
        newl.sx = xs;
        newl.sy = ys;
        newl.ex = xe;
        newl.ey = ye;
        root = insert (root,newl,ycor-1);
        printf("Inserted\n");

    }
    if(control == 2)
    {
      printf("Enter event details to delete and y\n");
      scanf("%f%f%f%f%f",&xs,&ys,&xe,&ye,&ycor);
      newl.sx = xs;
      newl.sy = ys;
      newl.ex = xe;
      newl.ey = ye;
      deleteNode(root, newl,ycor+1);
      deleteNode(root, newl,ycor+1);
      printf("Deleted from status \n");
    }
    if(control == 3){
      printf("enter point: \n");
      GLfloat px, py;
      scanf("%f %f", &px, &py);
      struct line leftl;
      struct line rightl;
      leftl.sx = -1;
      rightl.sx = -1;
      
      getNeighbors(root, px, py-0.1, &leftl, &rightl);
      if(leftl.sx == -1){
        printf("no left line\n");
      }
      else{
        printf("\nleft line: %f %f %f %f", leftl.sx, leftl.sy, leftl.ex, leftl.ey );
      }
      if (rightl.sx == -1) {
        printf("no right line\n");
      } else {
        printf("\nright line: %f %f %f %f", rightl.sx, rightl.sy, rightl.ex, rightl.ey );
      }      
    }
    preOrder(root);
    printf("Enter 1 to push 2 to pop 0 to exit\n");
    scanf("%d",&control);

  }
    return 1;
}
