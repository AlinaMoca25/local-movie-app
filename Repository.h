#pragma once
#include "Movie.h"
#include <string>
#include <vector>
#include <fstream>
#include "MovieValidator.h"

using namespace std;

class Repository
{
protected:
	vector<Movie> moviesList;
	vector<Movie> watchList;

public:
	Repository();

	void addStartEntries();
	Movie getIndex(string title, int year);
	bool addMovie(Movie movie);
	bool deleteMovie(string title, int year);
	bool updateMovie(Movie movie);
	vector<Movie> getAllMovies();

	void readFromFile(string filename);
	void saveToFile(string filename);

	Movie getIndexInWatchList(string title, int year);
	bool deleteFromWatchList(string title, int year);
	void increaseRating(string title, int year);
	bool addToWatchList(Movie m);
	vector<Movie> seeWatchList();

	virtual void saveWatchListToFile(string filename);
	virtual void openFile(string filename);
};


class CSVrepo : public Repository
{
public:
	CSVrepo();
	void saveWatchListToFile(string filename) override;
	void openFile(string filename) override;
};


class HTMLrepo : public Repository
{
public:
	HTMLrepo();
	void saveWatchListToFile(string filename) override;
	void openFile(string filename) override;
};
