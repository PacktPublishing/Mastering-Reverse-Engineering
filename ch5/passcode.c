#include <stdio.h>
#include <string.h>

void main(void)
{
    char pass[1024];
    printf("Enter password: ");
    scanf("%s", pass);
    int x = strlen(pass);
    if (x == 7)
    {
        int checksum = 0;
        for (int i=0; i < x; i++)
        {
            checksum += pass[i];
        }
        if (checksum == 734)    // sample passwords = ballpen, hhhhhhn, Zzz"zzz, zaafaaz, hijxyz8
            printf("Correct password!\n");
            return;
    }
    printf("Incorrect password!\n");
    return;
}
