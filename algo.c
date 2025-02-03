#include "stdio.h"


// int main()
// {
//     int i = 0 ;

//     int a;
//     int b;
//     int cc;
//     int o;
//     int h;
//     int uu;
//     uu = 0;
//     scanf("%d", &a);
//     int r[a];
//     while (i < a)
//     {
//         int j = 0;
//         scanf("%d", &b);
//         int arr[b];
//         while(j < b)
//         {
//             for(int k = 0; k < b; k++)
//             {
//                 scanf("%d", &arr[k]);
//             }
//             int rsu[b];
//             o = 0;
//             while(o < b)
//             {
//                 arr[o] += 1;
//                 cc = 1;
//                 int y = 0;
//                 while(y < b)
//                 {
//                     cc *= arr[y];
//                     y++; 
//                 }
//                 rsu[o] = cc;
//                 arr[o] -= 1;
//                 o++;
//             }
//             h = rsu[0];
//             for (int i = 0;i < b;i++)
//             {

//                 if (h < rsu[i])
//                 { 
//                     h = rsu[i];
//                 }
                
//             }
            
//             r[uu] = h;
//             uu++;
//             j++;
//             break;
//         }
//         i++;
//     }
//     int oo = 0;
//     while (a > oo)
//     {
//         printf("%d\n", r[oo]);
//         oo++;
//     }
// }


int main()
{

    int a;
    int firest, sec;
    scanf("%d", &a);
    int i = 0;
    int oper = 0;
    int arr[a];
    int flag;
    while (i < a)
    {
        scanf("%d, %d", &firest, &sec);
        if (firest == sec)
        {
            arr[i] = 0;
        }
        while (firest != sec)
        {
            flag += 1;
            if(firest % 2 == 0)
                firest = firest - (sec + firest);
            if(firest % 2 == 1)
                firest = firest - (sec - firest) + 1;
        }
        arr[i] = flag;
        i++;
    }
    i = 0;
    while(i < a)
    {
        printf("%d\n",arr[i]);
        i++;
    }







}


