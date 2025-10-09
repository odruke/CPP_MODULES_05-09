#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include "colors.hpp"

int	main()
{
	Data *data = new(Data);
	data->name = "John";
	data->age = 25;
	data->address = "13th maple street";

	uintptr_t raw = Serializer::serialize(data);
	Data *newData = Serializer::deserialize(raw);

	std::cout << "the name is: " << GREEN << newData->name << RESET
			<< "\nhis age is: " << GREEN << newData->age << RESET
			<< "\nand he lives in: " << GREEN << newData->address << RESET << std::endl;

	std::cout << "\nAddress of data: " << YELLOW << data << RESET
			<< "\nAddress of newData: " << YELLOW << newData << RESET
			<< "\nAddress of raw: " << YELLOW << &raw << RESET
			<< "\nContent of raw: " << BLUE << raw << std::endl;

	delete data;
}
