/*
Big picture:: 
	Compiler performs the follwoing step to resolve the names of the function (to determine which function need to be called for each call )
	1) Name lookup ( where to look for the fuction name ?)
	2) Template Argument Deduction. ( possible generate a set of candidate function from template) 
	3) overload resolution ( choose one from the candidate function set. if ambiguity exist through error )
	4) Access control
	5 virtual Function call

We will take each of the topic and expand on it.
Excerpts are taken from the Excellent Video.
Thank you "Stephan T. Lavavej"
http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Core-C-/Stephan-T-Lavavej-Core-C-1-of-n

*/
#include <iostream>
#include <ostream>
#define TEST17 1 


/*
==================== PART 3 ==================================================================================================

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;


#if TEST17
/*

	look what is passed as arguemnt and what is the parameter of the function. 
	Error in privious example is handled in standard library -- "provide overload"

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

template <typename T>void meow(const basic_string<T>& b){ 
  cout << "str:" << b << endl;
}
template <typename T>void meow(const T* b){  //overload
  cout << "ptr " << b << endl;
}
int main(){
  string S = string("abc"); // string is --  typdef  basic_string<char> string
	meow("abc");
  cout << "Finished" <<endl;
}

#endif

