
#ifndef ARRAY_HPP
# define ARRAY_HPP

template< typename T>
class Array
{
private:
	T* _array
public:
	Array();
	Array(unsigned int const& n);
	~Array();

};

#endif
