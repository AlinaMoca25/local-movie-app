#include "Services.h"
#include <cstring>
#include <algorithm>

Services::Services() {
	this->repo;
}

Services::Services(Repository* repo) {
	this->repo = repo;
}

bool Services::addMovie(Movie m)
{
	bool flag = this->repo->addMovie(m);
	if (flag)
		return true;
	return false;
}

bool Services::deleteMovie(string title, int year)
{
	bool flag = this->repo->deleteMovie(title, year);
	if (flag)
		return true;
	return false;
}

bool Services::updateMovie(Movie movie)
{
	bool flag = this->repo->updateMovie(movie);
	if (flag)
		return true;
	return false;
}

vector<Movie> Services::getAllMovies()
{
	return this->repo->getAllMovies();
}

vector<Movie> Services::seeWatchList()
{
	return this->repo->seeWatchList();
}

vector<Movie> Services::selectGenre(string genre)
{
	vector<Movie> allMovies, validMovies;
	allMovies = this->repo->getAllMovies();
	copy_if(allMovies.begin(), allMovies.end(), back_inserter(validMovies), [genre](Movie x) { return strstr(x.getGenre().c_str(), genre.c_str()); });
	return validMovies;
}

void Services::addToWatchList(Movie m)
{
	this->repo->addToWatchList(m);
}

void Services::deleteFromWatchList(string title, int year, bool rating)
{
	this->repo->deleteFromWatchList(title, year);
	if (rating)
		this->repo->increaseRating(title, year);
}

void Services::saveToFile(string filename)
{
	this->repo->saveToFile(filename);
}

void Services::saveWatchListToFile(string filename)
{
	this->repo->saveWatchListToFile(filename);
}

void Services::openFile(string filename)
{
	this->repo->openFile(filename);
}