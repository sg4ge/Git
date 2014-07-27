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
	heap<int> h2;
	h2=h1;
	h1.traverse();
	h2.traverse();
}
