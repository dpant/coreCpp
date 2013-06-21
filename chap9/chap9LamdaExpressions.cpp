/*

Understand concepts of expression 
Understand lamda expression

Excerpts are taken from the Excellent Video.
Thank you "Stephan T. Lavavej"
http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Core-C-/Stephan-T-Lavavej-Core-C-1-of-n

*/
#include <iostream>
#include <ostream>
#define TEST39 1 
#include <climits>

/*
================================================PART 8 =================================================
========================================================================================================


*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;

/* 

*/

#if TEST39
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

/*
	z = f() + g() + h();
    standard does not guaruntee the evaluation order of the function. it can
    execute in any order f,g,h or  h,g,f or g,f,h et al
     
    underfined behaviour ==> can be anything crash or runtime surprise 
                              eg i = i++;
    Impementation dependent ==> compiler implementor can choose any rational
                                behaviour and they have to document it
                                e.g : size of void*
    
    sequence point ==> defines the sequence of execution within a expression.
    , && || and many others are sequence point delemeter.
     Sequence point  also settles the side effect of operators ++ et al.
     
    think of 
    *src+++ = *dest++;
    
    , have the lowest priority 



*/
void sequencePoint(){ 
  int i = 10;
  int  j = 0,k=0;
  k  = (i++, j);
  cout << k <<endl;
  (j = i++),(j = i); // what is j?
  cout<< j <<endl;
  (j = i++); // what is j?
  cout<< j <<endl;
}

void meow(){
  cout << "meow" <<endl;
}

void purr(){
  cout << "purr" <<endl;
}

void printFunc(void (*p)()){
  p(); // this is equivalent to (*p)()
  (*p)();
}

int main(){

  printFunc(meow); // passing function as an argument 
  sequencePoint();
}

#endif

