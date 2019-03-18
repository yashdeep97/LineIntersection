#ifndef ALGO_H
#define ALGO_H

#include <algorithm>
#include <queue>
#include "status.h"
#include "event.h"

using namespace std;

// struct to represent a point
struct point
{
    GLfloat x;
    GLfloat y;
};

class FindIntersections
{
    private:
        // initialise eventQueue and status
        event eventQueue;
        struct q *eventQueueRoot = NULL;
        // statustree status = statustree();
    public:
        // constructor to initialise event queue and status
        FindIntersections( vector<lineSegment> segmentVector ){
            for(size_t i = 0; i < segmentVector.size(); i++)
            {   
                GLfloat startx, starty, endx, endy;
                if(segmentVector[i].startY >= segmentVector[i].endY){
                    startx = segmentVector[i].startX;
                    starty = segmentVector[i].startY;
                    endx = segmentVector[i].endX;
                    endy = segmentVector[i].endY;
                } else {
                    startx = segmentVector[i].endX;
                    starty = segmentVector[i].endY;
                    endx = segmentVector[i].startX;
                    endy = segmentVector[i].startY;
                }
                
                // printf("%f %f %f %f\n", startx, starty, endx, endy);             
                
                // insert end points into the event queue.
                eventQueueRoot = eventQueue.insert( eventQueueRoot, startx, starty, startx, starty, endx, endy, 1);
                eventQueueRoot = eventQueue.insert( eventQueueRoot, endx, endy, startx, starty, endx, endy, 2);
            }
        }

        // Given three colinear points p, q, r, the function checks if 
        // point q lies on line segment 'pr' 
        bool onSegment(point p, point q, point r) 
        { 
            if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
                q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
            return true; 
        
            return false; 
        } 
        
        // To find orientation of ordered triplet (p, q, r). 
        // The function returns following values 
        // 0 --> p, q and r are colinear 
        // 1 --> Clockwise 
        // 2 --> Counterclockwise 
        int orientation(point p, point q, point r) 
        { 
            GLfloat val = (q.y - p.y) * (r.x - q.x) - 
                    (q.x - p.x) * (r.y - q.y); 
        
            if (val == 0) return 0;  // colinear 
        
            return (val > 0)? 1: 2; // clock or counterclock wise 
        } 
        
        // The main function that returns true if line segment 'p1q1' 
        // and 'p2q2' intersect. 
        bool doIntersect(point p1, point q1, point p2, point q2) 
        { 
            // Find the four orientations needed for general and 
            // special cases 
            int o1 = orientation(p1, q1, p2); 
            int o2 = orientation(p1, q1, q2); 
            int o3 = orientation(p2, q2, p1); 
            int o4 = orientation(p2, q2, q1); 
        
            // General case 
            if (o1 != o2 && o3 != o4) 
                return true; 
        
            // Special Cases 
            // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
            if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
        
            // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
            if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
        
            // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
            if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
        
            // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
            if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
        
            return false; // Doesn't fall in any of the above cases 
        } 

        // point intsertionOf(lineSegment l1, lineSegment l2){
            
        //     point intersection;
        //     if (doIntersect(l1, l2) == 0) 
        //     { 
        //         // The line segments do not intersect.
        //         intersection.x = -1;
        //         intersection.y = -1;
        //     } 
        //     else
        //     {   
        //         // Line l1 represented as a1x + b1y = c1 
        //         double a1 = l1.endY - l1.startY; 
        //         double b1 = l1.startX - l1.endX; 
        //         double c1 = a1*(l1.startX) + b1*(l1.startY); 
            
        //         // Line l2 represented as a2x + b2y = c2 
        //         double a2 = l2.endY - l2.startY; 
        //         double b2 = l2.startX - l2.endX; 
        //         double c2 = a1*(l2.startX) + b1*(l2.startY); 
            
        //         double determinant = a1*b2 - a2*b1; 
        //         intersection.x = (b2*c1 - b1*c2)/determinant; 
        //         intersection.y = (a1*c2 - a2*c1)/determinant;
        //     }
        //     return intersection;
        // }

        // void findNewEvent(lineSegment sl, lineSegment sr, p){
        //     //find intersection point of sl and sr
        //     point newEventPoint = intsertionOf(sl, sr);

        //     if(newEventPoint.y < p.y){
        //         eventQueue.insert(newEventPoint);
        //     } else if(newEventPoint.y == p.y && newEventPoint.x > p.x){
        //         eventQueue.insert(newEventPoint);
        //     }
            
        // }

        vector<lineSegment> unionOf(vector<lineSegment> a, vector<lineSegment> b){
            vector<lineSegment> unionVec;

            return unionVec;
        }

        // handle each event point popped from the event queue
        void handleEventPoint(struct q* eventPoint){
            printf("hello");
            
            // // Union of Lp, Up and Cp
            // vector<lineSegment> all = unionOf(eventPoint.L, unionOf(eventPoint.U, eventPoint.C));

            // if (all.size() > 1) {
            //     // p is an intersection

            // }
            // // delete elements of Lp union Cp from status

            // //insert segments in Up union Cp into status according to their position just below the sweep line

            // // check if Up union Cp is empty
            // if(empty(unionOf(Up, Cp))){
            //     lineSegment sl = status.getLeftNeighbor(p);
            //     lineSegment sr = status.getRightNeighbor(p);
            //     findNewEvent(sl, sr, p);
            // } else {
                
            // }
            

        }

        // Run the algorithm to find the line intersections
        void runAlgorithm(){
            // while(eventQueueRoot != NULL){
            //     struct q* pop = eventQueue.maxValueNode(eventQueueRoot);
            //     eventQueue.deleteNode(eventQueueRoot, pop->xc, pop-> yc);
            //     // handleEventPoint(pop);
            // }
            
            
            // printf("%f %f\n", eventQueueRoot->xc, eventQueueRoot->yc);
            printf("Execution complete\n");
        }

};


#endif