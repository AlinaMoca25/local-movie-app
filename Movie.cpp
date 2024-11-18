#include "Movie.h"
#include <iostream>
#include <vector>
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS

Movie::Movie() {
	this->title = "";
	this->genre = "";
	this->trailer = "";
	this->yearOfRelease = 0;
	this->numberOfLikes = 0;
}

Movie::Movie(std::string title, std::string genre, std::string trailer, int year, float likes) {
	this->title = title;
	this->genre = genre;
	this->trailer = trailer;
	this->yearOfRelease = year;
	this->numberOfLikes = likes;
}

std::string Movie::getTitle() {
	return this->title;
}

std::string Movie::getGenre() {
	return this->genre;
}

std::string Movie::getTrailer() {
	return this->trailer;
}

int Movie::getYear() {
	return this->yearOfRelease;
}

float Movie::getLikes() {
	return this->numberOfLikes;
}

void Movie::setLikes(float newLikes)
{
	this->numberOfLikes = newLikes;
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector <std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream& operator>>(std::istream& stream, Movie& m)
{
	//stream >> m.title >> m.genre >> m.trailer;
	//stream >> m.yearOfRelease >> m.numberOfLikes;
	std::string buffer;
	getline(stream, buffer);
	std::vector<std::string> tokens = tokenize(buffer, ',');
	if (tokens.size() != 5)
		return stream;
	m.title = tokens[0];
	m.genre = tokens[1];
	m.trailer = tokens[2];
	m.yearOfRelease = atoi(tokens[3].c_str());
	m.numberOfLikes = atoi(tokens[4].c_str());
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Movie& m)
{
	stream << m.title << "(" << m.yearOfRelease << ")\n";
	stream << m.genre << " - " << m.numberOfLikes << " likes\n";
	stream << "Trailer: " << m.trailer << std::endl;
	return stream;
}

std::string Movie::toString()
{
	std::string m;
	std::string year, likes;
	year = std::to_string(this->yearOfRelease);
	likes = std::to_string(this->numberOfLikes);
	m = this->title + "(" + year + ") - " + this->genre + ", " + likes + " likes\nTrailer: " + this->trailer + "\n";
	return m;
}