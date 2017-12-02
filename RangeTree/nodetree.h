#ifndef NODETREE_H
#define NODETREE_H
#include <vector>

using namespace std;

struct point2D
{

    point2D( int x,  int y)
    {
        xy[0]=x;
        xy[1]=y;
    }
    int color=1;
    int xy[2];
};


struct nodeLayer
{
    nodeLayer(nodeLayer * l, nodeLayer * r , point2D *p):point(p){
        child[0]=l;
        child[1]=r;
    }

    nodeLayer  *child[2];
    point2D *point;

};

class nodeTree
{
    public:
        nodeTree(point2D *dato=nullptr):m_dato(dato){hijos[0]=nullptr;hijos[1]=nullptr;}
        point2D *m_dato;

        nodeTree *hijo_d;
        nodeTree *hijo_i;
        nodeTree *hijos[2]={hijo_i,hijo_d};
        vector<nodeLayer *> * vec_layer;




};



#endif // NODETREE_H
