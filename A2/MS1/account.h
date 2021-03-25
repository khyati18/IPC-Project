#ifndef ACCOUNT_H_
#define ACCOUNT_H_


struct Demographic
{
    int BirthYear;
    double HouseholdIncome;
    char Country [31];
};

struct UserLogin
{
    char Name[31];
    char LoginName[11];
    char Password[9];
};

struct Account
{
    int AccNumber;
    char AccType;
    struct UserLogin UsrLog;
    struct Demographic Demo;
};


void getAccount(struct Account* account, int max_acc_no);
void getUserLogin(struct UserLogin* login);
void getDemographic(struct Demographic* demo);

void updateAccount(struct Account* account);
void updateUserLogin(struct UserLogin* login);
void updateDemographic(struct Demographic* demo);


#endif