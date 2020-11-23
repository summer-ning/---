/******************************************************************************
 *  题目说明：想兑换100元钱，有1,2,5,10四种钱，问总共有多少兑换方法。
    解法：
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int exchangeCoin_recursion(int n)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    return exchangeCoin_recursion(n - 1) + exchangeCoin_recursion(n - 2) 
           + exchangeCoin_recursion(n - 5) + exchangeCoin_recursion(n - 10);
}

int exchangeCoin(int n)
{
    int *dp = (int *)malloc((n+1) * sizeof(int));
    int value;

    if (NULL == dp)
    {
        printf("[%s],line:%d,malloc fail\n",__FUNCTION__,__LINE__);
        return -1;
    }
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i-1] + dp[i-2];
        if (i >= 5)
        {
            dp[i] += dp[i-5];
        }
        if (i >= 10)
        {
            dp [i] += dp[i-10];
        }
    }
    value = dp[n];
    free(dp);
    return value;
}

int main()
{
    int count1,count2;

    count1 = exchangeCoin_recursion(23);
    count2 = exchangeCoin(23);
    if (count1 != count2)
    {
        printf("ERROR!! count1=%d,count2=%d\n",count1,count2);
    }
    return 0;
}