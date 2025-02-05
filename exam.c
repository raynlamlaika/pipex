#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

void pustr(char*str)
{
    while (*str)
    {
        write (1 ,*str, 1);
        str++;
    }
}

int ft_strlen(char*str)
{
    int i = 0 ;
    while (str[i])
        i++;
    return (i);
}

void	print_bits(unsigned char octet)
{
	int				idx;
	unsigned char	bit;

	idx = 8;
	while (idx--)
	{
		bit = ((octet >> idx & 1) + '0');
		write(1, &bit, 1);
	}
}

int main(int ac, char**av)
{
    int i = 0;
    if (ac == 2)
    {
        int len = ft_strlen (av[1]);
        int len2 = ft_strlen (av[1]);

        while (len)
        {
            if (len != ' ')
                len--;
        }



    }
}



