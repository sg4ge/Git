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

int bag_complete(const element* elements,int n,int weight)
{
#if 1
	int max[weight+1];

	//记录路径
	int path[n+1][weight+1];
	int i,j;
	for(i=0;i!=weight+1;++i)
	{
		max[i]=0;
	}
	for(i=1;i!=n+1;++i)
	{
		for(j=1;j!=weight+1;++j)
		{
			if(elements[i-1].weight<=j)
			{
				if(max[j-elements[i-1].weight]+elements[i-1].value>max[j])
				{
					max[j]=max[j-elements[i-1].weight]+elements[i-1].value;

					//表示max[j]使用了第i个物品
					path[i][j]=1;
				}
			}
		}
	}

	
	//打印出背包里具体的东西
	for(i=n,j=weight;i>0;)
	{
		if(path[i][j]==1)
		{
			j-=elements[i-1].weight;
			printf("%d\t",elements[i-1].name);
		}
		else
		{
			--i;
		}	
	}
	puts("");

	return max[weight];
#endif
}




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

//分为两个数组，每个数组的个数不限制，使两个数组之和尽量相等
#if 1
	int sum=0;
	int i,j;
	for(i=0;i!=n;++i)
	{
		sum+=arr[i];
	}

	int avg_sum=sum/2;

	int path[n+1][avg_sum+1];
	//tmp_sum[i][j],前i个元素最逼近j的和
	int tmp_sum[avg_sum+1];
	for(i=0;i!=avg_sum+1;++i)
		tmp_sum[i]=0;

	for(i=1;i!=n+1;++i)
	{
		for(j=avg_sum;j>=arr[i-1];--j)
		{
			if(tmp_sum[j-arr[i-1]]+arr[i-1]>tmp_sum[j])
			{
				tmp_sum[j]=tmp_sum[j-arr[i-1]]+arr[i-1];
				path[i][j]=1;
				//printf("path[%d][%d]\n",i,j);
			}
		}
	}

	for(i=n,j=avg_sum;i!=0;--i)
	{
		if(path[i][j]==1)
		{
			printf("%d\t",arr[i-1]);
			j-=arr[i-1];
		}
	}
	
	return tmp_sum[avg_sum];
#endif
}




//安卓手机总解锁方法数量,穷举法
/**************************************************************
 1   2   3

 4   5   6

 7   8   9，
 * *************************************************************/
#if 1
void android_unlock_total_driver(int* unlock_arr,int len,int this_len,int* count,int* used)
{
	if(this_len==len)
	{
		++*count;
		return;
	}
	int i;
	int flag;
	for(i=this_len;i!=9;++i)
	{
		flag=1;
		swap(&unlock_arr[this_len],&unlock_arr[i]);
		used[unlock_arr[this_len]]=1;
		if(this_len!=0)
		{
			if(1==unlock_arr[this_len-1]&&((3==unlock_arr[this_len]&&0==used[2])||(7==unlock_arr[this_len]&&0==used[4])||(9==unlock_arr[this_len]&&0==used[5])))
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(2==unlock_arr[this_len-1]&&8==unlock_arr[this_len]&&0==used[5])
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(4==unlock_arr[this_len-1]&&6==unlock_arr[this_len]&&0==used[5])
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(7==unlock_arr[this_len-1]&&9==unlock_arr[this_len]&&0==used[8])
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(3==unlock_arr[this_len-1]&&((7==unlock_arr[this_len]&&0==used[5])||(9==unlock_arr[this_len]&&0==used[6])))
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(9==unlock_arr[this_len-1]&&((1==unlock_arr[this_len]&&0==used[5])||(3==unlock_arr[this_len]&&0==used[6])||(7==unlock_arr[this_len]&&0==used[8])))
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(6==unlock_arr[this_len-1]&&4==unlock_arr[this_len]&&0==used[5])
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(8==unlock_arr[this_len-1]&&2==unlock_arr[this_len]&&0==used[5])
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(3==unlock_arr[this_len-1]&&1==unlock_arr[this_len]&&0==used[2])
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
			else if(7==unlock_arr[this_len-1]&&((1==unlock_arr[this_len]&&0==used[4])||(3==unlock_arr[this_len]&&0==used[5])))
			{
				flag=0;
				printf("this_len-1:%d,this_len:%d\n",unlock_arr[this_len-1],unlock_arr[this_len]);
			}
		}
		if(flag)
			android_unlock_total_driver(unlock_arr,len,this_len+1,count,used);
		used[unlock_arr[this_len]]=0;
		swap(&unlock_arr[this_len],&unlock_arr[i]);
	}
}
#endif

int android_unlock_total()
{
	int i,j;
	int count=0;
	int unlock_arr[9];
	int used[10];
	for(i=0;i!=9;++i)
	{
		unlock_arr[i]=i+1;
	}
	for(i=4;i!=10;++i)
	{
		for(j=0;j!=10;++j)
		{
			used[i]=0;
		}
		int tmp=0;
		android_unlock_total_driver(unlock_arr,i,0,&tmp,used);
		count+=tmp;
	}
	return count;
}

