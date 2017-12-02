#ifndef KDTREE_H
#define KDTREE_H
#include <vector>
#include <iostream>


#define _w 3000
#define _h 2000

using namespace std;


class KDNode
{
    public:
        KDNode(int dimention,vector<float> *coord):dim(dimention),coordK(coord){
            children[0]=nullptr;
            children[1]=nullptr;
            parent=nullptr;
        }
        void setLimits(int _xi,int _xf,int _yi,int _yf){ xi=_xi; xf=_xf; yi=_yi ;yf= _yf;}

        unsigned int dim;
        vector<float> *coordK;
        KDNode *children[2];
        KDNode *parent;

        int hv=0;
        float xi=0,xf=0;
        float yi=0,yf=0;

        int color=0;
        int size=3;
};



class KDTree
{
    public:

        KDTree():root(nullptr){}
        KDTree(int dimention);
        void insert(KDNode *node);
        void insertVecCoord(int dimention,vector<float> *vec);
        void print(KDNode *node);

        void insertRec(KDNode *nodeiT,KDNode *newNode, int i_dim);
        KDNode *find(KDNode * node, vector<float> * point,float &minDis);
        KDNode *shortPath(KDNode * node, vector<float> * point);
        void goRoot(KDNode *node,vector<float> *point, float &minDis);
        void otherBrach(KDNode *node,vector<float> *point, float &minDis);

        void range(float x0,float y0,float x2,float y2);



        KDNode *root;
        int dim;
        KDNode *closerPoint=nullptr;




};


#endif // KDTREE_H
