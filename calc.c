#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "calc.h"
enum dataType{
  binary,        //0
  octal,         //1
  decimal,       //2
  hex            //3
};

/* Number has three paramters: 
 * type holds the type of the number correlated to the dataTypes from enum dataTypes,  * input holds the character string that holds the numerical value of the number, and  * int signs has 0 if the numerical value is negative, and 1 if it is positive
*/
/*struct Number_{
  int type;
  char* input;
  int sign;
};
*/
typedef struct Number_ Number;

/* Creates Number based on input from the user*/
Number* NumberCreate(char* inputS, char typeS, int s)
{
  Number* newNum = (Number*)malloc(sizeof(Number));
  newNum->input=inputS;
  switch(typeS)
    {
    case 'b':
      newNum->type = binary; 
      break;
    case 'o':
      newNum->type = octal;
      break;
    case 'd':
      newNum->type = decimal;
      break;
    case 'x':
      newNum->type = hex;
      break;
    }
  newNum->sign = s;
  return newNum;
}

/*
  returns the exponential value of int x to the nth power.
 */
int power(int x,int n)
{
  int i; // Variable used in loop counter 
  int number = 1;

  for (i = 0; i < n; ++i)
    number *= x;

  return(number);
}

/*
  converts an integer into a char* without using cast
 */
char* ConvertString(int a)
{

  int len = a*10;
  char result [len];
  int tempR = a;


  //gets number of digits
  int remainder = 0; 
  int p = 1; 
  int count;
  for(count = 0; count<a*10; count++){
    remainder = tempR/power(10,p);
    if(remainder<1){
      break;
    }
    p++;
  }
  
  int numDigits = p;
  int singleDigit = tempR;
  int numPower = numDigits-1;

  //gets each digit individually and places it as a character in a char array
  for(count = 0; count<numDigits; count++){
    int powerN = power(10,numPower);
    singleDigit = tempR/powerN;
    result[count] = singleDigit+'0';
    int sub = singleDigit*powerN;
    tempR = tempR - sub;
    numPower--;
  }
  
  //converts the char array into a char* that is then returned
  result[count++] = '\0';
  char* str6 = malloc(sizeof(result));
  strcpy (str6, result);
  

  return str6;

}

int ConvertInt(char* str)
{
  int result = 0;
  int count = 0; 
  for(count = 0; str[count]!= '\0'; count++){
    result = result*10 + str[count] - '0';
  }
  return result;
}


void printNumber(Number* num)
{
  if(num->sign == 1){
    switch(num->type)
      {
      case binary:
	printf("b%s\n",num->input);
	break;
      case octal:
	printf("o%s\n",num->input);
	break;
      case hex:
	printf("x%s\n",num->input);
	break;
      case decimal:
	printf("d%s\n",num->input);
	break;
      } 
  }
  else{
    switch(num->type)
      {
      case binary:
	printf("-b%s\n",num->input);
	break;
      case octal:
	printf("-o%s\n",num->input);
	break;
      case hex:
	printf("-x%s\n",num->input);
	break;
      case decimal:
	printf("-d%s\n",num->input);
	break;
      }
  }
  
  
}


/*CONVERTION FUNCTIONS START HERE: */

Number* ConvertDecimal(Number* a)
{
  Number* numC = NumberCreate(a->input,'d',a->sign);  
  int len = strlen(a->input);
  len = len*2;
  char num [len]; //modified input string
  strcpy(num,a->input);
  int count, tempC;
  int tempR = 0; 
  //int tempV = 0;
  int numDigits = strlen(a->input)-1;
  //int base = 10;
  int number;
  int s = 0;
  int c = 10;
  int pos = 0;
  char i;
  //char result [len]; //resulting hex
  switch(a->type)
    {
    case binary:
      for(count = 0; count<strlen(num); count++){
	tempC = (num[count])-'0';
	tempR = (tempR*2)+tempC;
      }
      numC->input = ConvertString(tempR);    
      return numC;
    case octal:
      for(count = numDigits; count>=0; count--)
	{
	  if(num[pos]>='0' && num[pos]<= '7')
	    number = num[pos]-'0';
	  s+= number*(power(8,count));
	  pos++;
	}
      numC->input = ConvertString(s);    
      return numC;
    case hex:
      for(count = numDigits; count>=0; count--){
	if(num[pos]>='0' && num[pos]<= '9')
	  number = num[pos]-'0';
	else{
	  for(i = 'a'; i<= 'f'; i++){
	    if(num[pos] == i){
	      number = c;
	      break;
	    }
	    c++;
	  }
	  c = 10;
	  for(i = 'A'; i<= 'F'; i++){
	    if(num[pos] == i){
	      number = c;
	      break;
	    }
	    c++;
	  } 
	}
	s+= number*(power(16,count));
	pos++;
	}
      numC->input = ConvertString(s);    
      return numC; 
    case decimal:
      return a;
    }
  return a;
}

Number* ConvertHex(Number* a)
{
  Number* numC = NumberCreate(a->input,'x',a->sign);  
  Number* temp = NULL;
  Number* temp3 = NULL;
  int len = strlen(a->input);
  len = len*2;
  char num [len]; //modified input string
  int count,remainder;
  int pos = 0;
  char result [len]; //resulting hex
  switch(a->type){
  case hex:
    return a;
  case decimal:
    remainder = -1;
    strcpy(num,a->input);
    int temp;
    char temp2[3];
    char reverse [len];
    temp = ConvertInt(num);
    while(remainder!=0){
      remainder = temp%16;
      if(remainder>9){
	temp2[0] = 'a'+(remainder-10);
	temp2[1] = '\0';
      }
      else{
	temp2[0] = remainder+'0';
	temp2[1] = '\0';
      }
      if(strcmp(temp2,"0")!=0){
	strcpy(result+pos, temp2);
      }
      temp = temp/16;
      pos++;
    }
    result[pos++] = '\0';
    pos = 0;
    for(count = strlen(result)-1; count>=0; count--){
      reverse[pos] = result[count];
      pos++;
    }
    reverse[pos++]='\0';
    char* strd = malloc(sizeof(reverse));
    strcpy (strd, reverse);

    numC->input = strd;
    return numC;
  }
  temp = ConvertDecimal(a);
  temp3 = ConvertHex(temp);
  free(temp);
  char* tempString = malloc(sizeof(temp3->input));
  strcpy(tempString,temp3->input);
  numC->input = tempString;
  free(temp3);
  return numC;
    
}

Number* ConvertBinary(Number* a)
{
  Number* numC = NumberCreate(a->input,'b',a->sign);  
  int count = 0;
  char result [strlen(a->input)*4];
  int pos = 0;
  char num [strlen(a->input)];
  int len = strlen(a->input)*5;
  int numberInt = ConvertInt(a->input); //cnanot use atoi
  strcpy(num,a->input);
  int remainder;
  int dividend = -1;
  char reverse[len];

  Number* temp = NULL;
  Number* temp2 = NULL;

  switch(a->type){
  case binary:
    return a;
  case decimal:
    while(dividend!=0){
      dividend = numberInt/2;
      remainder = numberInt%2;
      result[count] = remainder+'0';
      count++;
      numberInt = dividend;
    }

    result[count++] = '\0';
    pos = 0;
    
    for(count = strlen(result)-1; count>=0; count--){
      reverse[pos] = result[count];
      pos++;
    }   
    reverse[pos++]='\0';
    char* strd = malloc(sizeof(reverse));
    strcpy (strd, reverse);  
    numC->input = strd;
    return numC;

  }
  
  temp = ConvertDecimal(a);
  temp2 = ConvertBinary(temp);
  free(temp);
  char* tempString = malloc(sizeof(temp2->input));
  strcpy(tempString,temp2->input);
  numC->input = tempString;
  free(temp2);
  return numC;

}

Number*ConvertOctal(Number* a)
{
  Number* numC = NumberCreate(a->input,'o',a->sign);  
  int count = 0;
  char result [strlen(a->input)*4];
  int pos = 0;
  char num [strlen(a->input)];
  int len = strlen(a->input)*5;
  int numberInt = atoi(a->input); //cnanot use atoi
  strcpy(num,a->input);
  int remainder;
  int dividend = -1;
  char reverse[len];

  Number* temp = NULL;
  Number* temp2 = NULL;

  switch(a->type)
    {
    case octal:
      return a;
    case decimal:
    while(dividend!=0){
      dividend = numberInt/8;
      remainder = numberInt%8;
      result[count] = remainder+'0';
      count++;
      numberInt = dividend;
    }

    result[count++] = '\0';
    pos = 0;
    
    for(count = strlen(result)-1; count>=0; count--){
      reverse[pos] = result[count];
      pos++;
    }   
    reverse[pos++]='\0';
    char* strd = malloc(sizeof(reverse));
    strcpy (strd, reverse);  
    numC->input = strd;
    return numC;     
    }
  temp = ConvertDecimal(a);
  temp2 = ConvertOctal(temp);
  free(temp);
  char* tempString = malloc(sizeof(temp2->input));
  strcpy(tempString,temp2->input);
  numC->input = tempString;
  free(temp2);
  return numC;

 
}

/*OPERATOR METHODS START HERE: */

/* Given two Numbers and the result type, add return the sum as a Number*/
Number* operate(Number* a, Number*b, char type, char op)
{
  Number* numA = ConvertDecimal(a);
  Number* numB = ConvertDecimal(b);
  Number* numC = NULL;
  Number* resultNum = NULL;
  int integerA = ConvertInt(numA->input);
  int integerB = ConvertInt(numB->input);
  int result = 0;
  int newSign = -1;

  if(numA->sign == 0)
    integerA = -1*integerA;
  if(numB->sign == 0)
    integerB = -1*integerB;
 

  //  printf("numA: %d \t numB: %d\n",a->type, b->type);
  switch(op)
    {
    case '+':
      result = integerA+integerB;
      break;
    case '-':
      result = integerA-integerB;
      break;
    case 'X':
      result = integerA*integerB;
      break;
    }
  if(result<0){
    newSign = 0; 
    result = result*-1;
  }
  else
    newSign = 1;

  char *resultString = ConvertString(result);
   switch(type)
    {
    case 'o':
      numC = NumberCreate(resultString,'d',newSign);
      resultNum = ConvertOctal(numC);
      free(numC);
      return resultNum;
    case 'b':
      numC = NumberCreate(resultString,'d',newSign);
      resultNum = ConvertBinary(numC);
      free(numC);
      return resultNum;
    case 'x':
      numC = NumberCreate(resultString,'d',newSign);
      resultNum = ConvertHex(numC);
      free(numC);
      return resultNum;
    case 'd':
      numC = NumberCreate(resultString,'d', newSign);
      return numC;
    }
   return numA;
}


/* Input arguments are concated into a char* in the main method and are then sent to
 * this method for format checking. 
 * Errors are printed out with a short description of why they are considered invalid 
 */

int FormatCheck(char* arg1, char* arg2, char* arg3, char* arg4)
{
  int len = strlen(arg1)+strlen(arg2)+strlen(arg3)+strlen(arg4);
  char operatorS [len];
  char cTypeS [len];
  char operator;
  char cType;
  char aType;
  char bType;
  int count;
  char aNum [len];
  char bNum[len];
  int numStartA = 0;
  int numStartB = 0;
    strcpy(operatorS, arg1);
    strcpy(aNum, arg2);
    strcpy(bNum, arg3);
    strcpy(cTypeS, arg4);
    
    operator = operatorS[0];
    cType = cTypeS[0];
    aType = aNum[0];
    bType = bNum[0];
    //operator can only be + or -
    if(!(operator=='+'||operator=='-'||operator=='X')){
      printf("ERROR: Invalid Operator\n");
      return 1;
    }
    if(aNum[0] == '+'||aNum[0]=='-'){
      numStartA = 1;
      aType = aNum[1];
    }
    if(bNum[0] =='+'||bNum[0] == '-'){
      numStartB = 1;
      bType = bNum[1];
    }
    
    //Only binary, octal, decimal and hex prefixes
    if(!( aNum[numStartA]=='b'|| aNum[numStartA]=='o'|| aNum[numStartA]== 'd'||  aNum[numStartA]=='x')){
      printf("ERROR: Invalid Number Prefix for Number 1\n");
      return 1;
    }
    if(!(bNum[numStartB]=='b'||bNum[numStartB]=='o'|| bNum[numStartB] == 'd'|| bNum[numStartB] =='x')){
      printf("ERROR: Invalid Number Prefix for Number 2\n");
      return 1;
    }
    if(!(cType=='b'||cType =='o'|| cType == 'd'|| cType =='x')){
       printf("ERROR: Invalid Result Type\n");
       return 1;
    }
    
    //CHECKING FIRST NUMBER
    for(count = numStartA+1; count<strlen(aNum); count++){
      if(aType == 'b' && !(aNum[count]=='0'|| aNum[count]=='1')){
	printf("ERROR: Invalid Number 1\n");
	return 1;
      }
      if(aType == 'o' && (aNum[count]>'7'|| aNum[count]<'0')){
	printf("ERROR: Invalid Number 1\n");
	return 1;
      }
      if(aType == 'd' && !(aNum[count]>='0'&& aNum[count]<='9')){
	printf("ERROR: Invalid Number 1\n");
	return 1;
      }
      if(aType == 'x' && !(aNum[count]>'0'&& aNum[count]<='9')){
	if(!((aNum[count]>='a' && aNum[count]<='f')|| (aNum[count]>='A' && aNum[count]<='F'))){
	  printf("ERROR: Invalid Number 1\n");
	  return 1;
	}
      }
    }
    //CHECKING SECOND NUMBER
    for(count = numStartB+1; count<strlen(bNum); count++){
      if(bType == 'b' && !(bNum[count]=='0'|| bNum[count]=='1')){
	printf("ERROR: Invalid Number 2\n");
	return 1;
      }
      if(bType == 'o' && (bNum[count]>'7'|| bNum[count]<'0')){
	printf("ERROR: Invalid Number 2\n");
	return 1;
      }
      if(bType == 'd' && !(bNum[count]>='0'&& bNum[count]<='9')){
	printf("ERROR: Invalid Number 2\n");
	return 1;
      }
      if(bType == 'x' && !(bNum[count]>='0'&& bNum[count]<='9')){
	if(!((bNum[count]>='a' && bNum[count]<='f')|| (bNum[count]>='A' && bNum[count]<='F'))){
	  printf("ERROR: Invalid Number 2\n");
	  return 1;
	}
      }
    }
  
  return 0;
}

int main(int argc, char** argv)
{

  //concat argv arguments to string and then Format check;

  //FORMAT CHECKING

  if(argc!=5)
    {
      printf("ERROR: Too little or too many arguments\n");
      return 0;
    }
   
  if(FormatCheck(argv[1],argv[2],argv[3],argv[4])!= 0){
    return 0;
  }

  //DECLARING AND INTIALIZING VARIABLES
  else{
    int len = strlen(argv[1]);
    char operator,aType,bType,cType;
    char aNumber [len];
    char bNumber [len];
    char aNum [len];
    char bNum [len];
    //    int count;
    int signA = 1;
    int signB = 1;
    char operatorS [len];
    char cTypeS [len];
    
    strcpy(operatorS, argv[1]);
    strcpy(aNumber, argv[2]);
    strcpy(bNumber, argv[3]);
    strcpy(cTypeS, argv[4]);

    operator = operatorS[0];
    cType = cTypeS[0];
    //    sscanf(argv[1],"%c %s %s %c",&operator,&aNumber,&bNumber,&cType);

    //HANDLING SIGNED NUMBERS
    if(aNumber[0] == '-'){
      signA = 0;
      aType = aNumber[1];
      strcpy(aNum, aNumber+2);
    }
    else if(aNumber[0] == '+'){
      aType = aNumber[1];
      strcpy(aNum, aNumber+2);
    }
    else{
      aType = aNumber[0];
      strcpy(aNum, aNumber+1);
    }

    if(bNumber[0] == '-'){
      signB = 0;
      bType = bNumber[1];
      strcpy(bNum, bNumber+2);
    }
    else if(bNumber[0] =='+'){
      bType = bNumber[1];
      strcpy(bNum, bNumber+2);
    }
    else{
      bType = bNumber[0];
      strcpy(bNum, bNumber+1);
    }

    //CREATES VARIABLES
    Number* numA = NumberCreate(aNum,aType,signA);
    Number* numB = NumberCreate(bNum,bType,signB);
    Number* numC = NULL;

    numC = operate(numA,numB,cType,operator);
    printNumber(numC);
    //    printf("C INFO: Sign: %d, Value: %s, Type: %d\n",numC->sign, numC->input, numC->type);


    free(numA);
    free(numB);
    free(numC);
  }  
  return 0;
}
