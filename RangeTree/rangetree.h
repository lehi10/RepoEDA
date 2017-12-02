#ifndef RANGETREE_H
#define RANGETREE_H

#include <vector>
#include <iostream>
#include "nodetree.h"

/*
#define cant_pts 10000000
#define _w 3600
#define _h 2400
*/

#define cant_pts 100000
#define _w 3000
#define _h 2000



using namespace std;

class rangeTree
{
public:
    nodeTree *root;
    vector<point2D*> vec_pts;

    rangeTree();

    void rec_build(nodeTree *node, int begin, int end,vector<nodeLayer *>  *layerParent, int beginP,int flagChild);
    void build();


    void print(nodeTree *node);
    void query( int a1,  int b1,  int a2,  int b2);
    nodeTree * split_Node(nodeTree *node,  int &a1,  int &a2);
    void rec_query_pred(nodeTree *node,  int val);
    void rec_query_succ(nodeTree *node,  int val);

    void lookForleaves(nodeTree *node );


     int x1,x2;
     int y1,y2;


};

#endif // RANGETREE_H




