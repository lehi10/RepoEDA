#include "rangetree.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <algorithm>
using namespace std;

rangeTree::rangeTree():root(nullptr){
    vec_pts.resize(cant_pts);
    for( int i=0;i<cant_pts;i++)
        vec_pts[i]=new point2D(rand() % _w,rand() % _h);
}

void rangeTree::build()
{
    std::sort(vec_pts.begin(),vec_pts.end(),[](point2D *a, point2D *b){
        return a->xy[0] < b->xy[0];
    });

    int middle=floor(vec_pts.size()/2)-1;
    root=new nodeTree(vec_pts[middle]);

     root->vec_layer= new vector<nodeLayer *>(vec_pts.size());

     for( size_t i=0;i<vec_pts.size();i++)
         (*root->vec_layer)[i]= new nodeLayer(nullptr,nullptr,this->vec_pts[i]);

    root->hijos[0]=new nodeTree;
    rec_build(root->hijos[0],0,middle,root->vec_layer,0,0);


    root->hijos[1]=new nodeTree;
    rec_build(root->hijos[1],middle+1,vec_pts.size()-1,root->vec_layer,middle+1,1);

    sort(root->vec_layer->begin(),root->vec_layer->end(),[](nodeLayer *a, nodeLayer *b)
    {
        return a->point->xy[1]< b->point->xy[1];
    });

}


void rangeTree::rec_build(nodeTree *node, int begin, int end,vector<nodeLayer *>  *layerParent, int beginP,int flagChild)
{
    int middle=ceil((end-begin)/2);
    node->m_dato=vec_pts[begin+middle];
    if( (end-begin) == 0)
        return;

    int size=end-begin+1;
    node->vec_layer= new vector<nodeLayer *>(size);



    for( int i=0;i < size  ;i++)
    {
        (*node->vec_layer)[i]= new nodeLayer( nullptr,nullptr, this->vec_pts[begin+i]);
        (*layerParent)[beginP+i]=(*node->vec_layer)[i];
    }

    std::sort(node->vec_layer->begin(),node->vec_layer->end(),[](nodeLayer *   a , nodeLayer *b)
    {
        return a->point->xy[1] < b->point->xy[1];
    });


    node->hijos[0]=new nodeTree;
    rec_build(node->hijos[0],begin,begin+middle,node->vec_layer,0,0);

    node->hijos[1]=new nodeTree;
    rec_build(node->hijos[1],begin+middle+1,end,node->vec_layer,middle+1,1);
}


int  binarySearch(vector<nodeLayer *>  * arr, int l, int r , int x)
{
    if (r >= l)
    {
         int mid = l + (r - l)/2;
         if ((*arr)[mid]->point->xy[1] == x)
             return mid;
         if ((*arr)[mid]->point->xy[1] > x)
                    return binarySearch(arr, l, mid-1, x);
         return binarySearch(arr, mid+1, r, x);
    }
    return l;
}



void rangeTree::rec_query_pred(nodeTree *node, int val)
{
    if(node->hijos[0]==nullptr || node->hijos[1]==nullptr)
        return;
    if(val <= node->m_dato->xy[0]  )
    {
        rec_query_pred(node->hijos[0],val);
        lookForleaves(node->hijos[1]);
    }
    else
        rec_query_pred(node->hijos[1],val);
    return;
}

void rangeTree::rec_query_succ(nodeTree *node, int val)
{
    if(node->hijos[0]==nullptr || node->hijos[1]==nullptr)
        return;
    if(val > node->m_dato->xy[0] )
    {
        rec_query_succ(node->hijos[1],val);
        lookForleaves(node->hijos[0]);
        /*
        int l=binarySearch(node->hijos[0]->vec_layer,0,node->hijos[0]->vec_layer->size()-1,this->y1);
        int r=binarySearch(node->hijos[0]->vec_layer,0,node->hijos[0]->vec_layer->size()-1,this->y2);
        for(int i=l;i<r;i++)
        {
            (*node->hijos[0]->vec_layer)[i]->point->color=0;
        }
        */
    }
    else
        rec_query_succ(node->hijos[0],val);
    return;
}



void rangeTree::lookForleaves(nodeTree *node)
{


    if(node->hijos[0]==nullptr && node->hijos[1]==nullptr)
    {
        if(y1<node->m_dato->xy[1] &&node->m_dato->xy[1]<y2)
            node->m_dato->color=0;
        return;
    }
    lookForleaves(node->hijos[0]);
    lookForleaves(node->hijos[1]);
    return;

}



void rangeTree::query( int a1, int b1, int a2, int b2)
{
    x1=a1;
    x2=b1;
    y1=a2;
    y2=b2;

    nodeTree * splitNode=split_Node(root,a1,b1);

    if(splitNode!= nullptr)
    {
        rec_query_pred(splitNode->hijos[0],a1);
        rec_query_succ(splitNode->hijos[1],b1);

    }
    return;
}



nodeTree * rangeTree::split_Node(nodeTree *node,  int &a1, int &b1)
{
    if(a1 <= node->m_dato->xy[0] && b1 >= node->m_dato->xy[0])
        return node;

    else
        if(node->hijos[0]!=nullptr && node->hijos[1]!=nullptr)
        {
            if(a1< node->m_dato->xy[0] && b1 < node->m_dato->xy[0])
                split_Node(node->hijos[0],a1,b1);
            else
            {
                if(a1> node->m_dato->xy[0] && b1 > node->m_dato->xy[0])
                    split_Node(node->hijos[1],a1,b1);
                else
                     return nullptr;
            }
        }
        else
            return nullptr;
}


void rangeTree::print(nodeTree *node)
{
    if(!node) return;
    if(node->hijos[0])
    {
        cout<<"\""<<node<<" , "<<node->m_dato->xy[0]<<"\" "<<" -> "<<"\""<<node->hijos[0]<<" , "<<node->hijos[0]->m_dato->xy[0]<<"\""<<endl;
        //cout<<node->m_dato->xy[0]<<" -> "<<node->hijos[0]->m_dato->xy[0]<<endl;
        //cout<<"\""<<node->m_dato->xy[0]<<" , "<<node->m_dato->xy[1]<<"\" "<<" -> "<<"\""<<node->hijos[0]->m_dato->xy[0]<<" , "<<node->hijos[0]->m_dato->xy[1]<<"\""<<endl;
    }

    if(node->hijos[1])
    {
        cout<<"\""<<node<<" , "<<node->m_dato->xy[0]<<"\" "<<" -> "<<"\""<<node->hijos[1]<<" , "<<node->hijos[1]->m_dato->xy[0]<<"\""<<endl;
        //cout<<node->m_dato->xy[0]<<" -> "<<node->hijos[1]->m_dato->xy[0]<<endl;
        //cout<<"\""<<node->m_dato->xy[0]<<" , "<<node->m_dato->xy[1]<<"\" "<<" -> "<<"\""<<node->hijos[1]->m_dato->xy[0]<<" , "<<node->hijos[1]->m_dato->xy[1]<<"\""<<endl;
    }
    print(node->hijos[0]);
    print(node->hijos[1]);
}
