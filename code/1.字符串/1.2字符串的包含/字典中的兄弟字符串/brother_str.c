/******************************************************************************
 *  题目说明：如果两个字符串中的字符一样，出现次数也一样，只是出现的顺序不一样，则认为
              这两个字符串是兄弟字符串。例如 "abc" 和 "acb"是兄弟字符串。提供一个字符
              串在字典中找到他的兄弟字符串
    解法：假设字典放在文件dictionary.txt中，每个单词占一行且每个单词都是小写字母。
         我们创建一种对单词的标识，使得兄弟字符串的标识相同，标识方法为对单词中的字母排序
         例如 "mississippi"可以标识为 iiiimppssss，进一步可以记作i4mp2s4(省略了1的计数)，
         把添加了标识的单词放在文件dictionary_mark.txt文件中，然后以标识为关键字排序，查找
         时使用二分法排序，排序后的保存到dictionary_flag_sort.txt中。以上步骤只要做一次，
         查找兄弟字符串的时候直接查找dictionary_mark_sort.txt
         此方法参考《编程珠玑》2.4-2.8章节
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define   FILE_DICTIONARY              ".\\dictionary.txt"
#define   FILE_DICTIONARY_MARK         ".\\dictionary_mark.txt"
#define   FILE_DICTIONARY_MARK_SORT    ".\\dictionary_mark_sort.txt"
#define   FILE_TEMPORY                 ".\\tempory.txt"
#define   WORD_MAX_LEN      (30)
#define   WORD_MAX_NUMBER   (100)  // 

int charcmp(char *x, char *y)
{
    return *x - *y;
}

int stringcmp(char *x, char *y)
{
    return strcmp(x,y);
}

// 获取单词标识缩写
void GetSigAbbrevition(char *word, char *sig_abbreviation)
{
    int i, j,count = 1;
    char sig[WORD_MAX_LEN];

    strcpy(sig,word);
    // 按字母排序
    qsort(sig, strlen(sig),sizeof(char),charcmp);
    //printf("%s %s\n",sig, word);
    // 简写成字母+计数
    for (i = 0, j = 0; i < strlen(sig); i++)
    {
        if (sig[i] == sig[i+1])
        {
            count++;
        }
        else
        {
            sig_abbreviation[j++] = sig[i];
            if (count != 1)
            {
                sig_abbreviation[j++] = '0' + count;
                count = 1;
            }
        }
    }
    sig_abbreviation[j] = '\0';
}

void FileStringSort(FILE *fd, FILE *new_fd)
{
    int i = 0,j,k;
    /*
       实际英文单词有17万-100万个，如果对文件里的单词排序，由于内存的限制可能一
       次无法读出文件里的所有单词，排序比较麻烦，这里我假设字典里的单词不超过
       WORD_MAX_NUMBER个，这样一次能够全部读完
      */
    char word[WORD_MAX_NUMBER][WORD_MAX_LEN]; 
    char sig_abbreviation[WORD_MAX_NUMBER][WORD_MAX_LEN]; 
    char temp[WORD_MAX_LEN];
    int len = 0;

    // 读出所有的单词
    fseek(fd,0,SEEK_SET);
    while(fscanf(fd,"%s %s", sig_abbreviation[i],word[i]) != EOF)
    {
        //printf("%s %s\n",sig_abbreviation[i],word[i]);
        i++;
    }
    len = i;
    // 冒泡排序
    for (j = 0; j < len; j++)
    {
        for (k = 0; k < len-j-1; k++)
        {
            if (strcmp(sig_abbreviation[k],sig_abbreviation[k+1]) > 0)
            {
                strcpy(temp,sig_abbreviation[k]);
                strcpy(sig_abbreviation[k],sig_abbreviation[k+1]);
                strcpy(sig_abbreviation[k+1],temp);

                strcpy(temp,word[k]);
                strcpy(word[k],word[k+1]);
                strcpy(word[k+1],temp);
            }
        }
    }
    for (i = 0; i < len; i++)
    {
        fprintf(new_fd, "%s %s\n",sig_abbreviation[i],word[i]);
    }
}

void MarkAndSortDictionary(FILE *fd,FILE *new_fd)
{
    char word[WORD_MAX_LEN], sig_abbreviation[WORD_MAX_LEN];
    FILE *tem_fd;

    tem_fd = fopen(FILE_TEMPORY, "w+"); // 临时的中间文件
    // 读字典中的单词
    while(fgets(word,WORD_MAX_LEN,fd) != NULL) // fgets函数如果督导文件结尾会返回NULL
    {
        if (word[strlen(word)-1] == '\n')
        {
            word[strlen(word)-1] = '\0';
        }
        GetSigAbbrevition(word,sig_abbreviation);
        //printf("%s %s %s\n",sig,sig_abbreviation,word);
        fprintf(tem_fd,"%s %s\n", sig_abbreviation, word);
    }
    FileStringSort(tem_fd,new_fd);  // 对文件里的单词排序
    // 删除临时文件
    fclose(tem_fd);
    remove(FILE_TEMPORY);
}

void PrintBrotherString(char *str, char words[][WORD_MAX_LEN], 
                        char sig_abbreviation[][WORD_MAX_LEN],int len)
{
    int low = 0, high = len, mid,i;
    char sig_str[WORD_MAX_LEN];
    // 获取str的标识
    GetSigAbbrevition(str,sig_str);
    printf("abbreviation:%s\n",sig_str);
    // 二分查找
    while(low < high)
    {
        mid = (low + high) / 2;
        if (strcmp(sig_str,sig_abbreviation[mid]) < 0)
            high = mid-1;
        else if (strcmp(sig_str,sig_abbreviation[mid]) > 0)
            low = mid+1;
        else
            break;
    }
    if (low < high)  // 存在兄弟字符串
    {
        printf("brother string: \n");
        printf("\t%s\n",words[mid]);
        // 兄弟字符串在mid附近
        i = mid;
        while ((--i) > 0)
        {
            if (strcmp(sig_str,sig_abbreviation[i]) == 0)
                printf("\t%s\n",words[i]);
            else
                break;
        }
        i = mid;
        while ((++i) < len)
        {
            if (strcmp(sig_str,sig_abbreviation[i]) == 0)
                printf("\t%s\n",words[i]);
            else
                break;
        }
    }
    else
    {
        printf("no brothere string\n");
    }
}

int main()
{
    FILE *fd, *new_fd;
    char word[WORD_MAX_LEN];
    char words[WORD_MAX_NUMBER][WORD_MAX_LEN]; 
    char sig_abbreviation[WORD_MAX_NUMBER][WORD_MAX_LEN]; 
    char sig_str[WORD_MAX_LEN];
    int len = 0, i = 0;

    if ((fd = fopen(FILE_DICTIONARY,"r")) == NULL)
    {
        printf("open file [%s] fail\n",FILE_DICTIONARY);
        return -1;
    }
    if ((new_fd = fopen(FILE_DICTIONARY_MARK_SORT,"w+")) == NULL)
    {
        printf("open file [%s] fail\n",FILE_DICTIONARY_MARK_SORT);
        return -1;
    }
    MarkAndSortDictionary(fd, new_fd);

    // 读出所有的单词和标识
    fseek(new_fd,0,SEEK_SET);
    while(fscanf(new_fd,"%s %s", sig_abbreviation[i],words[i]) != EOF)
    {
        //printf("word:%s abbreviation:%s\n",words[i],sig_abbreviation[i]);
        i++;
    }
    len = i;

    while(1)
    {
        printf("Input a word: ");
        gets(word);
        if (strlen(word) == 0)
            break;
        PrintBrotherString(word, words, sig_abbreviation,len);
    }

    return 0;
}