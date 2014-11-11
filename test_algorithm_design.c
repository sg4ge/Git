#include"algorithm_design.h"
#include<iostream>
using namespace std;
int main()
{
#if 1
element elem[100];
int n=0;
while(cin>>elem[n].name>>elem[n].weight>>elem[n].value)
{
++n;
}
cin.clear();
int bag_weight;
cin>>bag_weight;
int result=bag_complete(elem,n,bag_weight);
cout<<result<<endl;
#endif

#if 0
int i;
for(i=1;i!=20;++i)
cout<<n_queen(i)<<endl;
#endif

#if 0
int arr[1000];
int count=0;
while(cin>>arr[count])
{
count++;
}
cout<<array_divied(arr,count)<<endl;
#endif
#if 0
cout<<android_unlock_total()<<endl;
#endif
}
