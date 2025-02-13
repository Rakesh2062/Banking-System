#include <stdio.h>
#include <string.h>  // for using string functions
#include <dirent.h>  // for manipulating directories

// Directory means Folders so whenever I say directories understand it as folder
// Below structure is used for storing array (2) data for account number and password. The first i.e. l[0] will store the username and password from the file and l[1] will store the username and password provided by the user.

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

    DIR *folder = opendir(".");  // For opening current directory i.e. Banking System 
    struct dirent *file; // it opens all the files in the current directory (for us admin.c, admin.txt..... and so on)

    while (file = readdir(folder))    // it simply opens the files one by one till there exists file in the directory
    {
        // The struct dirent *file has in-built "d_name" structure variable which stores the name of the files
        if (strstr(file->d_name, ".txt") != NULL)    // file->d_name means the name of file and strstr() checks the first d_name has either .txt in its name or not and if there is .txt then it opens or it will give NULL and go out of if statement. Also we are only taking .txt files because the date (acc_no, password, username, amount) are stored in .txt files and .c and .exe files are useless for us.
        {
            FILE *fp; // Opening file
            fp = fopen(file->d_name, "r");   // opening file which has name as file->d_name with read mode.
            if (fp == NULL)  // file doesnot open then we will return 0.
            {
                return 0;
            }
            fscanf(fp, "%s", l[0].acc_no); // it stores the first line in the files (for us the first line is account number) into l[0].acc_no
            fscanf(fp, "%s", l[0].pass); // when we use again fscanf() then, as it has already read the first line now it will read second line (if we again use fscanf() below this then it will read third line) which has password stored in it and stores it in l[0].pass

            if (strcmp(l[0].acc_no, l[1].acc_no) == 0 && strcmp(l[0].pass, l[1].pass) == 0)  
            // we are simply comparing the account number given by user(l[1].acc_no) with already stored in file(l[0].acc_no). Also, we are comparing the password given by user (l[1].pass) with already stored in file (l[0].pass). And if the both matches then only it will identify as a user or it will be login error.
            {
                return i + 1; 
                // it will return i+1 (i.e. 0+1=1) to the calling function. Note: It will only return 1 for the first time but it will return higher than 1 as the loop will continue.
            }
            i++; // we will inc. the value of i by 1 and now the value of i will 1.
        }
    }

    closedir(folder); // as we have opened the directory we are closing it also.
    return 0; // if neither of the above code runs then it will return 0. 
    // By the way, above code will not run if the file is empty.
}
