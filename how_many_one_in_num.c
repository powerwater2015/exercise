/*
 * Description: find out how many 1 in a specified number.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASE_BIT (4)
#define BASE (16)

/*
 * 1000 1000 - 1 = 10000 0111
 * 1000 1000 & 1000 0111 = 1000 0000
 *
 * 1000 0000 - 1 = 0111 1111
 * 0111 1111 & 1000 0000  = 0
 *
 */

/*
int g_tbl[][2] = {
        {0000, 0},
        {0001, 1},
        {0010, 1},
        {0011, 2},
        {0100, 1},
        {0101, 2},
        {0110, 2},
        {0111, 3},
        {1000, 1},
        {1001, 2},
        {1010, 2},
        {1011, 3},
        {1100, 2},
        {1101, 3},
        {1110, 3},
        {1111, 4},
};
*/

int g_tbl[][2] = {
        {0, 0},
        {1, 1},
        {2, 1},
        {3, 2},
        {4, 1},
        {5, 2},
        {6, 2},
        {7, 3},
        {8, 1},
        {9, 2},
        {10, 2},
        {11, 3},
        {12, 2},
        {13, 3},
        {14, 3},
        {15, 4},
};

/* find by search */
int get_re(int num)
{
    int i = 0;
    
    for(i=0; i<sizeof(g_tbl)/(sizeof(int)*2); i++)
    {
        if(num == g_tbl[i][0])
        {
            return g_tbl[i][1];
        }
    }
    
    if (sizeof(g_tbl)/(sizeof(int)*2) == i)
    {
        printf("num(%d) not found!\n", num);
        return -1;
    }
}

/* find by hash */
int get_re_hash(int num)
{
    if (0>num || BASE<=num)
    {
        printf("INVALID input! %d\n", num);
        return -1;
    }
    
    return g_tbl[num][1];
}

/* get 4 bit which is specified by index */
int split(long long num, int index)
{
    long long base = 0xf << (index * BASE_BIT);
    //printf("%d. base = 0x%x\n", index, base);
    
    return ((num&base) >> (index*4));
}

/* solution 1 */
int calc(long long num)
{
    int i = 0;
    int re = 0;
    int item = 0;

    for (i=0; i<sizeof(long long)*8/BASE_BIT; i++)
    {
        item = split(num, i);
        printf("item = 0x%x\n", item);
    
        re += get_re_hash(item);
    }
    
    return (re);
}

/* solution 2 */
/* the lowest BIT 1 will be removed by each loop */
int calc_using_math(long long num)
{
    int cnt = 0;
    while(num)
    {
        num &= num - 1;
        cnt ++;
    }

    return cnt;
}

int main()
{
    srand((unsigned)time(NULL));

    long long num = rand() % 8589934592;  //2^33
    printf("num = %ld\n", num);
    printf("num = 0x%x\n", num);
    
    int re = calc(num);
    //int re = calc_using_math(num);
    printf("re = %d\n", re);
    
    return 0;
}
