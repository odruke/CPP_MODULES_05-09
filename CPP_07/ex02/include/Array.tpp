/* ========== Constructors and destructor ==============*/
template<typename T>
Array<T>::Array(void) : _array(NULL), _size(0) {}

template<typename T>
Array<T>::Array(unsigned int const& n) : _array(new T[n]()), _size(n) {}

template<typename T>
Array<T>::Array(Array const& copy) : _array(new T[copy._size]()), _size(copy._size)
{
	for (unsigned int i = 0; i < copy._size; i++)
		this->_array[i] = copy._array[i];
}

template<typename T>
Array<T>::~Array(void)
{
	delete[] this->_array;
}

/* ========== overload operators ==============*/
template<typename T>
Array<T>&	Array<T>::operator=(Array const& other)
{
	if (this == &other)
		return *this;

	if (this->_array)
		delete [] this->_array;
	T*	newArray = new T[other._size];
	for (unsigned int i = 0; i < other._size; i++)
		newArray[i] = other._array[i];

	this->_array = newArray;
	this->_size = other._size;
	return *this;
}

template<typename T>
T&	Array<T>::operator[](unsigned int pos)
{
	if (pos >= this->_size)
		throw OutOfBounds(pos);
	return this->_array[pos];
}

/* ========== member functions ==============*/

template<typename T>
unsigned int	Array<T>::size(void) const
{
	return this->_size;
}


/* ========== exceptions ==============*/

template<typename T>
Array<T>::OutOfBounds::OutOfBounds(unsigned int size)
{
	std::ostringstream oss;
	oss << YELLOW << "the index [" << RED << size
		<< YELLOW << "] is out of bounds for this array"
		<< RESET;
	this->_msg = oss.str();
}

template<typename T>
const char*	Array<T>::OutOfBounds::what() const throw()
{
	return this->_msg.c_str();
}

template<typename T>
Array<T>::OutOfBounds::~OutOfBounds() throw() {}



