#include"trie_tree.h"
#include<iostream>
void trie_tree::insert(const char* word)
{
	trie_node* tmp=root;
	while(*word!=0)
	{
		std::cout<<"test"<<std::endl;
		if(tmp->childs[*word-'a']==0)
		{
			tmp->childs[*word-'a']=new trie_node;
		}
		++(tmp->childs[*word-'a']->frequence);
		tmp=tmp->childs[*word-'a'];
		++word;
	}
	tmp->is_word=true;
}
int trie_tree::find(const char* word)
{
	trie_node* tmp=root;
	while(*word!=0)
	{
		if(tmp->childs[*word-'a']==0)
			return 0;
		tmp=tmp->childs[*word-'a'];
		++word;
	}
	return tmp->frequence;
}
void trie_tree::traverse_driver(trie_node* node,char* word,char* tmp)
{
int i;
	for(i=0;i!=NUMBER_OF_LETTER;++i)
	{
		if(node->childs[i]!=NULL)
		{
			*tmp++='a'+i;
			if(node->childs[i]->is_word)
			{
				*tmp=0;
				std::cout<<word<<"\t"<<node->childs[i]->frequence<<std::endl;
			}
			traverse_driver(node->childs[i],word,tmp);
			--tmp;
		}
	}
}
void trie_tree::traverse()
{
	char word[30];
	traverse_driver(root,word,word);
}
