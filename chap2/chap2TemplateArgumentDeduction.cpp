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

==================== PART 1 ==================================================================================================
==================== Name lookup ( where to look for the fuction name ?)======================================================

This files have sample snipped code to make you learn C++ name lookup.
topic covered

- How compiler perform name lookup
- Argument dependent lookup ADL
- NameSpaces (NS)
- template specilization ( Primary template and specilize template) 
- you need to change the MACRO TEST* at the begning of the file to see different snipped working.


http://www.gotw.ca/gotw/030.htm
*/
#include <iostream>
#include <ostream>
#define TEST12 1 


/*
==================== PART 2 ==================================================================================================
==================== Template Argument deduction  ( where to look for the fuction name ?)=====================================
Benifit:

 1) Used for efficency / used to provide efficiency by having "specilize code for specific problem " 
	- Genericity is compiled out. you have dedicated class after compile time.
	- Think of designing of container implementation a.k.a vector et al
		* Will you use inheritance and inhert all the element from a common base like object (this is what java used to do)?
		* STL used template for the same and is much better.
 2) Convinience 
	- C++11 see example of auto
 Convention::
    In C++ standard spec.
	Specialization means ==> instantiation
	Parameter (P) template parameter
	Argument (A)  arguments you provide while you call the template function

 - 
*/


#if TEST8

/*

This test demonstrate the Template Argument deduction with a STL example of sort

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;
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
	meow(1113); // Hover over and see it compiler is deducing the argument as int
	meow<int>(1234); // Explicity specifying the argument .Dont do it usually. let compiler do the jobs by template argument deduction. [TAD]
	cout << "Finished";
}

#endif



#if TEST10

/*

This test demonstrate the Template Argument deduction and shows how it will fails
function argument - you are actually providing 
function parameter - which template is taking
template parameter - typename T
template argument  - when you intantiate the template like meow<int>

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;
template <typename T> meow(T one,T two){ // paramameter must be **exactly** match. no autmatic typecasting by compiler. 
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
template <typename T> meow(T& t){ // copy by value so its ok to modify. it does not change source. Will not work (compile error) if you have T& t
	t = t* 2;
	cout <<t << endl;
}
int main(){
	const int n = 20000; // n is const
	meow(n); // able to pass a const to a non const function argument (if passed by value) . Error out if function Parameter is "reference".
	
	cout << "Finished";
}

#endif
