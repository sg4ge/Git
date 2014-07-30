#include "heap.h"
int main()
{
	heap<int> h1;
	int tmp;
	while(cin>>tmp)
	{	
		h1.insert(tmp);
	}
	heap<int> h2(h1);
	cin.clear();
	while(!h2.is_empty())
	{
		cout<<h2.delete_min()<<"\t";
	}
	cout<<endl;
}
