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
		void insert(const char* word);
		int find(const char* word);
		void traverse();
	private:
		void traverse_driver(trie_node* node,char* word,char* tmp);
		trie_node* root;
};
#endif
