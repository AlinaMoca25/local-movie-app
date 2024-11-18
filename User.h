#pragma once

#include "ui_UserGUI.h"
#include "Services.h"
#include <queue>

class User : public QMainWindow
{

	Q_OBJECT

public:
	User(QWidget* parent = nullptr);
	~User();

private:
	Ui::UserMenu ui;
	Repository* repo;
	Services* service;

	queue<Movie> watchList;
	
	string currentGenre;

	void connectSignalsAndSlots();

	void seeWatchList();
	void populateList();
	void listItemClicked();
	int getSelectedIndex();
	void deleteFromWatchList();

	void seeAvailableMovies();
	void addToWatchList();
	void addMovie(Movie m);
	void nextMovie();

	void hideAllExtra();
	void closeEvent(QCloseEvent* event) override;

signals:
	void close();
};