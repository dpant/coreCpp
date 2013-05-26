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
==================== PART 2 ==================================================================================================
==================== Template Argument deduction  ( where to look for the fuction name ?)=====================================
Benifit:

 1) Used for efficency / used to provide efficiency by having "specilize code for specific problem " 
	- Genericity is compiled out. you have dedicated class after compile time.
	- Think of designing of container implementation a.k.a vector et al
		* Will you use inheritance and inhert all the element from a common base like object (this is what java used to do)?
		* STL used template for the same and it is much better.
 2) Convinience 
	- C++11 see example of auto
 Convention::
    In C++ standard spec.
	Specialization means ==> instantiation
	Parameter (P) template parameter / function parameter in function definition
	Argument (A)  arguments you provide while you call the template function

*/


/*

This test demonstrate the Template Argument deduction with a STL example of sort

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;

#if TEST8
int main(){
	vector<int> v;
	v.push_back(1);
	v.push_back(7);
	v.push_back(2);
	v.push_back(9);
	std::sort(v.begin(),v.end()); // STL agorithm - can take any random access iterators.
	for (auto i = v.begin(); i!= v.end() ; i++){
		cout << *i;
	}
	cout << "Finished";
}

#endif



#if TEST9

/*

This test demonstrate the Template Argument deduction with a STL example of sort
- template argument deduction is matching between function parameter and function argument 

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;
template <typename T> meow(T t){
	cout <<t << endl;
}

int main(){
	meow(1113); // Hover over in visual studio to  see  compiler is deducing the argument as int
	meow<int>(1234); // Explicity specifying the argument . Dont do it usually. let compiler do the jobs by template argument deduction. [TAD]
	cout << "Finished";
}

#endif



#if TEST10

/*

This test demonstrate the Template Argument deduction and shows how it will fails
function argument - you are actually providing 
function parameter - which is denfined when defining the template
template parameter - typename T
template argument  - when you intantiate the template like meow<int>

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;
template <typename T> meow(T one,T two){ // paramameter must be **exactly** match. no autmatic typecasting/typeconversion done  by compiler. 
	cout <<one << two << endl;
}

int main(){
	meow(1113,100L); // ERROR. cant deduce the template paramater// int , long  
	cout << "Finished";
}

#endif


#if TEST11

/*
	This will work fine (compile fine) and do the Template argument deduction correctly notice the argument pass is const while the parameter to the template is non const

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;
template <typename T> meow(T t){ // copy by value so its ok to modify. it does not change source. Will not work (compile error) if you have T& t
	t = t* 2;
	cout <<t << endl;
}
int main(){
	const int n = 20000; // n is const
	meow(n); // able to pass a const to a non const function argument (if passed by value) . Error out if function Parameter is "reference".
	
	cout << "Finished";
}

#endif



#if TEST12
/*
	This will give a compile time error.  Can you find out the reason.
	look what is passed as arguemnt and what is the parameter of the function.
*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;
template <typename T> meow(T& t){ // copy by reference. its ok to modify the passed arguments?. it does change the source. Will not work (compile error)  T& t
	t = t* 2;
	cout <<t << endl;
}
int main(){
	const int n = 20000; // n is const
	meow(n); // will not be able to pass a const to a non const function argument (if passed by reference) . Error out if function Parameter is "reference".
	
	cout << "Finished";
}

#endif




#if TEST13
/*
   **must compile with -std=c++0x in gcc
	demonstrate the complexity of TAD in case of type_traits
    ** type_traits are used to 
       Agument the type of datatype in i.e add constantness, make is unsigned etc.


*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
#include <type_traits>
using namespace std;
template <typename T>void meow(T t){ 
  typedef typename  make_unsigned<T>::type U; //changed the type passed to unsigned type
  U u = static_cast<U>(t); // typecast t to new type  U
  cout << u << endl;
}
int main(){
	const int n = -20000; // n is const
	meow(n); 
	cout << "Finished" <<endl;
}

#endif

#if TEST14
/*
   **must compile with -std=c++0x in gcc

	This will give a compile time error. 
    Can you find out the reason (?) [TAD] failed ??

	look what is passed as arguemnt and what is the parameter of the function.

    ERROR:
    chap2TemplateArgumentDeduction.cpp:227:8: error: no matching function for call to ‘meow(const int&)’
	chap2TemplateArgumentDeduction.cpp:227:8: note: candidate is:
	chap2TemplateArgumentDeduction.cpp:222:27: note: template<class T> void meow(typename std::make_unsigned<_IntType>::type)

	TAD don't look across the :: (think it as a brick wall)
     because make_unsigned is a kind of mapping which maps
	 int, unsigned int ==> unsigned int.
	 short         ==> unsigned short.
     et al.
     it can't deduce from usinged int what value is passed an int or an unsigned int !! many to one function !!!.


*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
#include <type_traits>
using namespace std;
template <typename T>void meow(typename make_unsigned<T>::type t){  // TAD doesn't cross :: while deducte the T. 
   cout << t << endl;
}
int main(){
	const int n = -20000; // n is const
	meow(n); 
	
	cout << "Finished" <<endl;
}

#endif

#if TEST15
/*
    Can you find out the reason (?) [TAD] failed ??

	look what is passed as arguemnt and what is the parameter of the function. TAD happens smoothly

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

template <typename T>void meow(const basic_string<T>& b){ 
   cout << b << endl;
}
int main(){
  string S = string("abc"); // string is basic_string<char>
	meow(S);
  cout << "Finished" <<endl;
}

#endif

#if TEST16
/*

	look what is passed as arguemnt and what is the parameter of the function. TAD  does not happen

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

template <typename T>void meow(const basic_string<T>& b){ 
   cout << b << endl;
}
int main(){
	meow("abc"); // this is const char *. Can you convert it to const basic_string ?? 
	cout << "Finished" <<endl;
}

#endif

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

