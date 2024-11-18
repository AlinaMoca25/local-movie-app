#pragma once

#include "Movie.h"

class ValidationException
{
private:
	std::string message;

public:
	ValidationException(std::string _message);
	std::string getMessage() const;
};

class MovieValidator
{
public:
	void validateMovie(Movie& m);
};