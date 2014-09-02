#include<stdio.h>
#include<string.h>
#include<assert.h>
char* BF_CMP(const char* src1,const char* src2)
{
	int i,j;
	i=0;
	int len1=strlen(src1);
	int len2=strlen(src2);
	while(i!=len1)
	{
		j=0;
		while(src1[i]==src2[j]&&j!=len2&&i!=len1)
		{
			++i;
			++j;
		}
		if(len2==j)
			return &src1[i-j];
		else
			i=i-j+1;
	}
	return NULL;
}
void get_next(const char* str,int* next)
{
	int len=strlen(str);
	int i=0,j=-1;
	next[0]=-1;
	while(i!=len)
	{
		if(j==-1||str[i]==str[j])
		{
			++i;
			++j;
			next[i]=j;
		}
		else
		{
			j=next[j];
		}
	}
}
char* KMP_CMP(const char* str1,const char* str2)
{
	int len1=strlen(str1);
	int len2=strlen(str2);
	int next[len2+1];
	get_next(str2,next);
	int i,j;
	i=0;
	j=0;
	while(i!=len1)
	{
		if(str1[i]==str2[j]||j==-1)
		{
			++i;
			++j;
		}
		else
			j=next[j];
		if(len2==j)
			return &str1[i-j];
	}
	return NULL;
}
int main()
{
	char s1[100];
	char s2[100];
	fgets(s1,100,stdin);
	fgets(s2,100,stdin);
	int len1=strlen(s1);
	int len2=strlen(s2);
	s1[len1-1]=0;
	s2[len2-1]=0;
	char* result=KMP_CMP(s1,s2);
	if(result)
		printf("%s\n",result);
	else
		printf("No match!\n");
}
