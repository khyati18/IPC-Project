#ifndef ACCOUNT_TICKETING_UI_
#define ACCOUNT_TICKETING_UI_

#include "account.h"

struct AccountTicketingData
{
	struct Account* accounts;			// array of accounts
	const int ACCOUNT_MAX_SIZE; 		// maximum elements for account array
	struct Ticket* tickets;				// array of tickets
	const int TICKET_MAX_SIZE;			// maximum elements for ticket array
};

void displayAccountSummaryHeader(void);
void displayAccountDetailHeader(void);
void displayAccountSummaryRecord(const struct Account* account);
void displayAccountDetailRecord(const struct Account* account);


void applicationStartup(struct AccountTicketingData* account_data);
int menuLogin(struct AccountTicketingData* account_data);
void menuAgent(struct AccountTicketingData* account_data, const struct Account* user);     
void customermenuAgent(struct AccountTicketingData* account_data, const struct Account* user);     

int findAccountIndexByAcctNum(int AccNumber, struct Account account[], int size, int prompt);

void displayAllAccountSummaryRecords(const struct Account account[], int size);
void displayAllAccountDetailRecords(const struct Account account[], int size);
void pauseExecution(void);
int max_account_nom(const struct Account account[], int size);

#endif