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
#define TEST1 1 

#if TEST1
// To resolve an unqualified function call try search in the namespace where the function argument lives in  this is called ADL
int main(){
	/* where does compiler finds the function operator<< ? */
	operator<<(std::cout,"hello world\n"); // how is operator resolve here its through to "argument dependent lookup" (ADL).
}
#endif

#if TEST2
/*
This test demonstrate the Template specialization and the name lookup when namespace is present .
*/

template <typename T> struct meow {
	void purr(){
		puts("meow<T> purr()\n");
	}
};

template <> struct meow<int> {
	void purr(){
		puts("meow<int> purr()\n");
	}
};
int main(){
	meow<long> l;
	l.purr();

	meow<int> i;
	i.purr();

}
#endif

#if TEST3
/*
This test demonstrate the Template specialization and the name lookup when namespace is present .
*/
namespace Foo{
	template <typename T> struct meow {// primary template
		void purr(){
			puts("Foo::meow<T> purr()\n");
		}
	};

	template <> struct meow<int> { // explicity specialization template
		void purr(){
			puts("Foo::meow<int> purr()\n");
		}
	};
}
int main(){
	using Foo::meow; // dragging just "the name" don't care abou the implementation.
	meow<long> l;
	l.purr();

	meow<int> i;
	i.purr();

}
#endif



#if TEST4
/*
This test demonstrate the Template specialization and the name lookup when namespace is present .
*/
namespace Foo{
	namespace Bar{
		template <typename T> struct meow { // primary template
			void purr(){
				puts("Foo::Bar::meow<T> purr()\n");
			}
		};

		template <> struct meow<int> { // explicity specialization template
			void purr(){
				puts("Foo::Bar::meow<int> purr()\n");
			}
		};
	}
	using Bar::meow; // dragging in the meow from Bar namespace to Foo namespace
}

int main(){

	using Foo::meow; // dragging just "the name" don't care abou the implementation.
	meow<long> l;
	l.purr();

	meow<int> i;
	i.purr();

}
#endif

#if TEST5
/*
This test demonstrate the Template specialization and the name lookup when namespace is present .
*/
namespace Foo{
	namespace Bar{
		template <typename T> struct meow { // primary template
			void purr(){
				puts("Foo::Bar::meow<T> purr()\n");
			}
		};


	}
	using Bar::meow; // dragging in the meow from Bar namespace to Foo namespace
}
template <> struct Foo::meow<int> { // explicity specialization template :: This must know where the primary template is living so the qualificaiton Foo:: is coming from
	void purr(){
		puts("Foo::Bar::meow<int> purr()\n");
	}
};
int main(){

	using Foo::meow; // dragging just "the name" don't care abou the implementation.
	meow<long> l;
	l.purr();

	meow<int> i;
	i.purr();

}
#endif


#if TEST6
/*
This test demonstrate the Argument dependent lookup  when namespace is present .


*/
namespace Foo{
	namespace Bar{
		struct meow {};
		void purr(const meow & x){
			puts("Foo::Bar::purr()\n");
		}
	}
	using Bar::meow; // dragging in the meow from Bar namespace to Foo namespace
}

int main(){

	Foo::Bar::meow m; // dragging just "the name" don't care abou the implementation.
	purr(m); // HOW DOES COMPILER KNOW WHERE purr lives? its not a part of std:: its not a part of global namespace !!. its checks it in the namespace of the argument (ADL). here namespace where meow lives

}
#endif


#if TEST7
/*

This test demonstrate the Argument dependent lookup limitation when namespace is present.
-- ADL only search only "True name space" of argument not in NS where argument type appears to live. This is by design not a bug
-- this will not compile
*/
namespace Foo{
	namespace Bar{
		struct meow {};
	}
	using Bar::meow; // dragging in the meow from Bar namespace to Foo namespace so that meow appear to live in Bar namespace.
	void purr(const meow & x){
		puts("Foo::purr()\n");
	}
}

int main(){
	Foo::Bar::meow m; // dragging just "the name" don't care abou the implementation.
	purr(m); // HOW DOES COMPILER KNOW WHERE purr lives? its checks it in the namespace (true NameSpace) of the argument m which is Bar. here namespace where meow lives

}
//time for the test http://www.gotw.ca/gotw/030.htm
#endif


