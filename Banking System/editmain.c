#include <stdio.h>
#include <string.h>
#include "editedlogin.c"
#include "admin.c"
#include "cpuser.c"

int main()
{
    printf("------------- Welcome to XYZ Banking System -------------\n");
    int ans;
    ans = editedlogin();

    switch (ans)
    {
    case 0:
    printf("Entered username and password doesnot match. Please try again\n");
    main();
         
        break;
    case 1:
        admin();
        break;
  
    default:
        user();
        break;
    }

    return 0;
}