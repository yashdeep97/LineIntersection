#ifndef ALGO_H
#define ALGO_H

#include <iostream>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <queue>

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

class ComparisonClass{
    bool operator()(point a, point b) {
        if(a.y == b.y){
           if(a.x > b.x){
               return true;
           } else {
               return false;
           }
        }
        if (a.y < b.y) {
            return true;
        } else {
            return false;
        }
        
    }
};

class algorithm
{
private:
    // use priority queue as the event queue for time being
    priority_queue<point, vector<point>, ComparisonClass> eventQueue;
public:
    // constructor to initialise event queue and status
    algorithm( vector<lineSegment> segmentVector ){
        for(size_t i = 0; i < segmentVector.size(); i++)
        {
            struct point start, end;
            start.x = segmentVector[i].startX;
            start.y = segmentVector[i].startY;
            end.x = segmentVector[i].endX;
            end.y = segmentVector[i].endY;
            eventQueue.push(start);
            eventQueue.push(end);
        }
        
    }

};


#endif