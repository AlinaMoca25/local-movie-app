#include "Repository.h"

Repository::Repository()
{
	;
}

CSVrepo::CSVrepo()
{
	;
}

HTMLrepo::HTMLrepo()
{
	;
}

Movie Repository::getIndex(string title, int year) { //<->getMovie
	for(Movie i: this->moviesList)
		if (title == i.getTitle())
			if (year == i.getYear())
				return i;
	return Movie();
}

bool Repository::addMovie(Movie movie)
{
	MovieValidator validator;
	validator.validateMovie(movie);
	Movie m = this->getIndex(movie.getTitle(), movie.getYear());
	if (m.getTitle() != "" && m.getYear() != 0)
		return false;
	this->moviesList.push_back(movie);
	return true;
}

bool Repository::deleteMovie(string title, int year)
{
	Movie m = this->getIndex(title, year);
	if (m.getTitle() == "" && m.getYear() == 0)
		return false;
	this->moviesList.erase(remove(this->moviesList.begin(), this->moviesList.end(), m));
	return true;
}

bool Repository::updateMovie(Movie movie)
{
	MovieValidator validator;
	validator.validateMovie(movie);
	Movie m = this->getIndex(movie.getTitle(), movie.getYear());
	if (m.getTitle() == "" && m.getYear() == 0)
		return false;
	this->moviesList.erase(remove(this->moviesList.begin(), this->moviesList.end(), movie));
	this->moviesList.push_back(movie);
	return true;
}

vector<Movie> Repository::getAllMovies()
{
	return this->moviesList;
}

void Repository::addStartEntries() {
	this->moviesList.push_back(Movie("Encanto", "Family/Fantasy", "https://www.youtube.com/watch?v=CaimKeDcudo", 2021, (float)91));
	this->moviesList.push_back(Movie("Notting hill", "Romance/Comedy", "https://www.youtube.com/watch?v=4RI0QvaGoiI", 1999, (float)84));
	this->moviesList.push_back(Movie("Pride & Prejudice", "Romance/Drama", "https://www.youtube.com/watch?v=Ur_DIHs92NM", 2005, (float)87));
	this->moviesList.push_back(Movie("Catch Me If You Can", "Crime/Comedy", "https://www.youtube.com/watch?v=71rDQ7z4eFg", 2002, (float)96));
	this->moviesList.push_back(Movie("Forrest Gump", "Comedy/Romance", "https://www.youtube.com/watch?v=bLvqoHBptjg", 1994, (float)76));
	this->moviesList.push_back(Movie("The Boy In Stripped Pijamas", "War/Thriller", "https://www.youtube.com/watch?v=uwysOfnX2Qg", 2008, (float)65));
	this->moviesList.push_back(Movie("Bohemian Rapsody", "Musical/Documentary", "https://www.youtube.com/watch?v=mP0VHJYFOAU", 2018, (float)60));
	this->moviesList.push_back(Movie("Erin Brockovich", "Thriller/Documentary", "https://www.youtube.com/watch?v=jjqUUxIy_yk", 2000, (float)85));
	this->moviesList.push_back(Movie("Scent Of A Woman", "Thriller/Drama", "https://www.youtube.com/watch?v=Jd10x8LiuBc", 1992, (float)85));
	this->moviesList.push_back(Movie("Sense and Sensibility", "Romance/Comedy", "https://www.youtube.com/watch?v=2WGq2Rbs1Qg", 1995, (float)97));
	this->moviesList.push_back(Movie("Fight Club", "Thriller/Crime", "https://www.youtube.com/watch?v=BdJKm16Co6M", 1999, (float)80));
}

void Repository::readFromFile(string filename)
{
	ifstream file{ filename };
	//ifstream file;
	//file.open(filename.c_str());
	Movie m;
	while (file >> m)
	{
		//file >> m;
		//file.ignore('\n');
		this->moviesList.push_back(m);
	}
	file.close();
}

void Repository::saveToFile(string filename)
{
	ofstream file{ filename };
	for (Movie m : this->moviesList)
		file << m << "\n";
	file.close();
}

Movie Repository::getIndexInWatchList(string title, int year)
{
	for (Movie m : this->watchList)
		if (m.getTitle() == title && m.getYear() == year)
			return m;
	return Movie();
}

bool Repository::deleteFromWatchList(string title, int year)
{
	Movie m = this->getIndexInWatchList(title, year);
	if (m.getTitle() == "" && m.getYear() == 0)
		return false;
	else
	{
		this->watchList.erase(remove(this->watchList.begin(), this->watchList.end(), m));
		return true;
	}
}

bool Repository::addToWatchList(Movie m)
{
	this->watchList.push_back(m);
	return true;
}

vector<Movie> Repository::seeWatchList()
{
	return this->watchList;
}

void Repository::increaseRating(string title, int year)
{
	Movie m = this->getIndex(title, year);
	float likes = m.getLikes();
	m.setLikes(likes + 1);
	this->updateMovie(m);
}

void Repository::saveWatchListToFile(string filename) {
	;
}

void CSVrepo::saveWatchListToFile(string filename)
{
	ofstream file(filename, ios::app);
	for (Movie m : this->watchList)
	{
		file << m.getTitle() + "," + m.getGenre() + "," + m.getTrailer() + ", " << m.getYear() << ", " << m.getLikes() << "\n";
	}
	file.close();
}

void HTMLrepo::saveWatchListToFile(string filename)
{
	ofstream file(filename);
	file << "<!DOCTYPE html>    <!--write this exactly as it is here-->\n"
		"<html> <!--write this exactly as it is here-->\n"
		"<head> <!--write this exactly as it is here-->\n"
		"<title>Watch List</title> <!--replace Playlist with the title for your HTML-->\n"
		"</head> <!--write this exactly as it is here(close head tag) -->\n"
		"<body> <!--write this exactly as it is here-->\n"
		"<table border = \"1\"> <!--write this exactly as it is here-->\n";

	file << "<tr> <!--tr = table row; 1 row for each entity-->\n"
		"\t<td>Title</td> <!--td = table data; 1 td for each attribute of the entity-->\n"
		"\t<td>Genre</td>\n"
		"\t<td>Year of release</td>\n"
		"\t<td>Number of likes</td>\n"
		"\t<td>Trailer link</td>\n"
		"</tr>\n";

	for (Movie m : this->watchList)
	{
		file << "<tr>\n";
		file << "\t<td>" << m.getTitle() << "</td>\n";
		file << "\t<td>" << m.getGenre() << "</td>\n";
		file << "\t<td>" << m.getYear() << "</td>\n";
		file << "\t<td>" << m.getLikes() << "</td>\n";
		file << "\t<td><a href =\"" << m.getTrailer() << "\">trailer</a></td>\n";
		file << "</tr>\n";
	}

	file << "</table>\n"
		"</body>\n"
		"</html>\n";
	file.close();
}

void Repository::openFile(string filename)
{
	;
}

void CSVrepo::openFile(string filename)
{
	string command = "start " + filename;
	//string command = "start excel" + filename;
	system(command.c_str());
}

void HTMLrepo::openFile(string filename)
{
	string command = "start " + filename;
	system(command.c_str());
}