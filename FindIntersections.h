#ifndef ALGO_H
#define ALGO_H

#include <iostream>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// struct to represent a point
struct point
{
    GLfloat x;
    GLfloat y;
};

//struct to represent a line segment
struct lineSegment
{
    GLfloat startX;
    GLfloat startY;
    GLfloat endX = -1;
    GLfloat endY = -1;
};



class FindIntersections
{
    private:
        // initialise eventQueue and status
        EventQueue eventQueue = new EventQueue();
        Status status = new Status();
    public:
        // constructor to initialise event queue and status
        FindIntersections( vector<lineSegment> segmentVector ){
            for(size_t i = 0; i < segmentVector.size(); i++)
            {
                struct point start, end;
                start.x = segmentVector[i].startX;
                start.y = segmentVector[i].startY;
                end.x = segmentVector[i].endX;
                end.y = segmentVector[i].endY;

                // insert end points into the event queue.
                eventQueue.insert(start, end);
                eventQueue.insert(end);
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

        point intsertionOf(lineSegment l1, lineSegment l2){
            
            point intersection;
            if (doIntersect(l1, l2) == 0) 
            { 
                // The line segments do not intersect.
                intersection.x = -1;
                intersection.y = -1;
            } 
            else
            {   
                // Line l1 represented as a1x + b1y = c1 
                double a1 = l1.endY - l1.startY; 
                double b1 = l1.startX - l1.endX; 
                double c1 = a1*(l1.startX) + b1*(l1.startY); 
            
                // Line l2 represented as a2x + b2y = c2 
                double a2 = l2.endY - l2.startY; 
                double b2 = l2.startX - l2.endX; 
                double c2 = a1*(l2.startX) + b1*(l2.startY); 
            
                double determinant = a1*b2 - a2*b1; 
                intersection.x = (b2*c1 - b1*c2)/determinant; 
                intersection.y = (a1*c2 - a2*c1)/determinant;
            }
            return intersection;
        }

        void findNewEvent(lineSegment sl, lineSegment sr, p){
            //find intersection point of sl and sr
            point newEventPoint = intsertionOf(sl, sr);

            if(newEventPoint.y < p.y){
                eventQueue.insert(newEventPoint);
            } else if(newEventPoint.y == p.y && newEventPoint.x > p.x){
                eventQueue.insert(newEventPoint);
            }
            
        }

        // handle each event point popped from the event queue
        void handleEventPoint(point p){
            // get segments whose upper endpoints is p
            vector<lineSegment> Up = 
            // get segments whose lwer end point is p
            vector<lineSegment> Lp = 
            //get line segments that contain p
            vector<lineSegment> Cp = 

            // Union of Lp, Up and Cp
            vector<lineSegment> all = unionOf(Lp, unionOf(Up, Cp));

            if (all.size() > 1) {
                // p is an intersection

            }
            // delete elements of Lp union Cp from status

            //insert segments in Up union Cp into status according to their position just below the sweep line

            // check if Up union Cp is empty
            if(empty(unionOf(Up, Cp))){
                lineSegment sl = status.getLeftNeighbor(p);
                lineSegment sr = status.getRightNeighbor(p);
                findNewEvent(sl, sr, p);
            } else {
                
            }
            

        }

        // Run the algorithm to find the line intersections
        void runAlgorithm(){
            while(!eventQueue.empty()){
                handleEventPoint(eventQueue.top());
                eventQueue.pop();
            }
        }

};


#endif