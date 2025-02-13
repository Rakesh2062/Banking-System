#include <stdio.h>
#include <dirent.h>
#include <stdlib.h> // For system()

struct user
{
    int acc_no;
    char username[100], password[32];
    float balance;
} initial_user, transfering_user;

void account_details(struct user *);
void adding_balance(struct user *);
void withdraw_balance(struct user *);
void transfer_balance(struct user *, struct user *);
void user();

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void main()
{
    user();
}

void user()
{
    FILE *fptr;
    int choice;

    fptr = fopen("file location of logged in user", "rb"); // Reminder that this line needs editing later
    if (fptr == NULL)
    {
        perror("Error opening file");
        return;
    }
    fread(&initial_user, sizeof(initial_user), 1, fptr);
    fclose(fptr);

    clear_screen(); 

    printf("\t \t Welcome %s \n", initial_user.username);

label:
    printf("Press 1 to view your account details\n");
    printf("Press 2 to view your deposit amount to your account\n");
    printf("Press 3 to view your withdraw amount from your account\n");
    printf("Press 4 to view your transfer sum to another account\n");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n')
        {
            // its an empty loop to remove the characters from the buffer
        }; // Clear the input buffer
        goto label;
    }

    switch (choice)
    {
    case 1:
        account_details(&initial_user);
        break;
    case 2:
        adding_balance(&initial_user);
        break;
    case 3:
        withdraw_balance(&initial_user);
        break;
    case 4:
        transfer_balance(&initial_user, &transfering_user);
        break;
    default:
        printf("Please enter a valid choice\n");
        goto label;
        break;
    }
}

void account_details(struct user *p)
{
    clear_screen(); 

    printf("Your account details are:\n");
    printf("Account Number\t:\t %d\n", p->acc_no);
    printf("Username\t:\t %s\n", p->username);
    printf("Password\t:\t %s\n", p->password);
    printf("Balance\t:\t %f\n", p->balance);
}

void adding_balance(struct user *p)
{
    clear_screen(); 

    FILE *fptr, *fptrTemp;
    float deposit_amt;

    printf("Enter the amount you want to deposit:\t");
    if (scanf("%f", &deposit_amt) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    p->balance = p->balance + deposit_amt;

    printf("\nBalance is updated successfully\n");
    printf("\nYour new balance is:\t %.3f\n", p->balance);

    fptr = fopen("file location of logged in user", "rb"); // Reminder that this line needs editing later
    if (fptr == NULL)
    {
        perror("Error opening file"); // Error message uses errno to get error code and prints the error message
        return;
    }
    fptrTemp = fopen("temp.txt", "wb");
    if (fptrTemp == NULL)
    {
        perror("Error opening temp file"); 
        fclose(fptr);
        return;  /*exits the function early due to error*/
    }

    fwrite(p, sizeof(*p), 1, fptrTemp);

    fclose(fptr);
    fclose(fptrTemp);

    remove("000001.txt");
    rename("temp.txt", pointer_to_file_location_of_logged_in_user); // Reminder that this line needs editing later
}

void withdraw_balance(struct user *p)
{
    clear_screen(); 

    FILE *fptr, *fptrTemp;
    float withdraw_amt;

label_2:
    printf("Enter the amount you want to withdraw:\t");
    if (scanf("%f", &withdraw_amt) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    if (withdraw_amt > p->balance)
    {
        printf("\nYou cannot withdraw more than you have\n");
        printf("\nYour current balance is : \t%.3f\n", p->balance);
        goto label_2;
    }

    p->balance = p->balance - withdraw_amt;

    fptr = fopen("file location of logged in user", "rb"); // Reminder that this line needs editing later
    if (fptr == NULL)
    {
        perror("Error opening file");
        return;
    }
    fptrTemp = fopen("temp.txt", "wb");
    if (fptrTemp == NULL)
    {
        perror("Error opening temp file");
        fclose(fptr);
        return;
    }

    fwrite(p, sizeof(*p), 1, fptrTemp);

    printf("\nAmount withdrawn successfully from account.\n\n");
    printf("Your new balance is : \t%.3f\n", p->balance);

    fclose(fptr);
    fclose(fptrTemp);

    remove("file location of logged in user"); // Reminder that this line needs editing later
    rename("temp.txt", pointer to file location of logged in user); // Reminder that this line needs editing later
}

void transfer_balance(struct user *p, struct user *pt)
{
    clear_screen(); 

    FILE *fptr, *fptrTransfer, *fptrTemp, *fptrTemp2;
    float transfer_amt;
    int transfer_acc_no;

label_3:
    printf("Enter the amount you want to transfer:\t");
    if (scanf("%f", &transfer_amt) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    if (transfer_amt > p->balance)
    {
        printf("\nCannot transfer amount more than present in your account\n");
        goto label_3;
    }

    printf("Enter the account number you want to transfer the sum to:\t\n");
    if (scanf("%d", &transfer_acc_no) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    fptr = fopen("file location of logged in user", "rb"); // Reminder that this line needs editing later
    if (fptr == NULL)
    {
        perror("Error opening file");
        return;
    }
    fptrTransfer = fopen("file location of transferring user", "rb"); // Reminder that this line needs editing later
    if (fptrTransfer == NULL)
    {
        perror("Error opening transfer file");
        fclose(fptr);
        return;
    }

    fread(pt, sizeof(*pt), 1, fptrTransfer);

    p->balance = p->balance - transfer_amt;
    pt->balance = pt->balance + transfer_amt;

    printf("Amount transferred successfully from account.\n\n");

    printf("Your new balance is:\t%.3f\n", p->balance);

    fptrTemp = fopen("temp.txt", "wb");
    if (fptrTemp == NULL)
    {
        perror("Error opening temp file");
        fclose(fptr);
        fclose(fptrTransfer);
        return;
    }
    fptrTemp2 = fopen("temp2.txt", "wb");
    if (fptrTemp2 == NULL)
    {
        perror("Error opening temp2 file");
        fclose(fptr);
        fclose(fptrTransfer);
        fclose(fptrTemp);
        return;
    }

    fwrite(p, sizeof(*p), 1, fptrTemp);
    fwrite(pt, sizeof(*pt), 1, fptrTemp2);

    fclose(fptr);
    fclose(fptrTransfer);
    fclose(fptrTemp);
    fclose(fptrTemp2);

    remove("file location of logged in user"); // Reminder that this line needs editing later
    remove("file location of transferring user"); // Reminder that this line needs editing later

    rename("temp.txt", pointer to file location of logged in user); // Reminder that this line needs editing later
    rename("temp2.txt", pointer to file location of transferring user); // Reminder that this line needs editing later
}
