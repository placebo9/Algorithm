/*
This Code is Defining an array
Making Segment Tree from array
Giving Updation to segement Tree using lazy propagation and firing queries for given range for finding maximum in that range
*/
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;
# define size 1000000
# define inf 0x7fffffff
#define N 10
int arr[N];
int Tree[size];
int Lazy[size];

int max(int a,int b)
{
  return (a>b)?a:b;
}

void Create_Tree(int node,int a,int b)
{
  if(a>b)
  return;
  if(a==b)
  {
    Tree[node]=arr[a];
    return;
  }
  Create_Tree(node*2,a,(a+b)/2);
  Create_Tree(node*2+1,(a+b)/2+1,b);
  Tree[node]=max(Tree[node*2],Tree[node*2+1]);
}

void Update_Tree(int node,int a,int b,int i,int j,int val)
{
  if(Lazy[node]!=0)
  {
    Tree[node]+=Lazy[node];
    if(a!=b)
    {
      Lazy[node*2]+=Lazy[node];
      Lazy[node*2+1]=Lazy[node];
    }
    Lazy[node]=0;
  }
  if(a>b||j<a||i>b)
  return;
  if(a>=i&&b<=j)
  {
    Tree[node]+=val;
    if(a!=b)
    {
      Lazy[node*2]+=val;
      Lazy[node*2+1]+=val;
    }
    return;
  }
  
  Update_Tree(node*2,a,(a+b)/2,i,j,val);
  Update_Tree(node*2+1,(a+b)/2+1,b,i,j,val);
  Tree[node]=max(Tree[node*2],Tree[node*2+1]);
}

int Query_Tree(int node,int a,int b,int i,int j)
{
  if(a>b||j<a||i>b)
  return -inf; 
  
  if(Lazy[node]!=0)
  {
    Tree[node]+=Lazy[node];
    if(a!=b)
    {
      Lazy[node*2]+=Lazy[node];
      Lazy[node*2+1]=Lazy[node];
    }
    Lazy[node]=0;
  }
  
  if(a>=i&&b<=j)
  return Tree[node];
  
  int q1=Query_Tree(node*2,a,(a+b)/2,i,j);
  int q2=Query_Tree(node*2+1,(a+b)/2+1,b,i,j);
  
  return max(q1,q2);
}

int main()
{
  memset(Lazy,0,sizeof Lazy);
  for(int i=0;i<N;i++)
  cin>>arr[i];
  Create_Tree(1,0,N-1);
  int i,j,val;
  cin>>i>>j>>val;
  Update_Tree(1,0,N-1,i,j,val);
  cout<<Query_Tree(1,0,N-1,0,N-1);
}
