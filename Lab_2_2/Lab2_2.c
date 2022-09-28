#include<stdio.h>
main()
{
    int  count = 0, R = 100;
    for (int a = 0; a <= 2; a++)
    {
        for (int b = 0; b <= 5; b++)
        {
            for (int c = 0; c <= 20; c++)
            {
                for (int d = 0; d <= 50; d++)
                {
                    if (R == (a * 50 + b * 20 + c * 5 + d * 2))
                    {
                        count++;
                    }

                }
            }
        }
    }
    printf("Result = %d", count);
    return 0;
}