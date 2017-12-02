#include <iostream>
#include <algorithm>
using namespace std;



int maxsum1D(int *arr,int n)
{
    int currentSum=arr[0];
    int maxSum=arr[0];
    for(int i=1;i<n;i++)
    {
        currentSum=max(arr[i],arr[i]+currentSum);
        if(currentSum > maxSum)
            maxSum=currentSum;
    }
    return maxSum;
}

int Maxssum()
{   
    int N;
    cin>>N;
    int matrix[N][N];
    
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            cin>>matrix[i][j];
    
    
    int *itArr=new int[N];
    int currentSum=0;
    int maxSum=0;
    
    for(int i=0;i<N;i++)
    {
        
        for(int j=i;j<N;j++)
        {
            if(j==i)
                for(int k=0;k<N;k++)
                    itArr[k]=matrix[j][k];                
            else
                for(int k=0;k<N;k++)
                    itArr[k]+=matrix[j][k];                
            currentSum=maxsum1D(itArr,N);
            if(currentSum > maxSum )
                maxSum=currentSum;
        }   
    }
    return maxSum;
}

int main()
{
    cout<<Maxssum()<<endl;   
    return 0;
}


