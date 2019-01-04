
#include "U.h"
using namespace std;

U::U() 
{

	// default constructor
	state = 1;
	m_OutputStringAccumulate = "";

}

U::U(string filename)
{

	// constructor
	readfile(filename);
}



U::~U() {
	// deconstructor
}




std::string U::operator[](int index) const
{

	return get(index);

}

U::operator bool() const
{
	if (!(m_StringAccumulate.empty()))
		return 1;
	else
		return 0;
}

U::U(const U & u_object) 
{
	//copy constructor

	m_OutputStringAccumulate = u_object.m_OutputStringAccumulate;

	m_PropertiesFilename = u_object.m_PropertiesFilename;

	m_StringAccumulate = u_object.m_StringAccumulate;

	// Several instances of this class must be able to co - exist, without interfering with each other.
	// Containers are easier!

	m_Keys = u_object.m_Keys;

}

U & U::operator = (const U & rhs)
{

	// assignment constructor

	// Several instances of this class must be able to co - exist, without interfering with each other.
	// Containers are easier!
	m_OutputStringAccumulate = rhs.m_OutputStringAccumulate;

	m_PropertiesFilename = rhs.m_PropertiesFilename;

	m_StringAccumulate = rhs.m_StringAccumulate;

	// Several instances of this class must be able to co - exist, without interfering with each other.
	// Containers are easier!

	m_Keys = rhs.m_Keys;

	return *this;

}

U & U::operator=(const std::string literal_data)
{
	
	this->clear();
	this->append(literal_data);
	return *this;

}

U U::operator+(const U & rhs) const
{
	U temp(*this);
	temp += rhs;
	return temp;
}


U & U::operator+=(const U & rhs) 
{
	for(auto i : rhs.m_StringAccumulate)
		this->append(i);

	return *this; 

}



bool U::operator==(const U & rhs) const
{    
	int count = 0;
	for (auto i : rhs.m_Keys)
	{
		if (i == this->m_Keys[count])
		{
			//	std::cout << "found: " << i << std::endl;
			count++;
		}
		else
		{

			return false;

		}

	}

	return true;
}

bool U::operator!=(const U & rhs) const
{
	if (!(*this == rhs))
		return true;
	else
		return false;

}

void U::readfile(string data_file) 
{

	std::ifstream ifstream(data_file);

	if (ifstream.fail()) 
	{

		throw string(" failed to open data file: " + data_file);

	}
	do
	{

	 ParseStream(ifstream);

	} while (!ifstream.eof());

	ifstream.close();

}

void U::append(const std::string literal_data)
{

	std::istringstream istringstream(literal_data);

	do
	{

		ParseStream(istringstream);

	} while (!istringstream.eof());


}


void U::clear()
{


	m_PropertiesFilename.clear();

	m_OutputStringAccumulate.clear();
	
	m_OutputStringAccumulate = "";

	m_StringAccumulate.clear();

	m_Keys.clear();


}

void U::ParseStream(std::istream &istream)
{

	char symbol[5];

	symbol[0] = istream.get();
	

	if ((symbol[0] & 0b10000000) == 0b00000000) 
	{
		///* already have first bit*/

		short shift_one = symbol[0] & 0xff;


		///*create strings */
		symbol[1] = '\0';
	

		m_StringAccumulate.push_back(symbol);

		m_Keys.push_back(shift_one);



		//cout << endl;
		//cout << "bit1 " << endl;
		//cout << "symbol " << symbol << endl;
		//cout << "shift_one " << shift_one << endl;

	}
	else if ((symbol[0] & 0b11100000) == 0b11000000) 
	{


		symbol[1] = istream.get();
		if (istream.fail())		{
			throw string("invalid byte sequence ");
		}

		short shift_one = symbol[0] & 0xff;

		short shift_two = symbol[1] & 0xff;

		shift_one = shift_one & 0b00111111;
		shift_two = shift_two & 0b01111111;

		shift_one = shift_one << 6;
		shift_one = shift_one | shift_two;
		
	
		///*create strings*/
		symbol[2] = '\0';
	
		m_StringAccumulate.push_back(symbol);

		m_Keys.push_back(shift_one);


		//cout << endl;
		//cout << "bit2 " << endl;
		//cout << "symbol " << symbol << endl;
		//cout << "shift_one " << shift_one << endl;
	}
	else if ((symbol[0] & 0b11110000) == 0b11100000) 
	{


		symbol[1] = istream.get();
	
		if (istream.fail())		{
			throw string("invalid byte sequence");
		}
	
		symbol[2] = istream.get();

		if (istream.fail())		{
			throw string("invalid byte sequence");
		}

		short shift_one = symbol[0] & 0xff;
		
		short shift_two = symbol[1] & 0xff;

		short shift_three = symbol[2] & 0xff;

		shift_one = shift_one & 0b00011111;

		shift_two = shift_two & 0b01111111;

		shift_three = shift_three & 0b01111111;

		shift_one = shift_one << 12;

		shift_two = shift_two << 6;

		shift_one = shift_one | shift_two | shift_three;
	

	
		 ///*create strings*/
		symbol[3] = '\0';

		m_StringAccumulate.push_back(symbol);

		m_Keys.push_back(shift_one);

		//cout << endl;
		//cout << "bit3 " << endl;
		//cout << "symbol " << symbol << endl;
		//cout << "shift_one " << shift_one << endl;

	}
	else if ((symbol[0] & 0b11111000) == 0b11110000) 
	{


		symbol[1] = istream.get();

		if (istream.fail())		{
			throw string("invalid byte sequence");
		}

		symbol[2] = istream.get();

		if (istream.fail())		{
			throw string("invalid byte sequence");
		}

		symbol[3] = istream.get();

		if (istream.fail())		{
			throw string("invalid byte sequence");
		}

		int shift_one = symbol[0] & 0xff;

		int shift_two = symbol[1] & 0xff;

		int shift_three = symbol[2] & 0xff;

		int shift_four = symbol[3] & 0xff;

		shift_one = shift_one & 0b00001111;

		shift_two = shift_two & 0b01111111;

		shift_three = shift_three & 0b01111111;

		shift_four = shift_four & 0b01111111;

		shift_one = shift_one << 18;

		shift_two = shift_two << 12;

		shift_three = shift_three << 6;

		shift_one = shift_one | shift_two | shift_three | shift_four;
		

		symbol[4] = '\0';

		m_StringAccumulate.push_back(symbol);

		m_Keys.push_back(shift_one);

		//cout << endl;
		//cout << "bit4 " << endl;
		//cout << "symbol " << symbol << endl;
		//cout << "shift_one " << shift_one << endl;

	}

}

int U::front()
{
	if (this->m_Keys.empty())
		throw std::string("error codepoint is empty");
	return m_Keys.front();
}

int U::back()
{
	if (this->m_Keys.empty())
		throw std::string("error codepoint is empty");
	return m_Keys.back();
}






std::string U::get() const {
	// const for constant objects
	m_OutputStringAccumulate = "";
	for (unsigned int i = 0; i < m_StringAccumulate.size(); i++) {
		m_OutputStringAccumulate += m_StringAccumulate[i];
	}
	return m_OutputStringAccumulate;
}


std::string U::get(unsigned int index) const {
	// const for constant objects
	m_OutputStringAccumulate = "";
	if (!(index >= m_StringAccumulate.size())) {
		m_OutputStringAccumulate = m_StringAccumulate[index];
		return m_OutputStringAccumulate;
	}
	else {
		throw string("invalid index");
	}
}

std::string U::get(unsigned int start_index, unsigned int end_index) const {
	// const for constant objects
	if (start_index > end_index) {
		throw string("invalid interval");
	}
	m_OutputStringAccumulate = "";
	if (!(end_index == 0 || end_index >= m_StringAccumulate.size() + 1 || start_index >= m_StringAccumulate.size() + 1)) {
		for (unsigned int i = start_index; i <= end_index - 1; i++) {
			m_OutputStringAccumulate += m_StringAccumulate[i];
		}
		return m_OutputStringAccumulate;
	}
	else {
		throw string("invalid interval");
	}

}

int U::codepoint(const unsigned int index) const
{

	if (!(index >= m_Keys.size()))
	{
		return m_Keys[index];	
	}
	else
	{

		throw string("invalid index");

	}
	

}

U U::operator+(const char * literal_data) const
{
	U temp;
	temp.append(literal_data);
	return *this + temp;

}

U operator+(const char * literal_data, const U & rhs)
{
	U temp;
	temp.append(literal_data);
	return temp + rhs;
}

U & U::operator+=(const std::string literal_data)
{
	U temp;
	temp.append(literal_data);

	return *this += temp;

}

bool U::operator==(const char * literal_data) const
{
	U temp;
	temp.append(literal_data);

	if (*this == temp)
		return true;
	else
		return false;
	
}


bool operator==(const char * literal_data, const U & rhs)
{
	U temp;
	temp.append(literal_data);

	if (rhs == temp)
		return true;
	else
		return false;
}


bool U::operator!=(const char * literal_data) const
{
	U temp;
	temp.append(literal_data);

	if (*this != temp)
		return true;
	else
		return false;

}

bool operator!=(const char * literal_data, const U & rhs)
{
	U temp;
	temp.append(literal_data);

	if (rhs != temp)
		return true;
	else
		return false;
}


std::ostream & operator<<(std::ostream & stream, const U & other)
{
	stream << other.get();
	return stream;
}
