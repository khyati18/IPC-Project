#include <stdio.h>
#include <ctype.h>

#include "commonHelpers.h"
#include "account.h"

void getAccount(struct Account* account, int max_acc_no)
{
    printf("New Account Data (Account#:%d)\n", max_acc_no+1);
    printf("----------------------------------------\n");
    account->AccNumber = max_acc_no+1;
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->AccType = getCharOption("AC");
}

void getUserLogin(struct UserLogin* login)
{
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter user login (10 chars max): ");
    getCString(login->LoginName, 1, 10);

    int flag = 1;
    while(flag)
    {
    	int cntspace=0;
	    for (int i = 0; login->LoginName[i]!='\0' ; ++i)
	    {
	    	if(login->LoginName[i]==' ')
	    	{
	    		cntspace++;
	    	}
	    }
	    if(cntspace==0)
	    {
	    	flag=0;
	    }
	    else
	    {
	    	printf("ERROR: The user login must NOT contain whitespace characters.\n");
	    	printf("Enter user login (10 chars max): ");
    		getCString(login->LoginName, 1, 10);
	    }
	}
    printf("Enter the display name (30 chars max): ");
    getCString(login->Name, 1, 30);
    printf("Enter the password (must be 8 chars in length): ");
    getCString(login->Password, 8, 8);

    int fl=1;
    while(fl)
    {
    	int dgt=0, upp=0, lwr=0, symb=0;
	    for (int i = 0; login->Password[i]!='\0' ; ++i)
	    {
	    	if(isdigit(login->Password[i]))
	    	{
	    		dgt++;
	    	}
	    	if(isupper(login->Password[i]))
	    	{
	    		upp++;
	    	}
	    	if(islower(login->Password[i]))
	    	{
	    		lwr++;
	    	}
	    	if(login->Password[i]=='!' || login->Password[i]=='@' || login->Password[i]=='#' || login->Password[i]=='$' || login->Password[i]=='%' || login->Password[i]=='^' || login->Password[i]=='&' || login->Password[i]=='*')
	    	{
	    		symb++;
	    	}
	    }
	    if(dgt==2 && upp==2 && lwr==2 && symb==2)
	    {
	    	fl=0;
	    }
	    else
	    {
	    	printf("SECURITY: Password must contain 2 of each:\nDigit: 0-9\nUPPERCASE character\nlowercase character\nsymbol character: !@#$%%^&*");
	    	printf("\nEnter the password (must be 8 chars in length): ");
    		getCString(login->Password, 8, 8);
	    }
    }
}

void getDemographic(struct Demographic* demo)
{
    printf("Demographic Data Input\n");
    printf("----------------------------------------\n");
    int CurrentYear = currentYear();
    printf("Enter birth year (current age must be between 18 and 110): ");
    demo->BirthYear = getIntFromRange(CurrentYear-110, CurrentYear-18);
    printf("Enter the household Income: $");
    demo->HouseholdIncome = getPositiveDouble();
    printf("Enter the country (30 chars max.): ");

    char s[31];
    getCString(s, 0, 30);

    // convert to uppercase
    for (int i = 0; s[i]!='\0'; i++) {
      if(s[i] >= 'a' && s[i] <= 'z') {
         s[i] = s[i] -32;
      }
   	}

   	for (int i = 0; s[i]!='\0'; i++)
   	{
   		demo->Country[i] = s[i];
   	}
}

void updateAccount(struct Account* account)
{
    int option;
    do{
        printf("Account: %05d - Update Options\n", account->AccNumber);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n", account->AccType);
        printf("2) Login\n");
        printf("3) Demographics\n");
        printf("0) Done\n");
        printf("Selection: ");
        option = getIntFromRange(0, 3);
        printf("\n");

        if(option==1)
        {
            printf("Enter the account type (A=Agent | C=Customer): ");
            char choice = getCharOption("AC");
            printf("\n");
            account->AccType = choice;
        }

        if(option==2)
        {
            updateUserLogin(&account->UsrLog);
        }
        
        if(option==3)
        {
            updateDemographic(&account->Demo);
        }

    }while(option!=0);
}

void updateUserLogin(struct UserLogin* login)
{
    int option;
    do{
        printf("User Login: %s - Update Options\n", login->LoginName);
        printf("----------------------------------------\n");
        printf("1) Display name (current value: %s)\n", login->Name);
        printf("2) Password\n");
        printf("0) Done\n");
        printf("Selection: ");
        option = getIntFromRange(0, 2);
        printf("\n");

        if(option==1)
        {
            printf("Enter the display name (30 chars max): ");
            getCString(login->Name, 1, 30);
            printf("\n");
        }

        if(option==2)
        {
            printf("Enter the password (must be 8 chars in length): ");
            getCString(login->Password, 8, 8);
            printf("\n");

             int fl=1;
		    while(fl)
		    {
		    	int dgt=0, upp=0, lwr=0, symb=0;
			    for (int i = 0; login->Password[i]!='\0' ; ++i)
			    {
			    	if(isdigit(login->Password[i]))
			    	{
			    		dgt++;
			    	}
			    	if(isupper(login->Password[i]))
			    	{
			    		upp++;
			    	}
			    	if(islower(login->Password[i]))
			    	{
			    		lwr++;
			    	}
			    	if(login->Password[i]=='!' || login->Password[i]=='@' || login->Password[i]=='#' || login->Password[i]=='$' || login->Password[i]=='%' || login->Password[i]=='^' || login->Password[i]=='&' || login->Password[i]=='*')
			    	{
			    		symb++;
			    	}
			    }
			    if(dgt==2 && upp==2 && lwr==2 && symb==2)
			    {
			    	fl=0;
			    }
			    else
			    {
			    	printf("SECURITY: Password must contain 2 of each:\nDigit: 0-9\nUPPERCASE character\nlowercase character\nsymbol character: !@#$%%^&*");
			    	printf("\nEnter the password (must be 8 chars in length): ");
		    		getCString(login->Password, 8, 8);
			    }
		    }
        }

    }while(option!=0);
}

void updateDemographic(struct Demographic* demo)
{
        int option;
    do{ 
        printf("Demographic Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Household Income (current value: $%.2lf)\n", demo->HouseholdIncome);
        printf("2) Country (current value: %s)\n", demo->Country);
        printf("0) Done\n");
        printf("Selection: ");
        option = getIntFromRange(0, 2);
        printf("\n");

        if(option==1)
        {
            printf("Enter the household Income: $");
            demo->HouseholdIncome = getPositiveDouble();
            printf("\n");
        }

        if(option==2)
        {
            printf("Enter the country (30 chars max.): ");
            char s[31];
		    getCString(s, 0, 30);

		    // convert to uppercase
		    for (int i = 0; s[i]!='\0'; i++) {
		      if(s[i] >= 'a' && s[i] <= 'z') {
		         s[i] = s[i] -32;
		      }
		   	}

		   	for (int i = 0; s[i]!='\0'; i++)
		   	{
		   		demo->Country[i] = s[i];
		   	}
		   	printf("\n");
        }

    }while(option!=0);
}

