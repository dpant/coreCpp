/*

Template MetaProgramming, Airthmetic conversion.

Excerpts are taken from the Excellent Video.
Thank you "Stephan T. Lavavej"
http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Core-C-/Stephan-T-Lavavej-Core-C-1-of-n

*/
#include <iostream>
#include <ostream>
#define TEST37 1 
#include <climits>

/*
================================================PART 7 =================================================
========================================================================================================
* Explains the rules and gochas of Airthmetic conversion.


*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;

/* 

*/

#if TEST37
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

/*
type conversion

#1
   Integral promotion:: (Always happen to both operand) 
   --  They are value preserving. i.e value represented in type A
	   after conversion to type B the same value will be observed in 
	   type B
   Only happen to Tiny types (types which have size less than int
		 char (unsigned/signed)
		 short(unsigned/signed)
	Tiny types are promoted to int before any binary or boolean 
    comparision operation.
	This is consistent becuase the smallest possbile unit in which these 
    operator work at assembly language is int. so doing integral promotion
     conversion of tiny type is consistant with the machine req

#2
    If after doing integral promotion both the operand are not of same type
    a value promotion will happen from the smaller type to bigger type.
    so a 
    signed short + signed long long  
           will become 
    signed long  + signed long long 

#3
    consider a case 

     usigned char    +      unsigned T
     [ 0  - 255]    +      [ T can be char, short ,int long , long long]

    After integral promotion 

     int                +      [ T can be int ,long , long long]

so this case will not observe any value transformation. so we are safe.


#4
	There are many other complex rule which deal will value promotion of type
    which are mixed signed and unsiged.    
          
     signed char    +                  unsigned T
     [ -128 to  127]    +      [ T can be char, short ,int long , long long]

	Let say if the type T is long,long long
    After integral promotion 

     signed int                +      [ T will remain as unsiged long or unsigned long long  ]
   
     
  



*/

void printUnsignedCharSum(){ 
  unsigned char x = 250; 
  unsigned char y = 255;
  cout<< "sum is: " << x+y <<endl;  /* tiny type no overflow !! */
}

void printUnsignedLongSum(){
  cout<< sizeof(unsigned long) <<endl;
  unsigned long x = 4000000000; /* 4 B */
  unsigned long y = 3000000000; /* 3 B */
  cout<< "sum is: " << x+y <<endl;   /* not a tiny type so overflow */
}

void printMAX_INT(){ /* find out INT_MAX or INT_MIN */
  int INT_M;
  int  t =  sizeof(int);
  INT_M = ~(1 << (t * 8 -1));
  cout<< (INT_M == INT_MAX) <<endl;
  cout<< (INT_MIN == (1<<31)) <<endl;
  cout<< "INT_MAX: " << INT_M <<endl;
  cout<< "INT_MIN: " << (1<<31) <<endl;
}
/* 

 Promotion of signed char to unsigned long might be bit preserversing with a 
 sign extension. it is not value preserving!!! 
	Actual value transformation happens in the process of value promotion
		-1 is changes to a large postive value !!!!

		** be careful while you mix signed and unsigned type **

*/
void SignedUnsignedMixing(){ /* dangers of mixing signed and unsiged number */
  signed char sc = -1;
  unsigned long ul = 0xFFFFFFFF; /* a very large number */
  cout<< "comparision: " << (sc == ul) <<endl;   /* see -1 == very large number */
}


int main(){
  printUnsignedCharSum();
  printUnsignedLongSum();
  printMAX_INT();
  SignedUnsignedMixing();

}

#endif

