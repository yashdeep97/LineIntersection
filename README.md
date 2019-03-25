# LineIntersection
Computational Geometry Assignment 1

# Results
We have given an implementation of the Bentley-Ottmann plane sweep algorithm for line segment intersection. The implementation is complete and reliable in the sense that it will work for all input instances.

## Status Tree Generation
Insertion happens at a given Y - Co-ordinate which is 2 for this case.
- (0,0) (0,2)
- (0,0) (2,2)
- (0,0) (2,4)
- (0,0) (2,6)
- (0,0) (2,8)
Generating the tree:

0.000000 0.000000 2.000000 6.000000 4
0.000000 0.000000 0.000000 2.000000 3
0.000000 0.000000 0.000000 2.000000 1
0.000000 0.000000 2.000000 8.000000 2
0.000000 0.000000 2.000000 8.000000 1
0.000000 0.000000 2.000000 6.000000 1
0.000000 0.000000 2.000000 4.000000 2
0.000000 0.000000 2.000000 4.000000 1
0.000000 0.000000 2.000000 2.000000 1

Popping the line (0,0) - (2,6) at Y = 2 yields the tree:

0.000000 0.000000 2.000000 4.000000 4
0.000000 0.000000 0.000000 2.000000 3
0.000000 0.000000 0.000000 2.000000 1
0.000000 0.000000 2.000000 8.000000 2
0.000000 0.000000 2.000000 8.000000 1
0.000000 0.000000 2.000000 2.000000 2
0.000000 0.000000 2.000000 4.000000 1

## Event Queue Generation
Let the event points be (assuming all upper end points to show the value of U stored):

- (1,2)
- (2,3)
- (3,4)
- (3,6)
- (3,5)
Generating the tree:

2.000000 3.000000 3
 U:2.000000 3.000000 3.000000 4.000000
1.000000 2.000000 1
 U:1.000000 2.000000 2.000000 1.000000
3.000000 5.000000 2
 U:3.000000 5.000000 4.000000 3.000000
3.000000 4.000000 1
 U:3.000000 4.000000 2.000000 3.000000
3.000000 6.000000 1
 U:3.000000 6.000000 7.000000 4.000000

 Popping results:

Popping event point 3.000000,6.000000
New Tree:
2.000000 3.000000 3
 U:2.000000 3.000000 3.000000 4.000000
1.000000 2.000000 1
 U:1.000000 2.000000 2.000000 1.000000
3.000000 5.000000 2
 U:3.000000 5.000000 4.000000 3.000000
3.000000 4.000000 1
 U:3.000000 4.000000 2.000000 3.000000

##Main algorithm

For the lines:

- (1,1) - (11,11)
- (1,11) - (11,1)
- (1,11) - (11,11)
- (11,11) - (11,1)
- (11,1) - (1,1)
- (1,1) - (1,11)

Results:

Intersection: 1.000000 11.000000
Intersection: 11.000000 11.000000
Intersection: 6.000000 6.000000
Intersection: 1.000000 1.000000
Intersection: 11.000000 1.000000

Execution complete
Execution time in secinds: 0.191
