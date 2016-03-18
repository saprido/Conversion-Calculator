#ifndef CALC_H_
#define CALC_H_

struct Number_
{
  int type;
  char* input;
  int sign;
};


struct Number_* NumberCreate(char* inputS, char typeS, int s);
int power(int x, int n);
char* ConvertString(int a);
int ConvertInt(char* str);
void printNumber(struct Number_* num);
struct Number_* ConvertDecimal(struct Number_* a);
struct Number_* ConvertHex(struct Number_* a);
struct Number_* ConvertBinary(struct Number_* a);
struct Number_* ConvertOctal(struct Number_* a);
struct Number_* operate(struct Number_* a, struct Number_* b, char type, char op);
int FormatCheck(char* arg1, char* arg2, char* arg3, char* arg4);

#endif
