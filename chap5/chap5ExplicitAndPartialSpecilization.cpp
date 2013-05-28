/*
Big picture:: 
	Compiler performs the follwoing step to resolve the names of the function (to determine which function need to be called for each call )
	1) Name lookup ( where to look for the fuction name ?)
	2) Template Argument Deduction. ( possible generate a set of candidate function from template) 
	3) overload resolution ( choose one from the candidate function set. if ambiguity exist through error )
	4) Access control
	5) virtual Function call
    6) Explicity and partial specilization of template function and classes.
  

We will take each of the topic and expand on it.
Excerpts are taken from the Excellent Video.
Thank you "Stephan T. Lavavej"
http://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Core-C-/Stephan-T-Lavavej-Core-C-1-of-n

*/
#include <iostream>
#include <ostream>
#define TEST32 1 


/*
==================== PART 5 ==================================================================================================
======================================Excipilit and partial specilization==================================================================
* Some of the snippet does not work with gcc 4.6 need to use gcc 4.7 or higher
   in ubuntu use "sudo apt-get install gcc-snapshot"
   than you can use the experimental version of gcc 4.8 located at 	/usr/lib/gcc-snapshot/bin/gcc


*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;

/* 
	explicity specilization of class template  (full specilization)
		 
	match happens in the following order
		 Explicity specilization
		 partial specilization
		 prmary template
	
*/

#if TEST27
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;


template <typename T> class Kitty{ // primary template 
public:
  static void meow(){
	cout<<" kitty::Meow()!" <<endl;
  }
};

template <> class Kitty<double *>{ // template explicit specilazation. have to be exact match.
public:
  static void meow(){
	cout<<" template <> class Kitty<double *>" <<endl;
  }
};

template <typename X> class Kitty<X *>{ // template partial specilazation. will match any pointer
public:
  static void meow(){
	cout<< "<X> class Kitty<X *>" <<endl;
  }
};


int main(){
  Kitty<int>::meow();
  Kitty<double *>::meow();
  Kitty<const double *>::meow();
}

#endif

/* 
	explicity specilization of class template  (full specilization)
		 
	match happens in the following order
		 Explicity specilization
		 partial specilization
		 prmary template
	
*/

#if TEST28
/*
	shows partial specilization can lead to ambiguity in some cases which need to be resolved having another parital specilized template
  
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;


template <typename T,typename U> class Kitty{ };// primary template 
template <typename A,typename B> class Kitty<A*,B>{ };// partial specialization 
template <typename C,typename D> class Kitty<C,D*>{ };// partial specialization 
template <typename E,typename F> class Kitty<E*,F*>{ };// partial specialization  -- this is needed otherwise compile time error (Ambiguity) !!!!

int main(){
  Kitty<int*,int*> k ;
}

#endif


#if TEST29
/*
	explicit specializing of function template.
	There is no partial specilization possible of function template.!

     check how function specilization is different from function overloading.

*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

template <typename T> void meow(T){
  cout << "meow(T)"<<endl;
}
template <>void meow(long){
  cout << "meow(long ) with explicity specilization"<<endl;
}
void meow(long x){ //overloading the function. this is not the specilization of template.!
  cout << "meow(long) this is overloading of function"<<endl;
}
int main(){
  meow(111);
  meow(0L);
}

#endif


#if TEST30
/*
	explicit specializing of function template.
	There is no partial specilization possible of function template.!

     check how function specilization is different from function overloading.

*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

template <typename T> void meow(T){
  cout << "meow(T)"<<endl;
}
template <typename X>void meow(X* ){ // overload of a function above, not a partial specialization.
  cout << "meow(X* ) is an overload"<<endl;
}

int main(){
  meow(111);
  meow(0L);
  meow(static_cast<double *>(nullptr));
}

#endif


#if TEST31
/*
	explicit specializing of function template.
	There is no partial specilization possible of function template.!
	This one error outs!! trying to do a parital specialization

    Notice how function specilization is different from function overloading.

    error: function template partial specialization 'meow<X*>' is not allowed

	use type_tratis and helpers if you want to do something like this.
    or you can use classes as a wrapper to same function name and do the specilizatoin 
    in those classes


*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

template <typename T> void meow(){
  cout << "meow(T)"<<endl;
}
template <typename X>void meow<X*>(){ // overload of a function above, not a partial specialization.
  cout << "meow(X* ) is an overload"<<endl;
}

int main(){
  meow<int>();
  meow<long>();
  meow<double *>();
}

#endif


#if TEST32
/*
	explicit specializing of function template.
	There is no partial specilization possible of function template.!

    You can use classes as a wrapper to same function name and do the specilizatoin 
    in those classes

	Explicit instantiation of templates  ==> "templalte class meow<int>"; will spit out 
   code for meow<int> template even if it is not used.

	
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

template <typename T> class wrapper { // primary template 
public:
static void meow(){
  cout << "meow(T)"<<endl;
}
};
template <typename Z> class wrapper<Z*>{ //partial specilization
public:
  static void meow(){
	cout << "meow(T) specilization for pointers"<<endl;
  }
  

};

int main(){
  wrapper<int>::meow();
  wrapper<double *>::meow();
}

#endif

