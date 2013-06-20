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
#define TEST35 1 


/*
==================== PART 6 ==================================================================================================
======================================C++ 11 Features==================================================================
* Some of the snippet does not work with gcc 4.6 need to use gcc 4.7 or higher
   in ubuntu use "sudo apt-get install gcc-snapshot"
   than you can use the experimental version of gcc 4.8 located at 	/usr/lib/gcc-snapshot/bin/gcc
   Feature explained.
		1) Raw String. Anything between R"(this is a raw string \n\t )"
		2) explicit keyword (http://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean)
		3) template function defaults
        4) constructor delegation - constructor calling constructor meow(): meow(122,114,3.14,"abc"){ }
        5) uniform initilizatoin list 



unique_ptr
shared_ptr
make_shared



*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;

/* 
	How to make your UDC (user defined conversion) more Robust and safe.
		conside the code below it convert the smartPtr to bool but it will create
		lot of problem like cout << p * 1777 <<endl; will also compile if you dont use explicit keyword.
		use explicity keyword for only doing the conversion of smartPtr to bool in explicit cases.
		like bbool b(p);
 		
		
	
	
*/

#if TEST33
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

class smartPtr{
public:
   explicit operator bool()const { // UDC //use explicit keyword before operator to make the conversion more strict.
	return true;
  }
};

int main(){
  smartPtr p;
  bool b(p); // still  work fine with explicit convesion specific before operator
  bool x = p; // should error out with explicit keyword
  cout << p * 1777 <<endl; // will fail if explicit is specified 
  if(p){ //  still  work fine
	cout <<"true !"<<endl;
  }else{
	cout <<"false !"<<endl;
  }
}

#endif

/* 
	
Default template argument for functions.

    following works fine. its is use of default in class 
	template <typename X=int> class myclass{
	}
	template <typename T=int> void func(const T& t){} // will not work in C++ 98 should work in c++11

*/

#if TEST34
/*
*/
#include <ostream> 
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
#include <vector>
using namespace std;

template <typename C > void sort (C& c){
  sort(c.begin(),c.end());
}
template <typename C, typename f > void  sort (C& c, f F){ //overload with a functor
  sort(c.begin,c.end(),F);
}
template <typename C> void print(C &c){
  for (auto& e :c ){
	cout << e << " " ;
  }
  cout<<endl;	
}
int main(){
  vector<int> v;
  v.push_back(10);
  v.push_back(1);
  v.push_back(2);
  v.push_back(110);
  sort(v);
  print(v);


}

#endif
/* 
	
Use case of Default template argument for functions.

	template <typename T=int> void func(const T& t){} // will not work in C++ 98 should work in c++11

*/

#if TEST35
/*
*/
#include <ostream> 
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
#include <vector>
using namespace std;

// use of default in the template
template <typename C,typename F = less<typename C::value_type>> void sort (C &c, F f = F()){
  sort(c.begin(),c.end(),f);
 }
template <typename C> void print(C &c){
  for (auto& e :c ){
	cout << e << " " ;
  }
  cout<<endl;	
}
/*
template <typename C > void sort (C& c){
  sort(c.begin(),c.end());
}
template <typename C, typename f > void  sort (C& c, f F){ //overload with a functor
  sort(c.begin,c.end(),F);
}
*/
int main(){
  vector<int> v;
  v.push_back(10);
  v.push_back(1);
  v.push_back(2);
  v.push_back(110);

  sort(v);
  print(v);
  sort(v,greater<int>());
  print(v);

}

#endif

