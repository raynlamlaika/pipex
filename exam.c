#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_atoi(char *str)
{
    int i , rs, sign;
    i = 0 ,rs= 0, sign =1;

    while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    while(str[i] == '+' || str[i] == '-')   
    {
        if (str[i] == '-')
        {
            sign = -1;
        }
        i++;
    }
    
    while(str[i] >= 48 && str[i] <= 57)
    {
        rs = (str[i] - 48) + (rs *10);
        i++;
    }
    return((rs*sign));

}



int main(int ac , char **av)
{
    int i = 1;
    if (ac  > 1)
    {
        int j = 0;
        while (av[1][j])
        {
            while (av[1][j] == ' ' && (av[1][j+1])== ' ')
                j++;
            write(1, &av[1][j], 1);
            j++;
        }
    }
    return(write(1, "\n", 1), 0);
}