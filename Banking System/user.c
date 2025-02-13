#include <stdio.h>
/* Not sure if should create structure here or inisde void user :')*/
struct user
{

    int acc_no;
    
    char username[100],password[32];
    
    float balance;

}initial_user, transfering_user;  // Here i created two because while transfer the sum i'll need two structure

void account_details(struct user *);

void adding_balnce(struct user *);

void withdraw_balance(struct user *);

void transfer_balance(struct user *, struct user *);

void main()
{

    user();

}

void user()
{
    
    FILE *fptr,*fptrTemp;
    
    int choice;
    
    fptr = fopen("filelocation of logged in user","rb");  // Reminder that this line needs editing later
    
    fread(&initial_user,sizeof(initial_user),1,fptr);

    clrscr();

    printf("\t \t Welcome %s \n",initial_user.username);
    
    label:

    printf("Press 1 to view your account details\n");
    
    printf("Press 2 to view your deposit amount to your account\n");
    
    printf("Press 3 to view your withdraw amount from your account\n");
    
    printf("Press 4 to view your transfer sum to another account\n");
    
    scanf("%d",&choice);
    
    switch(choice)
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
    
            transfer_balance(&initial_user,&transfering_user);
        
            break;
        
        default:
    
            printf("Please enter a valid choice");
        
            goto label;
        
            break;  
    }

}

void account_details(struct user *p)
{
    // Done in assumption that pointers work " no way to check :( ", if they don't will edit later

    clrscr();

    printf("Your account details are:\n");

    printf("Account Number\t:\t %d\n",p->acc_no);

    printf("Username\t:\t %s\n",p->username);

    printf("Password\t:\t %s\n",p->password);

    printf("Balance\t:\t %f\n",p->balance);

}

void adding_balance(struct user *p)
{
    clrscr();

    float deposit_amt;   // Dont know why deposit_amt is not being read as a float variable

    printf("Enter the amount you want to deposit:\t");

    scanf("%f",&deposit_amt);
    
    p->balance = p->balance + deposit_amt;

    printf("\nBalance is updated successfully\n");
    
    printf("Your new balance is:\t %f",p->balance);

    fptrTemp = fopen("temp.txt","wb");  // update the temp.txt file location to the exact directory where other files are stored


    fwrite(p,sizeof(p),1,fptrTemp);

    fclose(fptr);

    fclose(fptrTemp);

    remove(fptr);

    rename("temp.txt",ptr);  // here ptr is a pointer that needs to be created in the main file 
                            // of the logged in user 
}
// here in the last part of the perivious block what i did is that after adding the sum i created another file temp.txt
// where i stored the update info i.e the balance and the i delted the existing file of the user and then renamed the 
// temp.txt file as the same name as that of previous file 

void withdraw_balance(struct user *p)
{

    clrscr();

    float withdraw_amt;

    label_2:

    printf("Enter the amount you want to withdraw:\t");

    scanf("%f",&withdraw_amt);

    if(withdraw_amt > p->balance)
    {
        printf("\nYou cannot withdraw more than you have\n");

        printf("Your current balance is : \t",p->balance); //shown so that they can enter the exact amount if they want to withdrwa all money

        goto label_2;  // should i add option where the user gets to choose whether to withdraw all balance??

    }

    p->balance = p->balance - withdraw_amt;

    fptrTemp = fopen("temp.txt","wb");  // update the temp.txt file location to the exact directory where other files are stored

    fwrite(p,sizeof(p),1,fptrTemp);

    printf("\nAmount wihtdrawed successfully from account.\n");

    printf("Your new balance is : \t",p->balance);

    fclose(fptr);

    fclose(fptrTemp);

    remove(fptr);

    rename("temp.txt",ptr);   // later update temp.txt location in deposit block as well

}

void transfer_balance(struct user *p, struct user *pt)
{

    clrscr();

    FILE *fptrTransfer, *fptrtemp2;   /* Create pointer for opening ampont to be transfered user file
                                            and for temporary file for it*/

    float transfer_amt, transfer_acc_no;

    label_3:

    printf("Enter the amount you want to transfer:\t");

    scanf("%f",&transfer_amt);

    if(transfer_amt > p->balance)
    {
        printf("\nCannot transfer amount more than present in your account\n");

        goto label_3;
    
    }

    printf("Enter the account number you want to transfer the sum to:\t\n");

    scanf("%f",&transfer_acc_no);

    /*check if transfer account no exists or not and display error message or run accordingly 
    I know here we have use dirent to go to files directory and then search all the files present
    in the directory but i wont go there for now let admin be complete then we i'll see what can be done*/ 

    // Proceding assuming transfer account exists

    fptrTransfer = fopen("transfer_file_location","rb");  /* Update the file location later*/

    fread(pt,sizeof(pt),1,fptrTransfer);

    p->balance = p->balance - transfer_amt;

    pt->balance = pt->balance + transfer_amt;

    printf("Your new balance is:\t",p->balance);
    
    fptrTemp = fopen("temp.txt","wb");   /* Update temp.txt  and temp2.txt file name later */

    fptrTemp2 = fopen("temp2.txt","wb");

    fwrite(p,sizeof(p),1,fptrTemp);

    fwrite(pt,sizeof(pt),1,fptrTemp2);

    fclose(fptr);

    fclose(fptrTransfer);

    fclose(fptrTemp);

    fclose(fptrTemp2);

    remove(fptr);

    remove(fptrTransfer);

    rename("temp.txt",ptr);  /* update temp.txt file name later*/

    rename("temp2.txt",ptr2);  /* ptr2 is pointer that points to user in whose account amount is being transfered
                                   file name */

}

