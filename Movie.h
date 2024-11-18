#pragma once
#include <string>
#include <iostream>


class Movie
{
private:
	std::string  title, genre, trailer;
	int yearOfRelease;
	float numberOfLikes;

public:
	Movie();
	Movie(std::string title, std::string genre, std::string trailer, int year, float likes);

	std::string getTitle();
	std::string getGenre();
	std::string getTrailer();
	int getYear();
	float getLikes();
	bool operator==(const Movie& m) const {
		if (this->title == m.title && this->yearOfRelease == m.yearOfRelease)
			return true;
		return false;
	};
	void setLikes(float newLikes);

	std::string toString();

	friend std::istream& operator>>(std::istream& stream, Movie& m);
	friend std::ostream& operator<<(std::ostream& stream, const Movie& m);

};