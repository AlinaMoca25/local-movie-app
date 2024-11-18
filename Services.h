	#pragma once
#include "Repository.h"
#include <string>
using namespace std;

class Services
{
private:
	Repository* repo;

public:
	Services();
	Services(Repository* repo);
	bool addMovie(Movie m);
	bool deleteMovie(string title, int year);
	bool updateMovie(Movie movie);
	vector<Movie> getAllMovies();
	vector<Movie> seeWatchList();
	vector<Movie> selectGenre(string genre);
	void addToWatchList(Movie m);
	void deleteFromWatchList(string title, int year, bool rating);
	void saveToFile(string filename);
	void saveWatchListToFile(string filename);
	void openFile(string filename);
};