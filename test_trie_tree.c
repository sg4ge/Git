#include<stdio.h>
#include"string_process.h"
#define MAX 1000000
int main(int argc,char** argv)
{
	char string[MAX];
	char substring[1024];

	puts("载入文件中。。。");
	FILE* fp=fopen(argv[1],"r");
	char* tmp=string;
	while(fread(tmp,sizeof(char),1024,fp)==1024)
	{
		tmp+=1024;
	}

	puts("载入完成，开始查找");
	//find_longest_repeated_substring(string,substring);
	//int num;
	//find_most_repeated_substring(string,substring,&num);
	find_matching_string(string,argv[2],substring);
	printf("%s\n",substring);
	
}
