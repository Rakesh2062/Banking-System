#include <stdio.h>
#include <string.h>
#include "login.c"
#include "admin.c"
#include "user.c"

int main()
{
    printf("------------- Welcome to XYZ Banking System -------------\n");
    int ans;
    ans = login();

    switch (ans)
    {
    case 0:
        printf("Entered account number and password doesnot match. Please try again\n");
        main();
        break;
    case 1:
        admin();
        break;
    default:
        user();
    }

    return 0;
}