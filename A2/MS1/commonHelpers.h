#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

int currentYear(void);
void clearStandardInputBuffer(void);

int getInteger();
int getPositiveInteger();
int getIntFromRange(int lower, int upper);

double getDouble();
double getPositiveDouble();
char getCharOption(const char* types);
void getCString(char* str, int min, int max);


#endif