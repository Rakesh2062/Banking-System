#include <stdio.h>
#include <string.h>
#include <dirent.h>

struct login
{
    char username[20], pass[20];
} l[2];

int login()
{
    int i = 0;

    printf("Enter username: ");
    scanf("%s", &l[1].username);
    printf("Enter password: ");
    scanf("%s", &l[1].pass);

    DIR *folder = opendir(".");
    struct dirent *file;
    char files[100][100];

    while (file = readdir(folder))
    {
        if (strstr(file->d_name, ".txt") != NULL)
        {
            FILE *fp;
            fp = fopen(file->d_name, "r");
            if (fp == NULL)
            {
                return 0;
            }
            fscanf(fp, "%s", l[0].username);
            fscanf(fp, "%s", l[0].pass);

            if (strcmp(l[0].username, l[1].username) == 0 && strcmp(l[0].pass, l[1].pass) == 0)
            {
                return i + 1;
            }
            i++;
        }
    }

    closedir(folder);
    return 0;
}