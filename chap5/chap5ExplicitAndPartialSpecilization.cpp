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
#define TEST26 1 


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

