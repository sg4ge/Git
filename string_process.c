#include"string_process.h"
#include<string.h>
#include<stdlib.h>
int string_compare(const void *str1,const void *str2)
{
	return strcmp(*(const char**)str1,*(const char**)str2);
}

void find_longest_repeated_substring(const char* src,char* sub)
{

//三重循环，时间复杂度位O(n3),很大的字符串耗时太久
#if 0
	int len=strlen(src);
	int i,j;
	int tmp1,tmp2,tmp_len;

	char* longest_substring;
	int substring_length=0;

	for(i=0;i!=len;++i)
		for(j=i+1;j!=len;++j)
		{
			tmp1=i;
			tmp2=j;
			tmp_len=0;
			while(src[j]&&src[tmp1++]==src[tmp2++])
			{
				++tmp_len;
			}
			if(tmp_len>substring_length)
			{
				longest_substring=&src[i];
				substring_length=tmp_len;
			}
		}
	for(i=0;i!=substring_length;++i)
	{
		sub[i]=longest_substring[i];
	}
	sub[substring_length]=0;
#endif

//使用后缀字符串数组

	int len=strlen(src);
	const char** suffix_array=malloc(sizeof(char*)*len);
	int i;
	for(i=0;i!=len;++i)
	{
		suffix_array[i]=&src[i];
	}
	qsort(suffix_array,len,sizeof(char*),string_compare);
	
	int substring_length=0;
	const char* longest_substring;
	const char* tmp1,*tmp2;
	int tmp_len;
	for(i=0;i!=len-1;++i)
	{
		tmp_len=0;
		tmp1=suffix_array[i];
		tmp2=suffix_array[i+1];
		while(*tmp1&&*tmp1++==*tmp2++)
		{
			++tmp_len;
		}
		if(tmp_len>substring_length)
		{
			substring_length=tmp_len;
			longest_substring=suffix_array[i];
		}
	}
	for(i=0;i!=substring_length;++i)
	{
		sub[i]=longest_substring[i];
	}
	sub[substring_length]=0;
}

int find_most_repeated_substring(const char* src,char* sub)
{
	int len=strlen(src);
	int i,j,k;
	const char* tmp1,*tmp2;
	const char* most_repeated_substring=NULL;
	int  max_num=0,tmp_num;
	int substring_length;
	for(i=0;i!=len;++i)
		for(j=1;j<=(len-i)/2;++j)
		{
			tmp_num=1;
			tmp1=&src[i];
			tmp2=&src[i+j];
			while(strncmp(tmp1,tmp2,j)==0)
			{
				tmp1+=j;
				tmp2+=j;
				++tmp_num;
			}
			if(tmp_num>max_num)
			{
				max_num=tmp_num;
				most_repeated_substring=tmp1;
				substring_length=j;
			}
		}
	for(i=0;i!=substring_length;++i)
	{
		sub[i]=most_repeated_substring[i];
	}
	sub[substring_length]=0;
	return max_num;
}

void find_matching_string(const char* src,const char* match_str,char* result_str)
{
	//
	int len=strlen(match_str);
	if(len>strlen(src))
		return;
	int i;
	const char* tmp=src;
	while(strncmp(tmp,match_str,len))
	{
		++tmp;
	}
	strncpy(result_str,tmp,1023);
}

int find_maxsum_sub(const int* src,int src_len,int* sub,int* p_sub_len)
{
	int this_sum=0;
	int max_sum=0;
	int left=0,right=0,left_tmp;
	int i,j;
	for(i=0;i!=src_len;++i)
	{
		if(this_sum<=0)
		{
			this_sum=src[i];
			left_tmp=i;
		}
		else
		{
			this_sum+=src[i];
		}
		if(this_sum>max_sum)
		{
			max_sum=this_sum;
			left=left_tmp;
			right=i;
		}
	}
	if(sub!=NULL&&max_sum)
	{
		for(i=left,j=0;i!=right+1;++i,++j)
		{
			sub[j]=src[i];
		}
	}
	if(p_sub_len!=NULL)
	{
		if(max_sum)
		*p_sub_len=right-left+1;
		else
		*p_sub_len=0;
	}
	return max_sum;
}


/***********************************************************************
 * 在m个数中选n个，有两种可能：选取当前位，在剩下m-1个中选取n-1个
 * 或者不选取当前位，在剩下的m-1个中选取n个
 * **************************************************************************/
void print_all_combination_driver(const char* src,char* combination,int src_use,int com_use,int candidate,int choose)
{
	if(candidate<choose)
		return;
	if(choose==0)
	{
		//char tmp=combination[com_use];
		combination[com_use]=0;
		printf("%s\n",combination);
		//combination[com_use]=tmp;
		return;
	}
	combination[com_use]=src[src_use];
	print_all_combination_driver(src,combination,src_use+1,com_use+1,candidate-1,choose-1);
	print_all_combination_driver(src,combination,src_use+1,com_use,candidate-1,choose);
}
void print_all_combination_driver_bit(const char* src,char* combination)
{
	int len=strlen(src);
	int i,j,k;
	for(i=1;i!=1<<len;++i)
	{	
		k=0;
		for(j=0;j!=len;++j)
		{

			if(i&1<<j)
				combination[k++]=src[j];
		}
		combination[k]=0;
		printf("%s\n",combination);
	}
}
void print_all_combination(const char* src)
{
#if 1
	//递归法求解
	int len=strlen(src);
	char combination[len+1];

	int i;
	for(i=1;i!=len+1;++i)
	{
		print_all_combination_driver(src,combination,0,0,len,i);
	}
#endif
#if 0
	//位操作求解
	int len=strlen(src);
	char combination[len+1];
	print_all_combination_driver_bit(src,combination);
#endif
}

