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
        // use priority queue as the event queue for time being
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

        vector<lineSegment> unionOf(vector<lineSegment> a, vector<lineSegment> b){
            
        }

        void findNewEvent(lineSegment sl, lineSegment sr, p){
            //find intersection point of sl and sr
            point newEventPoint = intsertionOf(sl, sr);

            if(!eventQueue.find(newEventPoint)){
                if(newEventPoint.y < p.y){
                    eventQueue.insert(newEventPoint);
                } else if(newEventPoint.y == p.y && newEventPoint.x > p.x){
                    eventQueue.insert(newEventPoint);
                }
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