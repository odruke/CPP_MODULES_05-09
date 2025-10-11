
#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <exception>
#include <iostream>
#include "colors.hpp"
#include <sstream>

template< typename T>
class Array
{
private:
	T* 				_array;
	unsigned int	_size;
public:
//canonic form
	Array();//creates empty array
	Array(unsigned int const& n);//creates array of n elements
	Array(Array const& copy);//deep copy
	Array&	operator=(Array const& other);//deep copy
	~Array();

//other overload functions
	T&	operator[](unsigned int pos);

//member functions
	unsigned int	size() const;

//exceptions

	class OutOfBounds : public std::exception
	{
	private:
		std::string	_msg;
	public:
		OutOfBounds(unsigned int size);
		virtual	~OutOfBounds() throw();
		virtual const char* what() const throw();
	};

};

#include "Array.tpp"
#endif

