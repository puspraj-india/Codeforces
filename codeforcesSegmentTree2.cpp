#include<bits/stdc++.h>
using namespace std;

struct segmentTree
{
  int *left,*right;
  long long int *arr,*delta,n;
  segmentTree(int n,long long int *ar)
  {
    this->n=n;
    left=new int[4*n+1];
    right=new int[4*n+1];
    arr=new long long int[4*n+1];
    delta=new long long int[4*n+1];
    for(int i=1;i<4*n+1;i++)
    {
      left[i]=right[i]=arr[i]=delta[i]=0;
    }
    partition(1,0,n-1,ar);
  }
  void partition(int index,int a,int b,long long int *ar)
  {

    if(a==b)
    {
      left[index]=a;
      right[index]=b;
      arr[index]=ar[a];
      return;
    }
    left[index]=a;
    right[index]=b;
    int mid=(a+b)/2;
    partition(2*index,a,mid,ar);
    partition(2*index+1,mid+1,b,ar);
    update(index);
  }
  void increment(int index,int a,int b,int val)
  {
    if(left[index]>b||right[index]<a)
    return;
    if(left[index]>=a && right[index]<=b)
    {
      delta[index]^=val;
      return;
    }
    propagation(index);
    increment(2*index,a,b,val);
    increment(2*index+1,a,b,val);

  }
  void propagation(int index)
  {

    delta[2*index]^=delta[index];
    delta[2*index+1]^=delta[index];
    delta[index]=0;
  }

  long long int pushdown(int index,int a,int b)
  {
    if(b<left[index]||a>right[index])
    {
      return 0;
    }
    if(left[index]==right[index])
    {
      arr[index]^=delta[index];
      delta[index]=0;
      return arr[index];
    }
    delta[2*index]^=delta[index];
    delta[2*index+1]^=delta[index];
    delta[index]=0;
    long long leftnode=pushdown(2*index,a,b);
    long long rightnode=pushdown(2*index+1,a,b);
    update(index);
    return leftnode+rightnode;
    /*
    if(left[2*index]==right[2*index])
    {
      arr[2*index]^=delta[2*index];
      delta[2*index]=0;
    }
    if(right[2*index+1]==left[2*index+1])
    {
      arr[2*index+1]^=delta[2*index+1];
      delta[2*index+1]=0;
    }
    */


  }
  void update(int index)
  {
    arr[index]=(arr[2*index])+(arr[2*index+1]);
  }
  long long int summation(int index,int a,int b)
  {
    if(a>right[index]||b<left[index])
    return 0;
    if(a<=left[index] &&b>=right[index])
    {
      return arr[index];
    }
      long long int temp=summation(2*index,a,b)+summation(2*index+1,a,b);
      update(index);
      return temp;
  }


};


int main()
{
  int n,x;
  cin>>n;
  long long int a[n];
  for(int i=0;i<n;i++)
  {
    cin>>a[i];
  }
  segmentTree obj(n,a);
  int k,q,l,r,val;
  cin>>k;
  for(int i=0;i<k;i++)
  {
    cin>>q;
    if(q==1)
    {
      cin>>l>>r;
      cout<<obj.pushdown(1,l-1,r-1)<<endl;
      //cout<<obj.summation(1,l-1,r-1)<<endl;
    }
    else
    {
      cin>>l>>r>>val;
      obj.increment(1,l-1,r-1,val);
    }
  }
}

















/*

#include<bits/stdc++.h>
using namespace std;

struct segmentTree
{
  long*arr,*delta;
  int *left,*right,n;
  segmentTree(int n,long*ar)
  {
    this->n=n;
    left=new int[4*n+1];
    right=new int[4*n+1];
    arr=new long[4*n+1];
    delta=new long[4*n+1];
    for(int i=1;i<4*n+1;i++)
    {
      left[i]=right[i]=0;
      arr[i]=delta[i]=0;
    }
    cout<<"hi";
    partition(1,0,n-1,ar);
  }
  void partition(int index,int a,int b,long *ar)
  {

    if(a==b)
    {
      left[index]=a;
      right[index]=b;
      arr[index]=ar[a];
      return;
    }
    left[index]=a;
    right[index]=b;
    int mid=a-(b-a)/2;
    partition(2*index,a,mid,ar);
    partition(2*index+1,mid+1,b,ar);
    update(index);
  }
  void increment(int index,int a,int b,long val)
  {
    if(left[index]>b||right[index]<a)
    return;
    if(left[index]>=a && right[index]<=b)
    {
      delta[index]^=val;
      return;
    }
    propagation(index);
    increment(2*index,a,b,val);
    increment(2*index+1,a,b,val);

  }
  void propagation(int index)
  {

    delta[2*index]^=delta[index];
    delta[2*index+1]^=delta[index];
    delta[index]=0;
  }

  void pushdown(int index,int a,int b)
  {
    if(b<left[index]||a>right[index])
    {
      return;
    }
    if(left[index]==right[index])
    {
      arr[index]^=delta[index];
      delta[index]=0;
      return;
    }
    delta[2*index]^=delta[index];
    delta[2*index+1]^=delta[index];
    delta[index]=0;
    pushdown(2*index,a,b);
    pushdown(2*index+1,a,b);
    update(index);


  }
  void update(int index)
  {
    arr[index]=(arr[2*index])+(arr[2*index+1]);
  }
  long long summation(int index,int a,int b)
  {
    if(a>right[index]||b<left[index])
    return 0;
    if(a<=left[index] &&b>=right[index])
    {
      return arr[index];
    }
      long long temp=summation(2*index,a,b)+summation(2*index+1,a,b);
      update(index);
      return temp;
  }


};


int main()
{
  int n,x;
  cin>>n;
  long *a=new long [n];
  for(int i=0;i<n;i++)
  {
    cin>>a[i];
  }
  segmentTree obj(n,a);
  long k,q,l,r,val;
  cin>>k;
  for(int i=0;i<k;i++)
  {
    cin>>q;
    if(q==1)
    {
      cin>>l>>r;
      obj.pushdown(1,l-1,r-1);
      cout<<obj.summation(1,l-1,r-1)<<endl;
    }
    else
    {
      cin>>l>>r>>val;
      obj.increment(1,l-1,r-1,val);
    }
  }
}

*/
