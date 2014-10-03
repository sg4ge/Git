#ifndef STRING_PROCESS_H
#define STRING_PROCESS_H
#include<string.h>
/*************************************************************
 *************找出src中重复出现的最长子串，放在sub中**********
 * ***********************************************************/
extern void find_longest_repeated_substring(const char* src,char* sub);

/*************************************************************
 *找出src中连续重复出现的最多子串，放在sub中，返回出现次数
 * ***********************************************************/
extern int find_most_repeated_substring(const char*src,char* sub);

/*********************************************************************
 *找出src中和match_str匹配的子字符串，并将其和其后1024个字符放在result_str中*
 * *******************************************************************/
extern void find_matching_string(const char* src,const char* match_str,char* result_str);

/*********************************************************************
 ***********************找出和最大的连续子串**************************
 * *******************************************************************/
extern int find_maxsum_sub(const int* src,int src_len,int* sub,int* p_sub_len);

/*************************************************************
 *打印出src中所有组合的可能性，比如abc，打印出a,b,c,ab,ac,bc,abc
 * ***********************************************************/
extern void print_all_combination(const char* src);
#endif
