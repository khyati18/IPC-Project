#include <stdio.h>

#include "accountTicketingUI.h"
#include "commonHelpers.h"

void displayAccountSummaryHeader(void)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");

}

void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* account)
{
    printf("%05d ", account->AccNumber);
    if(account->AccType=='C')
    {
        char type[10] = "CUSTOMER";
        printf("%-9s ", type);
    }
    else
    {
        char type[10] = "AGENT";
        printf("%-9s ", type);   
    }
    printf("%5d\n", account->Demo.BirthYear);
}

void displayAccountDetailRecord(const struct Account* account)
{
    printf("%05d ", account->AccNumber);
    if(account->AccType=='C')
    {
        char type[10] = "CUSTOMER";
        printf("%-9s ", type);
    }
    else
    {
        char type[10] = "AGENT";
        printf("%-9s ", type);   
    }
    printf("%5d ", account->Demo.BirthYear);
    
    printf("$%10.2lf ", account->Demo.HouseholdIncome);
    printf("%-10s ", account->Demo.Country);
    printf("%-15s ", account->UsrLog.Name);
    printf("%-10s ", account->UsrLog.LoginName);

    char password[9];
    int i;
    for(i=0; account->UsrLog.Password[i]!='\0'; i++)
        if(i%2) password[i] = '*';
        else password[i] = account->UsrLog.Password[i];
    password[i] = '\0';
    printf("%8s\n", password);
}

void applicationStartup(struct AccountTicketingData* account_data)
{
    int index=0;
    while((index=menuLogin(account_data))!=-1)
    {
        if(account_data->accounts[index].AccType=='A')
        {
            menuAgent(account_data, &account_data->accounts[index]);
        }
        else 
        {
        	customermenuAgent(account_data, &account_data->accounts[index]);
        }
    }

    printf("\n==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");

}

int menuLogin(struct AccountTicketingData* account_data)
{
    int selection = -1, accIndex = -1;
    do{
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 1);
        printf("\n");

        //choices
        if(selection==1)
        {
            printf("Enter your account#: ");
            int acno = getInteger();
            printf("\n");
            accIndex = findAccountIndexByAcctNum(acno, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
            if(accIndex==-1)
            {
                printf("ERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            else break;
        }
        
        if(selection==0)
        {
            //quit prompt
            printf("Are you sure you want to exit? ([Y]es|[N]o): ");
            char choice = getCharOption("yYnN");
            if(choice=='y' || choice=='Y')
            {
                accIndex = -1;
                //printf("\n");
                break;
            }
            printf("\n");
        }
    }while(1);
    return accIndex;
}

void menuAgent(struct AccountTicketingData* account_data, const struct Account* user)
{
    int option;
    do{
        printf("AGENT: %s (%05d)\n", user->UsrLog.Name, user->AccNumber);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: summary view\n");
        printf("5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("6) List new tickets\n");
        printf("7) List active tickets\n");
        printf("8) Manage a ticket\n");
        printf("9) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n\n");

        printf("Selection: ");
        option = getIntFromRange(0, 9);
        printf("\n");

        if(option==1)
        {
            int freeIndex = findAccountIndexByAcctNum(0, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
            if(freeIndex==-1) printf("ERROR: Account listing is FULL, call ITS Support!\n");
            else
            {
            	int max=0;
			    for(int i=0; i<account_data->ACCOUNT_MAX_SIZE; i++)
			    {
			        if(account_data->accounts[i].AccNumber>max)
			        {
			            max = account_data->accounts[i].AccNumber;
			        }
			    }
                getAccount(&account_data->accounts[freeIndex],max);
                printf("\n");
                getUserLogin(&(account_data->accounts[freeIndex].UsrLog));
                printf("\n");
                getDemographic(&(account_data->accounts[freeIndex].Demo));
                printf("\n");
                printf("*** New account added! ***\n");
                printf("\n");
                pauseExecution();
            }
        }

        if(option==2)
        {
            int index = findAccountIndexByAcctNum(0, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 1);
            updateAccount(&account_data->accounts[index]);
        }   

        if(option==3)
        {
            printf("Enter the account#: ");
            int acno = getInteger();
            int index = findAccountIndexByAcctNum(acno, account_data->accounts, account_data->ACCOUNT_MAX_SIZE, 0);
            if(account_data->accounts[index].AccNumber==user->AccNumber)
                printf("\nERROR: You can't remove your own account!\n");
            else{
                displayAccountDetailHeader();
                displayAccountDetailRecord(&account_data->accounts[index]);
                printf("\n");
                printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                char choice = getCharOption("YN");
                printf("\n");
                if(choice=='Y')
                {
                    account_data->accounts[index].AccNumber = 0;
                    printf("*** Account Removed! ***\n");
                }
                else printf("*** No changes made! ***\n");
            }
            printf("\n");
            pauseExecution();
        }

        if(option==4)
        {
            displayAllAccountSummaryRecords(account_data->accounts, account_data->ACCOUNT_MAX_SIZE);
            printf("\n");
            pauseExecution();
        }

        if(option==5)
        {
            displayAllAccountDetailRecords(account_data->accounts, account_data->ACCOUNT_MAX_SIZE);
            printf("\n");
            pauseExecution();
        }

        if(option==6)
        {
        	printf("Feature #%d currently available !\n", option);
        	printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }

        if(option==7)
        {
        	printf("Feature #%d currently available !\n", option);
        	printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }

        if(option==8)
        {
        	printf("Feature #%d currently available !\n", option);
        	printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }

        if(option==9)
        {
        	printf("Feature #%d currently available !\n", option);
        	printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }
    }while(option!=0);

    printf("### LOGGED OUT ###\n\n");
}

void customermenuAgent(struct AccountTicketingData* account_data, const struct Account* user)
{
    int option;
    do{
        printf("CUSTOMER: %s (%05d)\n", user->UsrLog.Name, user->AccNumber);
        printf("==============================================\n");
        printf("Customer Main Menu\n");
        printf("==============================================\n");
        printf("1) View your account detail \n");
        printf("2) List my tickets\n");
        printf("3) Create a new ticket\n");
        printf("4) Manage a ticket\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n\n");

        printf("Selection: ");
        option = getIntFromRange(0, 9);
        printf("\n");

        if(option==1)
        {
            displayAccountSummaryHeader();
		    int i;
		    for(i=0; i<account_data->ACCOUNT_MAX_SIZE; i++)
		    {
		        if(account_data->accounts[i].AccNumber==user->AccNumber)
		        {
		            displayAccountSummaryRecord(&account_data->accounts[i]);
		        }
		    }
		    printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }

        if(option==2)
        {
        	printf("Feature #%d currently available !\n", option);
        	printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }

        if(option==3)
        {
        	printf("Feature #%d currently available !\n", option);
        	printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }

        if(option==4)
        {
        	printf("Feature #%d currently available !\n", option);
        	printf("<< ENTER key to Continue... >>");
        	char enter = 0;
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
        }

    }while(option!=0);

    printf("### LOGGED OUT ###\n\n");
}

int findAccountIndexByAcctNum(int AccNumber, struct Account account[], int size, int prompt)
{
    if(prompt) 
    {
        printf("Enter the account#: ");
        AccNumber = getInteger();
        printf("\n");
    }
    int i, index = -1;
    for(i=0; i<size; i++)
    {
        if(account[i].AccNumber==AccNumber)
        {
            index = i;
            break;
        }
    }
    return index;
}

void displayAllAccountSummaryRecords(const struct Account account[], int size)
{
    displayAccountSummaryHeader();
    int i;
    for(i=0; i<size; i++)
        if(account[i].AccNumber!=0)
            displayAccountSummaryRecord(&account[i]);
}

void displayAllAccountDetailRecords(const struct Account account[], int size)
{
    displayAccountDetailHeader();
    int i;
    for(i=0; i<size; i++)
        if(account[i].AccNumber!=0)
            displayAccountDetailRecord(&account[i]);
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
}
