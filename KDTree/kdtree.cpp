#include "kdtree.h"
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


KDTree::KDTree(int dimention)
{
    this->root=nullptr;
    this->dim=dimention;
}


void KDTree::insert(KDNode *node)
{ if(root==nullptr)
    {
     root=node;
     return;
    }
    insertRec(root,node,0);
}


void KDTree::insertVecCoord(int dimention,vector<float> *vec)
{
    KDNode *node=new KDNode(dimention,vec);
    if(root==nullptr)
    {
         root=node;
         node->hv=0;
         node->setLimits(0,_w,0,_h);
         node->parent=nullptr;
         return;
    }
    insertRec(root,node,0);
}

void KDTree::print(KDNode *node)
{
    if(!node)
        return;
    if(node->children[0])
    {
        cout<<"\"";
        for(int i=0;i<dim;i++)
            cout<<(*node->coordK)[i]<<"-";
        cout<<"\"";

        cout<<" -> ";
        cout<<"\"";
        for(int i=0;i<dim;i++)
            cout<<(*node->children[0]->coordK)[i]<<"-";
        cout<<"\""<<endl;
    }
    print(node->children[0]);
    if(node->children[1])
    {
        cout<<"\"";
        for(int i=0;i<dim;i++)
            cout<<(*node->coordK)[i]<<"-";
        cout<<"\"";

        cout<<" -> ";

        cout<<"\"";
        for(int i=0;i<dim;i++)
            cout<<(*node->children[1]->coordK)[i]<<"-";
        cout<<"\""<<endl;
    }
    print(node->children[1]);
}


void KDTree::insertRec(KDNode *nodeIt, KDNode *newNode, int i_dim)
{
    if((*nodeIt->coordK)[i_dim] < (*newNode->coordK)[i_dim])
    {
        if(nodeIt->children[1])
            return insertRec(nodeIt->children[1],newNode,(i_dim+1)%this->dim);
        newNode->hv=(i_dim+1)%this->dim;

        if(newNode->hv==1)
            newNode->setLimits( (*nodeIt->coordK)[0],   nodeIt->xf,
                                nodeIt->yi,             nodeIt->yf);
        else
            newNode->setLimits( nodeIt->xi,             nodeIt->xf,
                                (*nodeIt->coordK)[1],   nodeIt->yf);
        newNode->parent=nodeIt;
        nodeIt->children[1]=newNode;
    }
    else
    {
        if(nodeIt->children[0])
            return insertRec(nodeIt->children[0],newNode,(i_dim+1)%this->dim);
        newNode->hv=(i_dim+1)%this->dim;
        if(newNode->hv==1)
            newNode->setLimits( nodeIt->xi, (*nodeIt->coordK)[0],
                                nodeIt->yi, nodeIt->yf);
        else
            newNode->setLimits( nodeIt->xi, nodeIt->xf,
                                nodeIt->yi, (*nodeIt->coordK)[1]);
        newNode->parent=nodeIt;
        nodeIt->children[0]=newNode;
    }

}


KDNode *KDTree::find(KDNode *node, vector<float> *point,float & minDis)
{
    float distance= sqrt(pow((*node->coordK)[0]-(*point)[0],2) + pow((*node->coordK)[1]-(*point)[1],2)) ;
    minDis=min(distance,minDis);

    if((*node->coordK)[node->hv] >= (*point)[node->hv])
    {
        if(node->children[0]==nullptr)
            return node;
        return find(node->children[0],point,minDis);
    }
    else
    {
        if(node->children[1]==nullptr)
            return node;
        return find(node->children[1],point,minDis);
    }
}



void KDTree::goRoot(KDNode *node,vector<float> *point, float &minDis)
{
    if(node==root)
        return;

    float distance= sqrt(pow((*node->coordK)[0]-(*point)[0],2) + pow((*node->coordK)[1]-(*point)[1],2)) ;
    if(distance <= minDis)
    {
        minDis=min(minDis,distance);
        closerPoint=node;
    }
    goRoot(node->parent,point,minDis);
}

void KDTree::otherBrach(KDNode *node,vector<float> *point, float & minDis)
{
    if(node==nullptr)
        return;
    float distance= sqrt(pow((*node->coordK)[0]-(*point)[0],2) + pow((*node->coordK)[1]-(*point)[1],2)) ;
    if(distance <= minDis)
    {
        minDis=min(minDis,distance);
        closerPoint=node;
    }
    otherBrach(node->children[0],point,minDis);
    otherBrach(node->children[1],point,minDis);
}



bool inRange(KDNode *node,float *ptni, float *pntf)
{

    if( ptni[0]<=(*node->coordK)[0] && (*node->coordK)[0]<=pntf[0] && ptni[1]<=(*node->coordK)[1] && (*node->coordK)[1]<=pntf[1])
            return true;
    return false;
}

void range_rec(KDNode *node,float *ptni, float *pntf)
{


    if(node==nullptr)
        return;

    if(inRange(node,ptni,pntf))
         node->color=1;

    if( pntf[node->hv] >  (*node->coordK)[node->hv]  )
        range_rec(node->children[1],ptni,pntf);

    if( ptni[node->hv] < (*node->coordK)[node->hv]  )
        range_rec(node->children[0],ptni,pntf);
    return;

}

void KDTree::range(float x0, float y0, float xf, float yf)
{
    float *pnti=new float[this->dim];
    pnti[0]=x0;
    pnti[1]=y0;

    float *pntf=new float[this->dim];
    pntf[0]=xf;
    pntf[1]=yf;

    range_rec(root,pnti,pntf);
}



KDNode *KDTree::shortPath(KDNode *node, vector<float> *point)
{
    float minDis=99999999;
    KDNode * baseNode=find(node,point,minDis);
    closerPoint=baseNode;
    goRoot(baseNode,point,minDis);
    otherBrach(root,point,minDis);
    return closerPoint;
}






