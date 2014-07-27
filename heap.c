#include "heap_fuxi.h"
int main()
{
	heap<int> h1;
	int tmp;
	while(cin>>tmp)
	{	
		h1.insert(tmp);
	}
	cin.clear();
	while(!h1.is_empty())
	{
		cout<<h1.delete_min()<<"\t";
	}
	cout<<endl;
}
