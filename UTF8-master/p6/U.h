
#ifndef U_H
#define U_H

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


class U
{
public:

	//Containers

	std::string	 m_PropertiesFilename;

	mutable std::string	 m_OutputStringAccumulate;

	std::vector<std::string> m_StringAccumulate;

	std::vector<unsigned int>	m_Keys;



	// Constructors
	U();

	U(const std::string filename);

	U(const U & u_object);

	U & operator = (const U & u_object);

	~U();

	// Data 
    void readfile(std::string data_file);

	void append(std::string literal_data);

	// Data query
	
	int size() const { return m_StringAccumulate.size(); }

	std::string  get() const;

	std::string  get(unsigned int index) const;

	std::string  get(unsigned int start_index, unsigned int end_index) const;

	int codepoint(unsigned int index) const;

	bool empty() const { if (!(m_StringAccumulate.empty())) { return false; } else { return true; } }

	void clear();

	 // Toolbox	
	void ParseStream(std::istream & istream);




};

#endif 