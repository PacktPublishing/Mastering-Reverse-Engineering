#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void badpass()
{
	printf("\nwrong password. try again!\n");
}

void goodpass()
{
	printf("\ncorrect password. bye!\n");
}


int main(int argc, char *argv[])
{
	//pass = "Audere est Facere"
	// e @ 3,5,7,14,16
	// space @ 6, 10
	// ere @ 3, 14
	// Aud @ 0
	// Fac @ 11
	// st @ 8
	char password[31];  // = "Audere est Facere";
	unsigned int x;
    int e[] = { 3,5,7,14,16 };
	int esize;
	int i;
	
	printf("what is the password? ");
	scanf("%30[0-9a-zA-Z ]", &password);
	if (strlen(password) == 17)
	{
		esize = sizeof(e) / sizeof(e[0]);
		for (i = esize; i > 0; i--)
		{
			if (password[e[i - 1]] != 'e')
			{
				badpass();
				return 0;
			}
		}
		x = *((unsigned int*)(password + 3)) & *((unsigned int*)(password + 14));
		x &= 0x0ffffff;
		if (0 == strcmp((char*)&x, "ere"))
		{
			if (0 == (password[6] ^ password[10]))
			{
				if (0x40 == (password[6] + password[10]))
				{
					if ((*((unsigned int*)password) & ~(0xff << 24)) == 'duA')
					{
						if ((*((unsigned int*)(password + 11)) & ~(0xff << 24)) == 'caF')
						{
							if ((*((unsigned int*)(password + 8)) & ~(0xffff << 16)) == 'ts')
							{
								goodpass();
								return 0;
							}
						}
					}
				}
			}
		}
	}
	badpass();
	return 0;
}
