/******************************************************************************
 *  题目说明：一个数组中只有两个数字是出现一次， 其他所有数字都出现了两次。 找出这两个
 *           只出现一次的数字，编程实现。
    解法：1.对所有的数异或。因为有两个数不用，所以结果肯定不为0
         2. 按位查找这个数，找到第一个位为1的位置pos
         3. 根据pos位把数组分成两个数组，array0和array1,array0表示元素的pos位为0bit,
            array1表示元素的pos位为1bit。对array0和array1分别异或就得到两个只出现一次
            的数。
            因为这个数组异或，pos位不为0，说明这两个只出现一次的数在pos位不同，所有array0
            中只包含一个只出现一次的数，对array0异或求出这个数，同理，……
******************************************************************************/
#include <stdio.h>

void findTwoNumber(int a[], int len, int *num1, int *num2)
{
    int result = 0;
    int i,pos;

    for (i = 0; i < len; i++)
    {
        result ^= a[i];
    }
    if (result == 0)
    {
        printf("input array error\n");
        return;
    }
    for (i = 0; i < sizeof(int); i++)
    {
        if (result & (0x01 << i))
            break;
    }
    pos = i;

    *num1 = 0;
    *num2 = 0;
    for (i = 0; i < len; i++)
    {
        if (a[i] & (0x01 << pos))
        {
            *num1 ^= a[i];
        }
        else
        {
            *num2 ^= a[i];
        }
        
    }
}

int main()
{
    int tst[] = {1,2,3,4,5,9,6,6,7,1,2,3,4,5};
    int num1, num2;

    findTwoNumber(tst,sizeof(tst)/sizeof(tst[0]), &num1, &num2);
    printf("two number:%d,%d\n",num1,num2);
    return 0;
}