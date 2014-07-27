#include<cstdlib>
#include<iostream>
#include<cstring>
using namespace std;
inline int lchild(int n)
{
	return 2*n;
}
inline int rchid(int n)
{
	return 2*n+1;
}
inline int parent(int n)
{
	return n/2;
}
template<typename T> class heap
{
	public:
		heap(int n=100);
		heap(heap<T>& hp);
		heap<T>& operator=(heap<T>& hp);

		void traverse();
		void insert(const T& t);
		T delete_min();

		~heap();
	private:
		T* pelem;
		int size;
		const int max_size;
};
template<typename T> heap<T>::heap(int n):size(0),max_size(n)
{
	pelem=static_cast<int*>(malloc(sizeof(T)*max_size));
}
template<typename T> heap<T>::heap(heap<T> &hp):size(hp.size),max_size(hp.max_size)
{
	pelem=static_cast<int*>(malloc(sizeof(T)*max_size));
	memcpy(pelem,hp.pelem,(size+1)*sizeof(T));
}
template<typename T> heap<T>& heap<T>::operator=(heap<T>& hp)
{
	heap<T> tmp=hp;

	T* p=tmp.pelem;
	tmp.pelem=pelem;
	pelem=p;
	
	size=tmp.size;
	return *this;
}
template<typename T> heap<T>::~heap()
{
	delete [] pelem;
}
template<typename T>void heap<T>::insert(const T& t)
{
	int n=size+1;
	while(parent(n)>0)
	{
		if(pelem[parent(n)]>t)
		{
			pelem[n]=pelem[parent(n)];
			n=parent(n);
		}
		else
			break;
	}
	pelem[n]=t;
	++size;
}
template<typename T>T heap<T>::delete_min()
{
	T min_elem=pelem[1];
	T max_elem=pelem[size];
	int n=1;
	while(lchild(n)<=size)
	{
		int child=lchild(n);
		if(lchild(n)<size&&pelem[rchild(n)]<pelem[lchild(n)])
			++child;
		if(pelem[child]<pelem[n])
			pelem[n]=pchild;
		else
			break;
	}
	pelem[n]=max_elem;
	return min_elem;
}
template<typename T>void heap<T>::traverse()
{
	int i;
	for(i=1;i!=size+1;++i)
		cout<<pelem[i]<<"\t";
	cout<<endl;
}
