#include <stdio.h>
#include <string.h>
#include <dirent.h>

struct login
{
    char acc_no[20], pass[20];
} l[2];

int login()
{
    int i = 0;

    printf("Enter acc_no: ");
    scanf("%s", &l[1].acc_no);
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
            fscanf(fp, "%s", l[0].acc_no);
            fscanf(fp, "%s", l[0].pass);

            if (strcmp(l[0].acc_no, l[1].acc_no) == 0 && strcmp(strlwr(l[0].pass), strlwr(l[1].pass)) == 0)
            {
                return i + 1;
            }
            i++;
        }
    }

    closedir(folder);
    return 0;
}