#include "Admin.h"

Admin::Admin(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->repo = new Repository();
    this->repo->readFromFile("movies.txt");
    this->service = new Services{ this->repo };

    this->connectSignalsAndSlots();
}

Admin::~Admin()
{}

void Admin::connectSignalsAndSlots()
{
    QObject::connect(this->ui.seeAllMoviesButton, &QPushButton::clicked, this, &Admin::populateTable);
    QObject::connect(this->ui.addMovieButton, &QPushButton::clicked, this, &Admin::addMovie);
    QObject::connect(this->ui.updateMovieButton, &QPushButton::clicked, this, &Admin::updateMovie);
    QObject::connect(this->ui.deleteMovieButton, &QPushButton::clicked, this, &Admin::deleteMovie);
    QObject::connect(this->ui.moviesList, &QListWidget::itemClicked, this, &Admin::listItemClicked);
}

void Admin::populateTable()
{
    this->ui.moviesList->clear();
    vector<Movie> movies = this->service->getAllMovies();
    for (Movie m : movies)
    {
        this->ui.moviesList->addItem(QString::fromStdString(m.toString()));
    }
}

void Admin::addMovie()
{
    string title = this->ui.titleLineEdit->text().toStdString();
    int year = atoi(this->ui.yearLineEdit->text().toStdString().c_str());
    string genre = this->ui.genreLineEdit->text().toStdString();
    float likes = atoi(this->ui.titleLineEdit->text().toStdString().c_str());
    string trailer = this->ui.trailerLineEdit->text().toStdString();
    Movie m(title, genre, trailer, year, likes);
    this->service->addMovie(m);
    this->populateTable();
}

void Admin::updateMovie()
{
    string title = this->ui.titleLineEdit->text().toStdString();
    int year = atoi(this->ui.yearLineEdit->text().toStdString().c_str());
    string genre = this->ui.genreLineEdit->text().toStdString();
    float likes = stof(this->ui.likeLineEdit->text().toStdString());
    string trailer = this->ui.trailerLineEdit->text().toStdString();
    Movie m(title, genre, trailer, year, likes);
    this->service->updateMovie(m);
    this->populateTable();
}

void Admin::deleteMovie()
{
    string title = this->ui.titleLineEdit->text().toStdString();
    int year = atoi(this->ui.yearLineEdit->text().toStdString().c_str());
    this->service->deleteMovie(title, year);
    this->populateTable();
}

void Admin::listItemClicked()
{
    int row = this->getSelectedIndex();
    if (row == -1)
    {
        this->ui.titleLineEdit->clear();
        this->ui.genreLineEdit->clear();
        this->ui.trailerLineEdit->clear();
        this->ui.yearLineEdit->clear();
        this->ui.likeLineEdit->clear();
        return;
    }
    Movie m = this->service->getAllMovies()[row];
    this->ui.titleLineEdit->setText(QString::fromStdString(m.getTitle()));
    this->ui.genreLineEdit->setText(QString::fromStdString(m.getGenre()));
    this->ui.yearLineEdit->setText(QString::fromStdString(to_string(m.getYear())));
    this->ui.trailerLineEdit->setText(QString::fromStdString(m.getTrailer()));
    this->ui.likeLineEdit->setText(QString::fromStdString(to_string(m.getLikes())));
}

int Admin::getSelectedIndex()
{
    if (this->ui.moviesList->count() == 0)
        return -1;

    QModelIndexList index = this->ui.moviesList->selectionModel()->selectedIndexes();
    if (index.size() == 0)
        return -1;

    int idx = index.at(0).row();
    return idx;
}

void Admin::closeEvent(QCloseEvent* event)
{
    emit close();
    QWidget::closeEvent(event);
    QApplication::quit();
}

