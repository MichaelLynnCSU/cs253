

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
#include <stdlib.h>


class U 
{
public:
	//Containers

	std::string	 m_PropertiesFilename;

	mutable std::string	 m_OutputStringAccumulate;

	std::vector<std::string> m_StringAccumulate;

	mutable std::vector<unsigned int>	m_Keys;

	int state;

	// Constructors
	U();

	U(const std::string filename);

	U(const U & u_object);

	U & operator=(const U & rhs);

	std::string operator[](int index) const;

	operator bool() const;

	U & operator=(const std::string literal_data);

	U operator+(const U & rhs) const;

	U operator+(const char *literal_data) const;

	friend U operator+(const char *literal_data, const U &rhs);

	U & operator+=(const U & rhs);

	U & operator+=(const std::string literal_data);

	bool operator==(const U &rhs) const;
	
	bool operator==(const char *literal_data) const;

	friend bool operator==(const char *literal_data, const U &rhs);

	bool operator!=(const U &rhs) const;

	bool operator!=(const char *literal_data) const;

	friend bool operator!=(const char *literal_data, const U &rhs);

	friend std::ostream& operator<< (std::ostream& stream, const U &other);
	
	~U();



	// Data 
	void readfile(std::string data_file);

	void append(std::string literal_data);

	// Data query
	
	int size() const { return m_StringAccumulate.size(); }

	std::string  get() const;

	std::string  get(unsigned int index) const;

	std::string  get(unsigned int start_index, unsigned int end_index) const;

	int codepoint(const unsigned int index) const;

	bool empty() const { if (!(m_StringAccumulate.empty())) { return false; } else { return true; } }

	void clear();

	 // Toolbox	
	void ParseStream(std::istream & istream);
	
	int front();

	int back();

	// codepoint Iterator



	class iterator
	{
	public:
		mutable U * u_objectPtr;
		mutable size_t itr;

		iterator()
		{
			u_objectPtr = NULL;
		}
		
		iterator(U* objPtr, size_t size)
		{
			u_objectPtr = objPtr;
			itr = size;
		}

		iterator(const iterator & rhs) 
		{
			u_objectPtr = rhs.u_objectPtr;
			itr = rhs.itr;

		}

		~iterator() { };
		

	    const iterator & operator = (const iterator & rhs) 
		{
			u_objectPtr = rhs.u_objectPtr;
			itr = rhs.itr;
			return *this;

		}

		int operator *() const
		{

			return (u_objectPtr->m_Keys[itr]);

		}

		const iterator & operator ++() const
		{

			itr++;
			return *this;
		}

		iterator operator ++(int) const
		{
			iterator tmp(*this);
			operator++();
			return tmp;
		}

		const iterator & operator --() const
		{
			itr--;
			return *this;
		}

		iterator operator --(int) const
		{
			iterator tmp(*this);
			operator--();
			return tmp;
		}

		bool operator != (const iterator & rhs) const
		{
			return !operator == (rhs);

		}

		bool operator == (const iterator & rhs) const
		{
			return u_objectPtr == rhs.u_objectPtr && itr == rhs.itr;

		}


	};


	template<typename T>
	U(const T start, const T end)
	{

		std::string s;
		for (auto it = start; it != end; it++)
		{
			s.push_back(*it);
		}
		append(s);


	}

	iterator begin()
	{
	
		return iterator(this, 0);

	}
	
	iterator end()
	{

		return iterator(this, size());

	}

};


	

	