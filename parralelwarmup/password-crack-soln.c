#include <stdio.h>
#include "sha-256.h"

static void hash_to_string(char string[65], const uint8_t hash[32])
{
    size_t i;
    for (i = 0; i < 32; i++)
    {
        string += sprintf(string, "%02x", hash[i]);
    }
}

static void crack(char hash_hex_str[65])
{
    char test_password[9];
    uint8_t hash[32];
    char test_hash_str[65];
    #pragma omp parallel for private(test_password, hash, test_hash_str)
    for(int password_nr = 0; password_nr <= 99999999; password_nr++) {
        snprintf(test_password, 9, "%08d", password_nr);
        calc_sha_256(hash, test_password, 8);
        hash_to_string(test_hash_str, hash);
        if(!strncmp(hash_hex_str, test_hash_str, 64)) {
            printf("Password: %s\n", test_password);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: password-crack.exe hash password or password-crack.exe crack hash\n");
        return -1;
    }
    if (strncmp(argv[1], "hash", 4) == 0)
    {
        // Calculate Hash from argv[2] (2nd argument to program),
        // convert to Hex-String and print to standard output
        // Check if passwort is exactly 8 digits
        if (strlen(argv[2]) != 8)
        {
            printf("Password must be 8 digits.\n");
            return -1;
        }
        for (int i = 0; i < 8; i++)
        {
            if ((argv[2][i] < '0') || (argv[2][i] > '9'))
            {
                printf("Password must be 8 digits.\n");
                return -1;
            }
        }

        uint8_t hash[32];
        calc_sha_256(hash, argv[2], strlen(argv[2]));
        char hash_string[65];
        hash_to_string(hash_string, hash);
        printf("%s\n", hash_string);
    }
    else if (strncmp(argv[1], "crack", 4) == 0)
    {
        char hash_string[65];
        if (strlen(argv[2]) != 64)
        {
            printf("%i\n", strlen(argv[2]));
            printf("Hash must have length 64 and only 0-9a-f\n");
            return -1;
        }
        else
        {
            for (int i = 0; i < 64; i++)
            {
                if (!((argv[2][i] >= '0') && (argv[2][i] <= '9')) &&
                    !((argv[2][i] >= 'a') && (argv[2][i] <= 'f')))
                {
                    printf("Hash must have length 64 and only 0-9a-f (pos %i, char %c)\n", i, argv[2][i]);
                    return -1;
                }
            }
            strncpy(hash_string, argv[2], 64);
            hash_string[64] = '\0';

            crack(hash_string);
        }
    }
    else
    {
        printf("Usage: password-crack.exe hash password or password-crack.exe crack hash\n");
        return -2;
    }
    return 0;
}