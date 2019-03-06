#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<bits/stdc++.h>
#include <GLFW/glfw3.h>
#include "event.h"
using namespace std;

int main()
{
struct q *root = NULL;
event newevent;

printf("Enter 1 to push 2 to pop 0 to exit\n");
int control;
scanf("%d",&control);
GLfloat x,y,xs,ys,xe,ye;
int teller;
while(control!=0)
{
  if(control==1)
  {
      printf("Enter new event details\n");
      scanf("%f%f%f%f%f%f%d",&x,&y,&xs,&ys,&xe,&ye,&teller);
      root = newevent.insert (root,x,y,xs,ys,xe,ye,teller);
      printf("Inserted %f,%f\n",x,y);

  }
  if(control == 2)
  {
    struct q* pop = newevent.maxValueNode(root);
    //pop is what is taken out
    printf("popping event point %f,%f \n",pop->xc,pop->yc);
    newevent.deleteNode(root, pop->xc, pop-> yc);
  }
  newevent.preOrder(root);
  printf("Enter co-ordinates 1 to push 2 to pop 0 to exit\n");
  scanf("%d",&control);

}


return 0;
}
