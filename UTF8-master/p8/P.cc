

#include "P.h"

using namespace std;



P::P(const string properties_filename)
{
	m_readfileFlag = false;
	readfile(properties_filename);
	state = 1;

}

P::P(const P & u_object)
{
	//copy constructor
	// Several instances of this class must be able to co - exist, without interfering with each other.
	// Containers are easier!

	// flags
	m_readfileFlag  =  u_object.m_readfileFlag;


	//Containers

	m_StringCategories = u_object.m_StringCategories;

	m_StringSetOccurrences = u_object.m_StringSetOccurrences;
	
	m_OutputStringAccumulate = u_object.m_OutputStringAccumulate;
	
	m_StringAccumulate = u_object.m_StringAccumulate;
	
	m_PropertiesFilename = u_object.m_PropertiesFilename;

	m_StringMapOccurrences = u_object.m_StringMapOccurrences;

	m_StringHexValues = u_object.m_StringHexValues;

}

P & P::operator=(const P & u_object)
{
	// assignment constructor

	// Several instances of this class must be able to co - exist, without interfering with each other.
	// Containers are easier!
	// Several instances of this class must be able to co - exist, without interfering with each other.
	// Containers are easier!

	// flags
	m_readfileFlag = u_object.m_readfileFlag;

	//Containers

	m_StringCategories = u_object.m_StringCategories;

	m_StringSetOccurrences = u_object.m_StringSetOccurrences;

	m_OutputStringAccumulate = u_object.m_OutputStringAccumulate;

	m_StringAccumulate = u_object.m_StringAccumulate;

	m_PropertiesFilename = u_object.m_PropertiesFilename;

	m_StringCategories = u_object.m_StringCategories;

	m_StringHexValues = u_object.m_StringHexValues;

	m_StringMapOccurrences = u_object.m_StringMapOccurrences;

	m_StringHexValues = u_object.m_StringHexValues;

	return *this;
	
}

P::operator bool() const
{
	if (!(m_StringCategories.empty()))
		return 1;
	else
		return 0;
}


void P::readfile(string  properties_filename)
{


	///*load the hex and cat values*/


	ifstream ifstream(properties_filename);

	if (ifstream.fail())
	{

		throw string("failed to open property file " + properties_filename);

	}
	else if (!(m_StringCategories.empty()))
	{

		throw string("undefined behavior");

	}
	else
	{
		m_readfileFlag = true;

		m_PropertiesFilename = properties_filename;

		LoadCategoryKeys(ifstream);

		ifstream.clear();

		///*reuse stream */

		ifstream.seekg(0, std::ios::beg);

		LoadHexKeys(ifstream);

		ifstream.close();

	}

}

void P::LoadCategoryKeys(std::ifstream& ifstream)
{


	///* map the properties to a integer init to 0*/
	string category_data = "";

	do
	{
		getline(ifstream, category_data);

		if (!(category_data.empty()))
		{

			size_t category_position = 0;

			for (unsigned int i = 0; i < 3; i++)
			{
				///*find target location*/
				category_position = category_data.find(';', category_position);

				if (category_position != std::string::npos)
				{

					category_position += 1;

				}

			}

			category_data = category_data.substr(category_position - 3, 2);

			m_StringCategories.push_back(category_data);

			m_StringMapOccurrences[category_data] = 0;

		}

	} while (!ifstream.eof());

}

void P::LoadHexKeys(std::ifstream& ifstream)
{

	///* create integer hex key*/
	string hex_data = "";

	do
	{
		getline(ifstream, hex_data);

		if (!(hex_data.empty()))
		{
			///* find target location*/
			size_t category_position = hex_data.find(';');

			hex_data = hex_data.substr(0, category_position);

			int hexkey = strtol(hex_data.c_str(), NULL, 16);

			m_StringHexValues.push_back(hexkey);

		}

	} while (!ifstream.eof());

}

std::set<string> P::props() const
{

	///*const for constant objects*/
	for (auto i : m_StringCategories)
	{

		m_StringSetOccurrences.insert(i);

	}

	return m_StringSetOccurrences;
}

void P::count(const unsigned int codepoint) const
{ 
	
	
	if (!(m_readfileFlag))
		{

			throw string("undefined behavior");
	
		}
	 else
	 {

		 Generateoccurence(codepoint);

	 }
}

size_t P::count(const std::string & property_target) const
{
	///*check for valid */
	if (!(m_StringMapOccurrences[property_target] == 0))
	{

		return m_StringMapOccurrences[property_target];

	}
	else
	{

		return 0;

	}

}

void P::Generateoccurence(const unsigned int code_point) const
{
		int count = 0;

		for (auto j : m_StringHexValues)
		{
			if (code_point == j)
			{
				///*	 increase key value*/
				//		cout << " key " << i << " value " << j << endl;
				m_StringMapOccurrences[m_StringCategories[count]]++;

				break;
			}

			count++;

		}


	
}

void P::ResetMap() const
{
	for (auto &i : m_StringMapOccurrences)
	{

		i.second = 0;

	}

}

void P::clear()
{

	// flags
	m_readfileFlag = false;


	//Containers

	m_PropertiesFilename.clear();

	m_StringSetOccurrences.clear();

	m_OutputStringAccumulate.clear();

	m_StringAccumulate.clear();

	m_StringCategories.clear();

	m_StringHexValues.clear();

	m_StringMapOccurrences.clear();


}

std::ostream & operator<<(std::ostream & stream, const P & other)
{
	for (string i : other.props())
				{
		stream << i << ": ";
		stream <<  other.count(i.c_str()) << " ";
				}
	return stream;
}
