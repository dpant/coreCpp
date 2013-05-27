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
#define TEST22 1 


/*
==================== PART 3 ==================================================================================================
======================================overload Resolution==================================================================
1) add candidate function to the overload set , some of these candidate will come from template argument deduction
    overload resolution does not look into the return type. it completely ignores it.
2) "Viability Test:" Is candidate a viable fucntion ? , matches the number of arguments with the number of parameters. 
    Also check if the argment provided is convertable (by implicity conversion)  to the parameter specified.
	eg::
	foo(int,int)   
	foo(int,int,int);
	foo(1,2); the first foo will be selected becuase it is the only vaiable candidate

	int meow(int)
	int meow(const string &)

	meow(11) //int // second candidate will fail the viabiity test since int is not convertable to string.
	meow(s) // string --
	meow("peperment"); // const char[N]

	Both option "int meow(int)" and "int meow(const string &)" are vaiable candidate 

3)  Best viable function concept
		some implicit conversion of argment are better than others  


*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;


#if TEST18
/*
	Best viable option:
		both meow function are viable but only the best viable are choosen.
		least argument conversion is the best viable match.

*/
#include <ostream>
#include <iostream>
#include <string>
using namespace std;

template <int N>void meow(const char (&)[N]){ 
  cout << "void meow(const char (&)[N])" << endl;
}
void meow(const string & ){
  cout << "meow(const string & )" <<endl;
}
int main(){
  meow("abc"); // which function to choose ?? (Best viable option)
  string st("bob"); // which function to choose?? (Best Viable option)
	meow(st);
}

#endif


#if TEST19
/*
	Best viable option:
		both meow function are viable but only the best viable are choosen.
		least argument conversion is the best viable match.

*/
#include <ostream>
#include <iostream>
#include <string>
using namespace std;

template <int N>void meow(const char (&)[N]){ 
  cout << "void meow(const char (&)[N])" << endl;
}
void meow(const string & ){
  cout << "meow(const string & )" <<endl;
}
int main(){
  meow("abc"); // which function to choose ?? (Best viable option)
  string st("bob"); // which function to choose?? (Best Viable option)
	meow(st);
}

#endif


#if TEST20
/*
	Trickly question:
		what will be output of the follwoing program?
	Both the function are the viable candidate.
		but which one is the most viable candidate?
		int * ==>  const int* [ qualification conversion ]
		int* ==> const (int*) & [ identity conversion ]

	moral of story .. Template are greedy :)


*/
#include <ostream>
#include <iostream>
#include <string>
using namespace std;

/* TAD will deduce the T as int*  so the argument become "const (int*) &m" ===> m is a reference to "integer pointer which is constant" */
template <typename T>void foo(const T& m){  // m is a reference to type T which is constant. === m is a referece to constant T

  cout << "template <typename T>void foo(const T&)" << endl;
}
/* TAD will decude T as "int" so the argument become "const (int)* k" ==>  k is a pointer to an constant integer  */
template <typename T>void foo(const T* k){ 
  cout << "template <typename T>void foo(const T *)" << endl;
}

int main(){
  int *p = nullptr;
  foo(p);
}

#endif


#if TEST21
/*
	Trickly question:
	(tie breaker rule)
		minimum distance conversion. 
		Morederived* is convered to Derived *

*/
#include <ostream>
#include <iostream>
#include <string>
using namespace std;


class Base {};
class Derived :public Base {};
class MoreDerived : public Derived {};

void foo(Base *){
  cout << " i am inside void foo(Base *)" <<endl;
}

void foo(Derived *){
  cout << " i am inside void foo(Derived *)" <<endl;
}

int main(){
  MoreDerived *md = new MoreDerived();
  foo(md);

}

#endif


#if TEST22
/*
		shared_ptr is part of standand library not the core C++ language.
		All UDC (user defined conversion) are considered indistinquishable. (there is no way to prefer one over other)  
		so an ambiguity arises here.

		to fix the static_cast to fix this.

*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;


class Base {};
class Derived :public Base {};
class MoreDerived : public Derived {};

void foo(shared_ptr<Base> &){
  cout << " i am inside void foo(shared_ptr<Base> *)" <<endl;
}

void foo(shared_ptr<Derived> &){
  cout << " i am inside void foo(shared_ptr<Derived> *)" <<endl;
}

int main(){
  shared_ptr<MoreDerived> spmd;
  //shared_ptr<Derived> spd = static_cast<shared_ptr<Derived>>(spmd); // to make it work do a static cast 
  //foo(spd);
  foo(smpd);
}

#endif

