#ifndef TRIE_TREE_H
#define TRIE_TREE_H
#define NUMBER_OF_LETTER 26
class trie_node
{
	public:
		trie_node():is_word(false),frequence(0)
		{
			int i;
			for(i=0;i!=NUMBER_OF_LETTER;++i)
				childs[i]=0;
		}
		trie_node* childs[NUMBER_OF_LETTER];
		bool is_word;
		int frequence;
};
class trie_tree
{
	public:
		trie_tree()
		{
			root=new trie_node;
		}
		//将一个单词插入树中
		void insert(const char* word);
		//找到一个单词出现的频率
		int find(const char* word);
		//遍历整棵树，找出所有单词
		void traverse();
		~trie_tree()
		{
			delete_tree(root);
		}
	private:
		//遍历驱动函数
		void traverse_driver(trie_node* node,char* word,char* tmp);
		//删除树
		void delete_tree(trie_node* node);
		trie_node* root;
};
#endif
