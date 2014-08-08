#include "algorithm_design.h"
#include <stdio.h>
int bag_01(const element* elements,int n,int weight)
{
//空间复杂度O(MN),背包不要求完全装满
#if 0
	int max[n+1][weight+1];
	int i,j;
	for(i=0;i!=weight+1;++i)
	{
		max[0][i]=0;
	}
	for(i=0;i!=n+1;++i)
	{
		max[i][0]=0;
	}
	for(i=1;i!=n+1;++i)
		for(j=1;j!=weight+1;++j)
		{
			if(elements[i-1].weight<=j)
			{
				if(max[i-1][j-elements[i-1].weight]+elements[i-1].value>max[i-1][j])
					max[i][j]=max[i-1][j-elements[i-1].weight]+elements[i-1].value;
				else
					max[i][j]=max[i-1][j];
			}
			else
				max[i][j]=max[i-1][j];
		}
	return max[n][weight];
#endif

//空间复杂度O(M)，背包完全装满
#if 1
	int max[weight+1];

	//记录路径
	int path[n+1][weight+1];
	int i,j;
	max[0]=0;
	for(i=1;i!=weight+1;++i)
	{
		max[i]=-1;
	}
	for(i=1;i!=n+1;++i)
	{
		for(j=weight;j!=0;--j)
		{
			if(elements[i-1].weight<=j)
			{
				if(max[j-elements[i-1].weight]!=-1&&max[j-elements[i-1].weight]+elements[i-1].value>max[j])
				{
					max[j]=max[j-elements[i-1].weight]+elements[i-1].value;

					//表示max[j]使用了第i个物品
					path[i][j]=1;
				}
			}
		}
	}

	/*
	//打印出背包里具体的东西
	for(i=n,j=weight;j>0;--i)
	{
		if(path[i][j]==1)
		{
			j-=elements[i-1].weight;
			printf("%d\t",elements[i-1].name);
		}
	}
	puts("");
	*/

	return max[weight];
#endif
}
/*int bag_01_backtrack(element* elements,int n,int bag_weight,int* elem_used,int elem_used_num,int total_weight,int total_value)
{
	if(elements[elem_used_num].weight+total_weight<bag_weight)
	{
		elem_used[elem_used_num]=1;
	}
	else if(elements[elem_used_num])
}*/




/******************************************************************************/
void swap(int *a,int *b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
void n_queen_driver(int* queen,int size,int length,int* p_count)
{
//回溯法
#if 0
	if(length==size)
	{
		++*p_count;
		return;
	}
	int i,j;
	int flag;
	for(i=0;i!=size;++i)
	{
		flag=1;
		queen[length]=i;
		for(j=0;j<length;++j)
		{
			if(queen[length]==queen[j]||(queen[length]-queen[j])==(length-j)||(queen[length]-queen[j])==(j-length))
			{
				flag=0;
				break;
			}
		}
		if(flag)
		n_queen_driver(queen,size,length+1,p_count);
	}
#endif

//皇后各列也互异，减少循环的次数
#if 1
	if(length==size)
	{
		++*p_count;
		return;
	}
	int i,j;
	int flag;
	for(i=0;i!=size-length;++i)
	{
		flag=1;
		swap(queen+length,queen+length+i);
		for(j=0;j<length;++j)
		{
			if((queen[length]-queen[j])==(length-j)||(queen[length]-queen[j])==(j-length))
			{
				flag=0;
				break;
			}
		}
		if(flag)
		n_queen_driver(queen,size,length+1,p_count);
		swap(queen+length,queen+length+i);
	}
#endif
}
int n_queen(int size)
{
	int queen[size];
	int count=0;
	int i;
	for(i=0;i!=size;++i)
	{
		queen[i]=i;
	}
	n_queen_driver(queen,size,0,&count);
	return count;
}
/*********************************************************************************/
int array_divied(int* arr,int n)
{
	//分成两个n/2的数组，两个数组的和最相近
#if 0
	int sum=0;
	int i,j,k;
	for(i=0;i!=n;++i)
	{
		sum+=arr[i];
	}

	int avg_sum=sum/2;
	int avg_n=n/2;
	//路径
	int path[n+1][avg_n+1][avg_sum+1];

	//tmp_sum[i][j][k],前i个数里面选取j个数的和最逼近k的值
	int tmp_sum[avg_n+1][avg_sum+1];

	for(i=0;i!=avg_sum+1;++i)
		tmp_sum[0][i]=0;

	for(i=1;i!=n+1;++i)
		{
			if(i<avg_n)
				j=i;
			else
				j=avg_n;
			for(;j!=0;--j)
			{
				for(k=0;k<=avg_sum;++k)
				{
					if(k>=arr[i-1])
					{
						if(tmp_sum[j-1][k-arr[i-1]]+arr[i-1]>tmp_sum[j][k])
						{
							tmp_sum[j][k]=tmp_sum[j-1][k-arr[i-1]]+arr[i-1];
							path[i][j][k]=1;
						}
					}
				}
			
			}
		}
	//打印路径
	for(i=n,j=avg_n,k=avg_sum;j!=0;--i)
	{
		if(path[i][j][k]==1)
		{
			printf("%d\t",arr[i-1]);
			--j;
			k-=arr[i-1];
		}
	}
	return tmp_sum[avg_n][avg_sum];
#endif
#if 1
	int sum=0;
	int i,j;
	for(i=0;i!=n;++i)
	{
		sum+=arr[i];
	}

	int avg_sum=sum/2;

	int path[n+1][avg_sum+1];
	int tmp_sum[avg_sum+1];
	for(i=0;i!=avg_sum+1;++i)
		tmp_sum[i]=0;

	for(i=1;i!=n+1;++i)
	{
		for(j=arr[i-1];j<=avg_sum;++j)
		{
			if(tmp_sum[j-arr[i-1]]+arr[i-1]>tmp_sum[j])
			{
				tmp_sum[j]=tmp_sum[j-arr[i-1]]+arr[i-1];
				path[i][j]=1;
			}
		}
	}

/*	for(i=n,j=avg_sum;j!=0;--i)
	{
		if(path[i][j]==1)
		{
			printf("%d\t",arr[i-1]);
			j-=arr[i-1];
		}
	}
	*/
	return tmp_sum[avg_sum];
#endif
}
