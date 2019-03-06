#ifndef EVENT_H
#define EVENT_H

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<bits/stdc++.h>
#include <GLFW/glfw3.h>
using namespace std;
/// structure that stores a line in the form of start and end points
struct line
{
  GLfloat sx,sy,ex,ey;
};
/// basic structure for the q tree
struct q
{
	GLfloat xc,yc;
	struct q *left;
	struct q *right;
  vector<line> U;
  vector<line> C;
  vector<line> L;
	int height;
};
/// a class that contains functions to delete and insert to the tree as well as find an event point
class event
{
private:

public:
  ///function to find height of a node
  int height(struct q *N)
  {
  	if (N == NULL)
  		return 0;
  	return N->height;
  }
  int max(int a, int b)
  {
  	return (a > b)? a : b;
  }
  /// function to create a new node
  // value for teller
  // 1 - upper endpoint
  // 2- lower endpoint
  // 3 - interior point

  struct q* newq(GLfloat xc, GLfloat yc, GLfloat xs, GLfloat ys, GLfloat xe, GLfloat ye, int teller)
  {
  	struct q* node = (struct q*)
  						malloc(sizeof(struct q));
  	node->xc = xc;
    node->yc = yc;
    line l;
    l.sx = xs;
    l.sy = ys;
    l.ex = xe;
    l.ey = ye;
    if(teller == 1)
    node->U.push_back(l);
    else if(teller ==2)
    node->L.push_back(l);
    else
    node->C.push_back(l);
  	node->left = NULL;
  	node->right = NULL;
  	node->height = 1;
  	return(node);
  }

  /// function to right rightRotate about a node to rebalance
  struct q *rightRotate(struct q *y)
  {
  	struct q *x = y->left;
  	struct q *T2 = x->right;

  	x->right = y;
  	y->left = T2;

  	y->height = max(height(y->left), height(y->right))+1;
  	x->height = max(height(x->left), height(x->right))+1;


  	return x;
  }
  /// function to right leftRotate about a node to rebalance

  struct q *leftRotate(struct q *x)
  {
  	struct q *y = x->right;
  	struct q *T2 = y->left;

  	y->left = x;
  	x->right = T2;


  	x->height = max(height(x->left), height(x->right))+1;
  	y->height = max(height(y->left), height(y->right))+1;
  	return y;
  }
  /// function used as a comparator for insertion and deletion
  int mygreater(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
  {
    if(y1<y2)
    return 0;
    else if(y1>y2)
    return 1;
    else
    {
      if(x1>x2)
      return 0;
      else if(x1<x2)
      return 1;
    }
  }
  /// function used as a comparator for insertion and deletion
  int mylesser(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
  {
    if(y1<y2)
    return 1;
    else if(y1>y2)
    return 0;
    else
    {
      if(x1>x2)
      return 1;
      else if(x1<x2)
      return 0;
    }
  }
  /// function to get balance factor of a node
  int getBalance(struct q *N)
  {
  	if (N == NULL)
  		return 0;
  	return height(N->left) - height(N->right);
  }
  /// function to insert a new event point
  struct q* insert(struct q* node, GLfloat xc, GLfloat yc, GLfloat xs, GLfloat ys, GLfloat xe, GLfloat ye,int teller)
  {

  	if (node == NULL)
  		return(newq(xc,yc,xs,ys,xe,ye,teller));

      if (yc < node->yc)
      {

        node->left  = insert(node->left, xc,yc,xs,ys,xe,ye,teller);
      }
      else if (yc > node->yc)
      {
        // printf("Going right\n");
        node->right  = insert(node->right, xc,yc,xs,ys,xe,ye,teller);
      }
      else if(xc > node->xc)
      {
        // printf("Going left\n");
        node->left  = insert(node->left, xc,yc,xs,ys,xe,ye,teller);
      }
      else if(xc < node->xc)
      {
        // printf("Going right\n");
        node->right  = insert(node->right, xc,yc,xs,ys,xe,ye,teller);
      }
      else
      {
        int counter = 1;
        if(teller==1)
        {
          for(int q=0;q<node->U.size();q++)
          {
            line l = node->U[q];
            if(l.sx == xs && l.sy == ys && l.ex == xe && l.ey == ye)
            counter == 0;
          }
          if(counter ==1)
          {
            line l;
            l.sx = xs;
            l.sy = ys;
            l.ex = xe;
            l.ey = ye;
            node->U.push_back(l);
          }
        }
        else if (teller == 2)
        {
          for(int q=0;q<node->L.size();q++)
          {
            line l = node->L[q];
            if(l.sx == xs && l.sy == ys && l.ex == xe && l.ey == ye)
            counter == 0;
          }
          if(counter ==1)
          {
            line l;
            l.sx = xs;
            l.sy = ys;
            l.ex = xe;
            l.ey = ye;
            node->L.push_back(l);
          }
        }
        else if(teller == 3)
        {
          for(int q=0;q<node->C.size();q++)
          {
            line l = node->C[q];
            if(l.sx == xs && l.sy == ys && l.ex == xe && l.ey == ye)
            counter == 0;
          }
          if(counter ==1)
          {
            line l;
            l.sx = xs;
            l.sy = ys;
            l.ex = xe;
            l.ey = ye;
            node->C.push_back(l);
          }
        }
        if(counter == 0)
        return node;
      }



  	node->height = 1 + max(height(node->left),
  						height(node->right));


  	int balance = getBalance(node);

  	if (balance > 1 && mylesser(xc,yc,node->left->xc,node->left->yc))
  		return rightRotate(node);

  	if (balance < -1 && mygreater(xc,yc,node->right->xc,node->right->yc))
  		return leftRotate(node);

  	if (balance > 1 && mygreater(xc,yc,node->left->xc,node->left->yc))
  	{
  		node->left = leftRotate(node->left);
  		return rightRotate(node);
  	}
  	if (balance < -1 && mylesser(xc,yc,node->right->xc,node->right->yc))
  	{
  		node->right = rightRotate(node->right);
  		return leftRotate(node);
  	}

  	return node;
  }
  /// function to find min vale node for bst deletion
  struct q * minValueNode(struct q* node)
  {
      struct q* current = node;


      while (current->left != NULL)
          current = current->left;

      return current;
  }
  /// function to find node to pop
  struct q * maxValueNode(struct q* node)
  {
      struct q* current = node;

      /* loop down to find the rightmost leaf */
      while (current->right != NULL)
          current = current->right;

      return current;
  }
  /// function to delete the enent point that is to be popped
  struct q* deleteNode(struct q* root, GLfloat xc, GLfloat yc)
  {

      if (root == NULL)
          return root;

      if ( yc < root->yc )
          root->left = deleteNode(root->left, xc,yc);


      else if( yc > root->yc )
          root->right = deleteNode(root->right, xc,yc);

      else if (xc > root->xc)
          root->left = deleteNode(root->left,  xc,yc);
      else if (xc < root->xc)
          root->right = deleteNode(root->right, xc,yc);
      else
      {
          // node with only one child or no child
          if( (root->left == NULL) || (root->right == NULL) )
          {
              struct q *temp = root->left ? root->left :
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

              struct q* temp = minValueNode(root->right);

              // Copy the inorder successor's data to this node
              root->xc = temp->xc;
              root->yc = temp->yc;
              root->U = temp->U;
              root->C = temp->C;
              root->L = temp->L;
              // Delete the inorder successor
              root->right = deleteNode(root->right, temp->xc , temp->yc);
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
  /// function to print preorder of current tree
  void preOrder(struct q *root)
  {
  	if(root != NULL)
  	{
  		printf("%f %f %d\n",root->xc, root->yc,root->height);
  		preOrder(root->left);
  		preOrder(root->right);
  	}
  }
};

#endif
