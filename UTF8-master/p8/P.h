


#ifndef P_H
#define P_H

#include "U.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

class P : public U
{
public:
	
	// flags
	bool  m_readfileFlag;


	//Containers
	std::string	m_PropertiesFilename;

	mutable std::set<std::string> m_StringSetOccurrences;

	mutable std::string	 m_OutputStringAccumulate;

	std::vector<std::string> m_StringAccumulate;

	std::vector<std::string> m_StringCategories;

	std::vector<unsigned int> m_StringHexValues;

	mutable std::map<std::string, unsigned int> m_StringMapOccurrences;

	int state;


	// Constructors
	P() { m_readfileFlag = false; }

	P(const std::string properties_filename);

	P(const P & u_object);

	P & operator = (const P & u_object);

	operator bool() const;

	friend std::ostream& operator<< (std::ostream& stream, const P &other);

	~P() {}


	// Data
	void readfile(std::string  properties_filename);


	// Data query
	void LoadCategoryKeys(std::ifstream& ifstream);

	void LoadHexKeys(std::ifstream& ifstream);

	std::set<std::string> props() const;
	
	size_t count(const std::string & property_count) const;

	void count(const unsigned int codepoint) const;

	void Generateoccurence(const unsigned int code_point) const;

	void ResetMap() const;

	bool empty() const { if(!(props().empty())) { return false; } else { return true; } }

	size_t size() const { return props().size();  }

	void clear();





};

#endif