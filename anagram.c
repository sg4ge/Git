#include <map>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;
int cmp(const void *pa,const void* pb)
{
	return *(char*)pa-*(char*)pb;
}
void stats_anagram(char** words,int n)
{
	int i,j;
	multimap<char*,char*> anagram_map;
	for(i=0;i!=n;++i)
	{
		int len=strlen(words[i]);
		char *tmp=static_cast<char*>(malloc(len*(sizeof(char)+1)));
		strncpy(tmp,words[i],len);

		for(j=0;j!=len;j++)
		{
			tolower(tmp[j]);
		}
		qsort((void*)tmp,len,sizeof(char),cmp);
		anagram_map.insert(make_pair(tmp,words[i]));
	}
	for(multimap<char*,char*>::iterator iter=anagram_map.begin();iter!=anagram_map.end();++iter)
	{
		cout<<iter->first<<": "<<iter->second<<endl;
	}
}
