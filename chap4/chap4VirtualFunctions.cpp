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
#define TEST26 1 


/*
==================== PART 4 ==================================================================================================
======================================Virtual Functions==================================================================
* Some of the snippet does not work with gcc 4.6 need to use gcc 4.7 or higher
   in ubuntu use "sudo apt-get install gcc-snapshot"
   than you can use the experimental version of gcc 4.8 located at 	/usr/lib/gcc-snapshot/bin/gcc

   * changed the makefile to take gcc from /usr/lib/gcc-snapshot/bin/gcc. (4.7 or higher) 


	* inherentence is usually overused. compiler use vptr and vtable to implement the virtual function mechanism
	* inhertence is not the only way you can achieve code reuse.!!
	* Remember inheretence create tight coupling between base and derived class. Relationship between the base and the derived
	  class is second closest which can happen in C++. the most closest is the friendship in which class knows everything about
	  the other class
    * Remember object oriented programming is "to use object to encapsulate state and behaviour"

	* Every class have its static type and dynamic type.

	* REMEMBER VIRTUAL FUNCTION MECHANISM IS BASED ON RUNTIME AND COMPLETELY INDEPENDENT WITH THE COMPILE TIME ACCESS SPECIFIER SO YOU CAN 
      EVEN SPECIFY THE PRIVATE SPECIFIER IN THE DERIVED CALSS FOR THE VIRTUAL FUNTION AND STILL DERIVED FUNCTION WILL BE ACCESSIBLE. 
      ACCESS CONTROL CHECK IS APPLIED STATICALLY 
	

*/
#include <vector> // puts vector in std namespace
#include <algorithm> // puts sort in std namespace
#include <ostream>
#include <iostream>
using namespace std;

#if TEST23
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;


class Base {
public: // you need meow to be public before using it as p->meow(); in dervied class meow can be private virtual.
  void virtual  meow(){ // "virtual is must" to indicate that take the dyanmic type of the object in consideration beforing selecting the imlementation
	cout <<"Base" <<endl;
  }
};
class Derived :public Base {
private : // being private Does not have effect on  what meow() is choosen !! REMEMBER VIRTUAL FUNCTION MECHANISM IS RUNTIME AND COMPLETE INDEPENDENT WITH THE COMPILE TIME ACCESS SPECIFIER
  void virtual meow(){
	cout <<"Derived" <<endl;
  
  }
};
class MoreDerived : public Derived {};



int main(){
  Base *p = new MoreDerived();
  // if meow() is virtual the implementation is choosen based on dynamic type of p.
  // if meow is non virtual the implementation to execute is choosen based on static type of *p
  p->meow(); // static type of *p is Base (what compiler sees). dynamic type of *p is derived.

}

#endif
/* 
	understanding slicing and how to avoid that. ==> make the copy constructor private;
	understanding the memory leak which can be caused by non virtual Destructors ; make destructor virtual

*/

#if TEST24
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

class Base {
  int b;
public:
  virtual ~Base(){ cout<< "base Destructor" <<endl;}; // virtual destructors is needed. correct destructor get called. when you delete basep pointing to derived; otherwise you will leak derived part in the class
  Base(){}
private : 
  Base (const Base &){} // make the copy constructor private to avoid the slicing. compiler will not generate the default copy constructor in this case
};
// derived become copyable !!!.
class Derived :public Base {
  int d;
public:
  Derived(){}
  ~Derived(){  cout<< "Derived Destructor" <<endl;}
};


int main(){
  Base *p = new Derived();
  //  Base b2 = *p; // the implicit generated copy constructor will slice the object. Will  Only copy over the base class memeber to b2.So make the copy constructor private to error out at compile time
  delete p;
}

#endif
/* 
   	demonstrate use of shared pointer to avoid memory leaks
	demonstrate the masking of virtual function when the parameters are different.
		you should always use same signature for the virtual functions in the hierarchy down the chain to avoid the masking.

	C++ 11 have two context sensitive keyword. override and final.
    use override keyword for compiler to erroring out indicating the programmer when the masking is happening. [ C++ 11 feature]
    use final to avoid derivation of class. lock down the class 
	
*/

#if TEST25
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

class Shape {
  int b;
public:
  virtual void draw(int x,int y){
	cout << "inside Shape::draw" << "x:" << x << "y:" << y <<endl;
  }
  virtual ~Shape(){ cout<< "Shape Destructor" <<endl;}; // virtual destructors is needed. correct destructor get called. when you delete basep pointing to derived; otherwise you will leak derived part in the class
  Shape(){}
private :
  Shape (const Shape &){} // make the copy constructor private to avoid the slicing. compiler will not generate the default copy constructor in this case
};

class Polygon :public Shape {
  int d;
public:
  Polygon(){}
  virtual void  draw(int x,int y) override { // c++ 11 feature. no effect here but if you put it in Evilgon draw it will give a compile error to indicate there is a problem in code.
	cout << "inside Polygon::draw" << " x:" << x << " y: " << y <<endl;
  }
  ~Polygon(){  cout<< "Polygon  Destructor" <<endl;}
};
class Evilgon :public Shape {
  int d;
public:
  Evilgon(){}
  virtual void draw(double x,double  y)  { // NOTICE THE ARGUMENTS HERE.  // NO overriding happens as the argument are different 
	cout << "inside Polygon::draw" << " x: " << x << " y: " << y <<endl;
  }
  ~Evilgon(){  cout<< "Evilygon  Destructor" <<endl;}
};

int main(){
  shared_ptr<Shape> shape = make_shared<Polygon>(); // shared ptr to avoid memory leak
  shape->draw(11,22);
  shape = make_shared<Evilgon>();
  shape->draw(33,22);

}

#endif

/* 
   	Demonstrate NVI (Non Virtual interface) Ideam. Kind of design pattern to structure your code such that user of the class
    only uses non virtual interfaces of the base class but base class internally can use the virtual mechanism to do work in
    it functions.

	
*/

#if TEST26
/*
*/
#include <ostream>
#include <iostream>
#include <string>
#include <memory> // for shared_ptr
using namespace std;

class Shape {
  int b;
public:
  void draw(int x,int y){ // NOTE: This is an non virtual function 
	cout<< " NVI starts here" <<endl;
	do_draw(x,y);
	cout<< " NVI ends here" <<endl;
  }
  virtual ~Shape(){ cout<< "Shape Destructor" <<endl;}; // virtual destructors is needed. correct destructor get called. when you delete basep pointing to derived; otherwise you will leak derived part in the class
  Shape(){}
protected : //notice protected so that derived can access the fucntion.
  virtual void do_draw(int x,int y){
	cout << "inside Shape::draw" << "x:" << x << "y:" << y <<endl;
  }
private :
  Shape (const Shape &){} // make the copy constructor private to avoid the slicing. compiler will not generate the default copy constructor in this case
};

class Polygon :public Shape {
  int d;
public:
  Polygon(){}
  ~Polygon(){  cout<< "Polygon  Destructor" <<endl;}
private:
  virtual void  do_draw(int x,int y){ // c++ 11 feature. no effect here but if you put it in Evilgon draw it will give a compile error to indicate there is a problem in code.
    Shape::do_draw(x,y); //QUALIFICATION OF FUCNTION NAME OVERRIDES THE VIRTUAL MECHANISM. do_draw() in base should be protected or public.
	cout << "inside Polygon::draw" << " x:" << x << " y: " << y <<endl;
  }

};


int main(){
  shared_ptr<Shape> shape = make_shared<Polygon>(); // shared ptr to avoid memory leak
  shape->draw(11,22);
}

#endif

