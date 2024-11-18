#include "MovieValidator.h"

ValidationException::ValidationException(std::string _message) : message{ _message }
{
}

std::string ValidationException::getMessage() const
{
	return this->message;
}

void MovieValidator::validateMovie(Movie& m)
{
	std::string errors;
	//validate title, genre, trailer?
	if (m.getYear() < 1888 || m.getYear() > 2024)
		errors += "Year not valid!\n";
	if (m.getLikes() < 0)
		errors += "Number of likes not valid!\n";
	if (errors.size() > 0)
		throw ValidationException(errors);
}