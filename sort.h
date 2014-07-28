#ifndef SORT_H
#define SORT_H
#include<cstdlib>
#include<ctime>
template<typename T>
void swap(T& t1,T& t2)
{
	T tmp=t1;
	t1=t2;
	t2=tmp;
}

/*************************************************************
 *************************插入排序*****************************
 *************************************************************/
template<typename T>
void Charu_sort(T* p,int n)
{
	int i,j;
	T tmp;
	for(i=1;i!=n;i++)
	{
		tmp=p[i];
		for(j=i;j>0&&p[j-1]>tmp;j--)
			p[j]=p[j-1];
		p[j]=tmp;
	}
}

/*************************************************************
 **************************希尔排序*****************************
 *************************************************************/

template<typename T>
void shell_sort(T* p,int n)
{
	int i,j,increment;
	T tmp;
	//increment=exp2((int)log2(n))-1;
	for(increment=n/2;increment>0;increment=increment/2)
	{
		for(i=increment;i!=n;i++)
		{
			tmp=p[i];
			for(j=i;j>=increment&&p[j-increment]>tmp;j=j-increment)
				p[j]=p[j-increment];
			p[j]=tmp;
		}
	}
}


/*************************************************************
 **************************堆排序*****************************
 *************************************************************/
inline int lchild(int n) 
{
	return 2*n+1;
}
//把i位置的元素下滤
template<typename T>
void perc_down(T* p,int i,int n)
{
	int child;
	T tmp=p[i];
	while(lchild(i)<=n)
	{
		child=lchild(i);
		if(child<n&&p[child+1]>p[child])
			child++;
		if(p[child]>tmp)
		{
			p[i]=p[child];
			i=child;
		}
		else
		break;
	}
	p[i]=tmp;
}
//堆排序
template<typename T>
void heap_sort(T* p,int n)
{
	int i;

	//建立堆
	for(i=n/2;i>=0;i--)
		perc_down(p,i,n-1);
	//排序
	for(i=n-1;i>0;i--)
	{
		swap(p[0],p[i]);
		perc_down(p,0,i-1);
	}
}

/*************************************************************
 **************************归并排序*****************************
 **************************************************************/

template<typename T>
void merge_sort_driver(T* p,T* tmp,int n)
{
	if(n==1)
		return;

	int center=n/2;
	merge_sort_driver(p,tmp,center);
	merge_sort_driver(p+center,tmp,n-center);

	int lpos=0,rpos=center,tmppos=0;
	while(lpos!=center&&rpos!=n)
	{
		if(p[lpos]<=p[rpos])
			tmp[tmppos++]=p[lpos++];
		else
			tmp[tmppos++]=p[rpos++];
	}
	while(lpos!=center)
	{
		tmp[tmppos++]=p[lpos++];
	}
	while(rpos!=n)
	{
		tmp[tmppos++]=p[rpos++];
	}
	for(tmppos=0;tmppos!=n;tmppos++)
	{
		p[tmppos]=tmp[tmppos];
	}

}

//归并排序
template<typename T>
void merge_sort(T* p,int n)
{
	T *tmp=new T[n];
	merge_sort_driver(p,tmp,n);
	delete [] tmp;
}

/*************************************************************
 ***************************快速排序*****************************
 *************************************************************/
template <typename T>
inline T max(const T& a,const T &b)
{
	return a>b?a:b;
}
template<typename T>
inline T min(const T& a,const T& b)
{
	return a<b?a:b;
}

//计算枢纽元
template<typename T>
int count_hub(T* p,int n)
{
	int	hub_pos;
	//随机选择一个作为枢纽元
	srand(time(NULL));
	hub_pos=rand()%n;
	//三数中值分割法
#if 0
	int cnter=n/2;
	T hub=max(min(p[0],p[center]),min(p[center],p[n-1]));
	switch(hub)
	{
		case p[0]:
			hub_pos=0;
			breakl;
		case p[cnter]:
			hub_pos=cnter;
			break;
		case p[n-1]:
			hub_pos=n-1;
			break;
	}
#endif
	return hub_pos;
	
}

//快速排序
template<typename T>
void quick_sort(T* p,int n)
{
	if(n==0)
		return;
	int hub_pos=count_hub(p,n);
	T hub=p[hub_pos];
	swap(p[n-1],p[hub_pos]);

	int left=0,right=n-2;
	while(left<n-1&&right>0)
	{
		while(p[left]<hub)
			++left;
		while(p[right]>hub)
			--right;
		if(left<right)
			swap(p[left++],p[right--]);
		else
			break;
	}
	swap(p[left],p[n-1]);
	quick_sort(p,left);
	quick_sort(p+left+1,n-left-1);
}
#endif
