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
    int i = 2;
    if (ac == 2)
    {
        int j = 0;
        if (av[1])
        {
            while (av[1][j])
            {
                if (av[1][j != '_'])
                    j++;
            }   
            char *re=  malloc(j);
            if(!re)
                return (0);
            j = 0;
            while(av[1][j])
            {
                if(av[1][j] == _)
                    j++;
                    if(av[1][j] != '_' && (av[1][j] >= && av[1][j] <= ))
                        write();


            }

        }



    }
    write(1, "\n", 1);
}