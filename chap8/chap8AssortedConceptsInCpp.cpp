/*

Understand various cast in C++
Understand ODR rule in C++

Excerpts are taken from the Excellent Video.
Thank you "Stephan T. Lavavej"
http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Core-C-/Stephan-T-Lavavej-Core-C-1-of-n

*/
#include <iostream>
#include <ostream>
#define TEST38 1 
#include <climits>

/*
================================================PART 8 =================================================
========================================================================================================

Understand various cast in C++
Understand ODR rule in C++


*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;

/* 

*/

#if TEST38
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

/*
casts

#1
Four type of cast in C++
  1)const_cast
     cast away constantness
  2) static_cast
     force one type to other explicitly but only when possible.
	 * can be used with template argument deduction if eg:
		max (const T & a, const T &);
		and you call it for int and an long long. Template argument 
        deduction will fail in this case because both type does not 
        match.
        int i;
        long long ll;
		max(i,ll);
	  * can static cast one type to other only if they are convertiable like int to long long, any base class to derive class. et al.
		
  3) reinterpret_cast

  * Think this as a casting of bit to other type.
  * you can cast an interget and make it a pointer through this but does it 
    really you want. Think twice before you use reinterpret_cast.
  * You can potientially cast any type to any other type , which might lead to
    undefined behaviour if you haven't thought carefully about casting.
  * "never use reinterpret_cast in inheritence". Think what will happen when you
    have a multiple inheritence and you did a reinterpret cast of base pointer
    to a derived class. due to the class layout your resulted (casted pointer)
    might or might not be correct 
  * In inheritence cases always you static_cast becuase it do the offset
   adjustment based on the layout.
      
  4) dyanmic_cast
 
   * decided at runtime. so it might have a runtime panalty.
   * if you are using this think can i use virtual function instead!!!.
  


C style casts:

* It interally chooses one of the 4 categories metioned above. 
* Never prefer this. 
	* Hard to search in code what cast you are using
    * it is much more unpredictiable and can choose any one of the 4 casts metioned above. It might surprise you at the end.

  Y = (int) X 
  Z = int (X) // new style in C++ but is same as old C style.
  
*/
/* 
constCast ==> cast away constant ness 
	changing a data member which is born const can trigger an undefined behaviour
    but you can always cast away constantness of pointers.

*/
void constCastExample(){ 
  const int x = 10;
  const int y = 20;
  int const *pci = &x;
  int *pmi = const_cast<int*>(&y);
  //*pci = 11; // compilation error !! pci is pointer to const int
  pci = pmi;	/* its perfectly find to add constant ness. compiler is happy with this */
  cout<< *pci << endl;	
  //pmi = pci; /* this is not valid, compiler error: converting const int* to int* */
  pmi = const_cast<int*>(pci); /* const cast make it work */
  *pmi = 100;
  cout<< "Y changed to :" << x << endl;	 // changing data which is born const undefined behaviour. does not reflect the change !! 
  
}



int main(){
  constCastExample();
}

#endif

