#include<bits/stdc++.h>
using namespace std;

struct segmentTree
{
  long *arr,*left,*right,n;
  segmentTree(int n)
  {
    this->n=n;
    long temp=4*(1<<n)+1;
    arr=new long[temp];
    left=new long[temp];
    right=new long[temp];
    for(long i=0;i<temp;i++)
    {
      arr[i]=left[i]=right[i]=0;
    }
    partition(1,0,(1<<n)-1);
  }
  void partition(int index,int a,int b)
  {
    left[index]=a;
    right[index]=b;
    if(a==b)
    return;
    long mid=(a+b)/2;
    partition(2*index,a,mid);
    partition(2*index+1,mid+1,b);
  }
  void update(int index,int a,int val,int n)
  {
    if(right[index]<a||left[index]>a)
    return;
    if(left[index]==a &&right[index]==a)
    {
        arr[index]=val;
      return;
    }
    update(index*2,a,val,n-1);
    update(index*2+1,a,val,n-1);
    pushup(index,n);
  }
  void pushup(int index,int n)
  {
    if(n%2==1)
    {
      arr[index]=arr[2*index]|arr[2*index+1];
    }
    else
    {
      arr[index]=arr[2*index]^arr[2*index+1];
    }
  }
  void displayarr()
  {
    for(int i=1;i<=4*(1<<n);i++)
    {
      cout<<"["<<left[i]<<","<<right[i]<<"] = "<<arr[i]<<endl;
    }
  }
  long result()
  {
    return arr[1];
  }
};


int main()
{
  long n,m,x,p,b;

  cin>>n>>m;
  segmentTree obj(n);
  long temp=1<<n;
  for(long i=0;i<temp;i++)
  {
    cin>>x;
    obj.update(1,i,x,n);
  }
  //obj.displayarr();
  for(int i=0;i<m;i++)
  {
    cin>>p>>b;
    obj.update(1,p-1,b,n);
    cout<<obj.result()<<endl;
  }


}
