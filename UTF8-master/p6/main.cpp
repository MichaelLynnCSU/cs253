#include "U.h"
#include "P.h"
#include <iostream>
using namespace std;


int main() {
	
	cout << endl << endl;
	//------------------------------------ Compile------------------------------------------------------>

	try {
		cout << "Testcase: Compile " << endl;

		std::cout << "Compile Success" << '\n';

		cout << endl << endl;
	}
	catch (const string &msg) {
		cout << "I expected this: " << msg << '\n';
	}

	cout << endl << endl;

	//----------------------------------main #1-------------------------------------------------------->

	try {
		cout << "Testcase: main #1 " << endl;

		// Test for default constructor and propcount method

		U u;
		P p;
	
		p.readfile("/s/bach/a/class/cs253/pub/UnicodeData.txt");
		u.readfile("story2.txt");	
	

		for (int i = 0; i<u.size(); i++)
			p.count(u.codepoint(i));

		cout << "Cc: " << p.count("Cc") << '\n';
	}
	catch (const string &msg) {
		cout << "I expected this: " << msg << '\n';
	}

	cout << endl << endl;

	//------------------------------------ main #2------------------------------------------------------>

	try {
		cout << "Testcase: main #1 " << endl;

		const string propFile = "UnicodeDataV2.txt";

		// Test for Copy Constructor and get method with two arguments

		U u;
		P p;
		P p2 = p;
		U u1 = u;
		u1.readfile("story.txt");
		p2.readfile(propFile);
		cout << "Get: " << u1.get(23, 46) << '\n';

	}
	catch (const string &msg) {
		cout << "I expected this: " << msg << '\n';
	}

	cout << endl << endl;




	//------------------------------------ main #2------------------------------------------------------>

	try {
		cout << "Testcase: main #2 " << endl;

		const string pub = "/s/bach/a/class/cs253/pub/";   // ~ only works in shells
		const string readfile = "data1";
		const string readfile1 = "data2";

		// Test for Assignment operator
		// Testing Data accumulation in readfile
		// Testing get method get method without argument  

		U u;
		U u2;
		P p;
		P p2;
		
		for (int i = 0; i<u.size(); i++)
			p.count(u.codepoint(i));

		u2 = u;	
		p2 = p;

		u2.readfile(readfile);
		u2.readfile(readfile1);
		p2.readfile(pub + "UnicodeData.txt");
		cout << "Get: " << u2.get() << '\n';
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << std::endl;
	}
	cout << endl << endl;


	//------------------------------------ main #3------------------------------------------------------>

	try {
		cout << "Testcase: main #3 " << endl;

		// Testing for get method with a single argument with a different property file

		U u;
		P p;

		p.readfile("UnicodeDataV2.txt");
		u.readfile("story.txt");
		cout << "Get: " << u.get(50) << '\n';
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << std::endl;
	}
	cout << endl << endl;

	//------------------------------------ main #4------------------------------------------------------>


	try {

		const string propFile = "UnicodeDataV2.txt";

		cout << "Testcase: main #4 " << endl;	
		
		// Error check for invalid range arguments in get method

		U u1;
		P p1;
		u1.readfile("story.txt");
		p1.readfile(propFile);



		u1.get(-1, 4); // Error check for invlid argument
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << std::endl;
	}

	cout << endl << endl;

	//------------------------------------ main #5------------------------------------------------------>

	try {
		cout << "Testcase: main #5 " << endl;

		const string pub = "/s/bach/a/class/cs253/pub/";   // ~ only works in shells

		// Error check for invalid single argument

		U u2;
		P p2;

		u2.readfile("data1");
		p2.readfile(pub + "UnicodeData.txt");
		u2.get(8828636); // Error statement for invlid argument
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	//------------------------------------ main #6------------------------------------------------------>

	try {
		cout << "Testcase: main #6 " << endl;


		// Error check for bad readfile

		U u3;
		u3.readfile("blah.txt");
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}
	//u3.propfile(pub+"UnicodeData.txt");
	//cout << "Get: " << u3.get(90) << '\n';

	cout << endl << endl;

	//------------------------------------ main #7------------------------------------------------------>
	try {
		cout << "Testcase: main #7 " << endl;

		const string readfile = "all_range";

		// Error check for invalid property file

		U u4;
		P p4;
		u4.readfile(readfile);

		p4.readfile("UnicodeData.txt");
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}


	cout << endl << endl;

	//------------------------------------ main #8------------------------------------------------------>

	try {

		cout << "Testcase: main #8 " << endl;

		const string pub = "/s/bach/a/class/cs253/pub/";   // ~ only works in shells

		// Testing with test constructor and size method

		P p;
		p.readfile(pub + "UnicodeData.txt");
		U u;
		u.append("就这样银银的头发变成了银色");
		
		for (int i = 0; i<u.size(); i++)
			p.count(u.codepoint(i));

		cout << "Size: " << u.size() << '\n'
			<< "PropCount: " << p.count("Ll") << '\n'
			<< "Get: " << u.get(3, 5) << '\n';


	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}


	cout << endl << endl;


	//------------------------------------ main #9------------------------------------------------------>
	
	const string pub = "/s/bach/a/class/cs253/pub/";   // ~ only works in shells

	try {

		cout << "Testcase: main #9 " << endl;


		// Testing for props() method and invlaid propcount   

		P p;
		p.readfile(pub + "UnicodeData.txt");
		U foo;
		foo.append("3xyz + 3xy2z - 0.1xz - 200y + 0.5");

		for (int i = 0; i<foo.size(); i++)
			p.count(foo.codepoint(i));

		cout << "insane: " << p.count("insane") << '\n';


		for (const auto &p : p.props())
			cout << "Property: " << p << '\n';

	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;


	//------------------------------------ main #10------------------------------------------------------>

	try {
		cout << "Testcase: main #10 " << endl;

		// Testing destructor

		U *u = new U();
		u->~U();
		cout << "Testing destructor Passed" << '\n';

	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}


	cout << endl << endl;

	//------------------------------------ main #11------------------------------------------------------>

	try {
		cout << "Testcase: main #11 " << endl;
		// Testing for constant argument in readfile 

		U foo;
		const string filename = "data1";
		foo.readfile(filename);
		cout << "Testing for constant argument in readfile Passed" << '\n';
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	//------------------------------------ main #12------------------------------------------------------>

	try {
		cout << "Testcase: main #12 " << endl;
		U foo;
		P p;
		const string filename = "UnicodeDataV2.txt";
		p.readfile(filename);
		cout << "Testing for constant argument in propfile Passed" << '\n';

	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	//------------------------------------ main #13------------------------------------------------------>

	try {
		cout << "Testcase: main #13 " << endl;

		// Testing for constant argument in copy constructor and assignment operator

		const U foo;
		U u1 = foo;

		cout << "Testing constant argument in copy constructor Passed" << '\n';

		U u2;
		u2 = foo;

		cout << "Testing constant argument in assignment operator Passed" << '\n';

	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	////------------------------------------ main #14------------------------------------------------------>

	try {
		cout << "Testcase: main #14 " << endl;

		// Testing for error for invalid byte sequence  
		//Testcase - 21
		//	---------------- -
		//	Throws: Invalid initial UTF - 8 byte encountered(Similar std::string)
		//Based on these rules, there are two things which can go wrong and make the UTF - 8 invalid:

		// a continuation byte is encountered at a point where a start byte is expected
		// there was a start byte indicating more continuation bytes then followed

		U foo;
		foo.readfile("error");
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	//------------------------------------ main #15------------------------------------------------------>

	try {

		cout << "Testcase: main #15 " << endl;

		const string pub = "/s/bach/a/class/cs253/pub/";   // ~ only works in shells

		// Testing for constant methods

		P p;
		p.readfile(pub + "UnicodeData.txt");
		U foo;
		foo.append("3xy + 0.2xz - 100y + 0.7");

			for (int i = 0; i<foo.size(); i++)
				p.count(foo.codepoint(i));

		cout << "Size " << foo.size() << '\n';
		cout << "Get(): " << foo.get() << '\n';
		cout << "Get(4): " << foo.get(4) << '\n';
		cout << "Get(3, 5): " << foo.get(3, 5) << '\n';
		cout << "Nd: " << p.count("Nd") << '\n';
		for (const auto &p : p.props())
			cout << "Property: " << p << '\n';


	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	////------------------------------------ main #16------------------------------------------------------>

	try {
		cout << "Testcase: main #16 " << endl;

		// Testing for partially mutibyte UTF-8 Sequence 
		U foo;

		foo.readfile("error2");
	}
	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	////------------------------------------ main #17------------------------------------------------------>

	try {

		cout << "Testcase: main #17 " << endl;

		const string pub = "/s/bach/a/class/cs253/pub/";   // ~ only works in shells
		const string propFile = "UnicodeDataV2.txt";
		const string readfile = "data1";

		// Test for checking several instance of class must be able to co-exist 

		U u;
		P p;

		p.readfile(propFile);
		u.readfile(readfile);

		for (int i = 0; i<u.size(); i++)
			p.count(u.codepoint(i));

		cout << "Cc: " << p.count("Cc") << '\n';

		U u1;
		P p1;
		p1.readfile("UnicodeDataV4.txt");
		u1.readfile("data2");

		for (int i = 0; i<u1.size(); i++)
			p1.count(u1.codepoint(i));

		cout << "Cc: " << p1.count("Cc") << '\n';



	}

	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	//------------------------------------ valgrind------------------------------------------------------>

	try {
		cout << "Testcase: valgrind " << endl;
		cout << "implement" << endl;


	}

	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}

	cout << endl << endl;

	//------------------------------------ hamlet------------------------------------------------------>
	try {
		cout << "Testcase: hamlet #1 " << endl;

		// Test hamlet property count

		U u;
		P p;

		p.readfile("/s/bach/a/class/cs253/pub/UnicodeData.txt");
		u.readfile("hamlet.txt");


		for (int i = 0; i < u.size(); i++)
			p.count(u.codepoint(i));

		for (string i : p.props()) 
		{
			cout << "Property : " << i;
			cout << " " << p.count(i.c_str()) << endl;
		}
	}

	catch (string caught)
	{
		cout << "Throws: " << caught << endl;
	}


}


