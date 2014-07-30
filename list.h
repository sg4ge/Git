#ifndef LIST_H
#define LIST_H
//节点
template<typename T> class node
{
	public:
		node(const T& t):data(t),pnext(NULL){}
		T data;
		node* pnext;

};

template<typename T> class list
{
	public:
		list():head(NULL),size(0){}
		void insert(const T& t);
		void del(const T& t);
		void reverse();
		void traverse(void(*f)(const T& data));
	private:
		int is_empty()
		{
			return !size;
		}
		node<T>* head;
		int size;
};

template<typename T>void list<T>::insert(const T& t)
{
	node<T>* ptr_node_to_insert=new node<T>(t);
	//链表为空
	if(is_empty())
	{
		head=ptr_node_to_insert;
		++size;
		return;
	}

	node<T>* tmp1=head;
	node<T>* tmp2=NULL;
	while(tmp1->data<=ptr_node_to_insert->data&&tmp1->pnext!=NULL)
	{
		tmp2=tmp1;
		tmp1=tmp1->pnext;
	}
	//在链表尾部插入
	if(tmp1->data<=ptr_node_to_insert->data)
	{
		tmp1->pnext=ptr_node_to_insert;
	}
	//在链表中间插入
	else if(tmp2!=NULL)
	{
		tmp2->pnext=ptr_node_to_insert;
		ptr_node_to_insert->pnext=tmp1;
	}
	//在链表头部插入
	else
	{
		head=ptr_node_to_insert;
		ptr_node_to_insert->pnext=tmp1;
	}	
	++size;
}

template<typename T>void list<T>::del(const T& t)
{
	if(is_empty())
		return;

	node<T>* tmp1=head;
	node<T>* tmp2=NULL;
	while(tmp1->data!=t&&tmp1->pnext!=NULL)
	{
		tmp2=tmp1;
		tmp1=tmp1->pnext;
	}
	//没有这个元素
	if(tmp1->data!=t)
		return;
	//从头部删掉
	else if(tmp2==NULL)
	{
		head=tmp1->pnext;
		delete tmp1;
	}
	//从中间或尾部删掉
	else if(tmp2!=NULL)
	{
		tmp2->pnext=tmp1->pnext;
		delete tmp1;
	}
	--size;
}
template<typename T> void list<T>::reverse()
{
	node<T>* tmp1=head;
	node<T>* tmp2=NULL;
	node<T>* tmp3;
	while(tmp1!=NULL)
	{
		tmp3=tmp1->pnext;
		tmp1->pnext=tmp2;
		tmp2=tmp1;
		tmp1=tmp3;
	}
	head=tmp2;
}
template<typename T>void list<T>::traverse(void(*f)(const T& data))
{
	if(!is_empty())
	{
		node<T>* tmp=head;
		while(tmp!=NULL)
		{
			f(tmp->data);
			tmp=tmp->pnext;
		}
	}
}
#endif
