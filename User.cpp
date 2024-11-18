#include "User.h"
#include <QMessageBox>

User::User(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
    this->repo = new Repository();
    this->repo->readFromFile("movies.txt");
    this->service = new Services{ this->repo };
    this->currentGenre = "";

    this->hideAllExtra();
    this->connectSignalsAndSlots();
}

User::~User()
{}

void User::connectSignalsAndSlots()
{
    QObject::connect(this->ui.seeWatchListButton, &QPushButton::clicked, this, &User::seeWatchList);
    QObject::connect(this->ui.watchListList, &QListWidget::itemClicked, this, &User::listItemClicked);
    QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &User::deleteFromWatchList);
    QObject::connect(this->ui.seeMoviesButton, &QPushButton::clicked, this, &User::seeAvailableMovies);
    QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &User::nextMovie);
    QObject::connect(this->ui.addToWatchListButton, &QPushButton::clicked, this, &User::addToWatchList);
}

void User::seeWatchList()
{
    this->hideAllExtra();
    this->ui.watchListList->clear();
    vector<Movie> watchList = this->service->seeWatchList();
    if (watchList.empty())
        QMessageBox::critical(this, "Error", "Nothing was added to the watch list!");
    else
    {
        for (Movie m : watchList)
        {
            this->ui.watchListList->addItem(QString::fromStdString(m.toString()));
        }
    }
}

void User::populateList()
{
    this->ui.watchListList->clear();
    vector<Movie> watchList = this->service->seeWatchList();
    for (Movie m : watchList)
    {
        this->ui.watchListList->addItem(QString::fromStdString(m.toString()));
    }
}

void User::listItemClicked()
{
    this->hideAllExtra();
    int row = this->getSelectedIndex();
    if (row == -1)
    {
        this->ui.titleLineEdit->clear();
        this->ui.genreLineEdit->clear();
        this->ui.trailerLineEdit->clear();
        this->ui.yearLineEdit->clear();
        this->ui.likesLineEdit->clear();
        return;
    }
    Movie m = this->service->seeWatchList()[row];
    this->ui.titleLineEdit->setText(QString::fromStdString(m.getTitle()));
    this->ui.genreLineEdit->setText(QString::fromStdString(m.getGenre()));
    this->ui.yearLineEdit->setText(QString::fromStdString(to_string(m.getYear())));
    this->ui.trailerLineEdit->setText(QString::fromStdString(m.getTrailer()));
    this->ui.likesLineEdit->setText(QString::fromStdString(to_string(m.getLikes())));
}

int User::getSelectedIndex()
{
    if (this->ui.watchListList->count() == 0)
        return -1;

    QModelIndexList index = this->ui.watchListList->selectionModel()->selectedIndexes();
    if (index.size() == 0)
        return -1;

    int idx = index.at(0).row();
    return idx;
}

void User::deleteFromWatchList()
{
    this->hideAllExtra();
    string title = this->ui.titleLineEdit->text().toStdString();
    int year = atoi(this->ui.yearLineEdit->text().toStdString().c_str());
    bool rating = false;

    this->ui.ratingLabel->show();
    this->ui.likeRadioButton->show();
    this->ui.likeRadioButton_2->show();

    QObject::connect(this->ui.likeRadioButton, &QRadioButton::clicked, this, [this](bool rating){ rating = true; this->ui.thankRating->show();});
    QObject::connect(this->ui.likeRadioButton_2, &QRadioButton::clicked, this, [this](bool rating){ rating = false; this->ui.thankRating->show();});
    this->service->deleteFromWatchList(title, year, rating);

    this->populateList();
}

void User::seeAvailableMovies()
{
    this->hideAllExtra();
    this->ui.nextButton->show();
    this->ui.addToWatchListButton->show();

    //show a label saying to enter the genre
    string genre = this->ui.genreLineEdit->text().toStdString();
    vector<Movie> movies = this->service->selectGenre(genre);

    while (!this->watchList.empty())
        this->watchList.pop();

    for (Movie m : movies)
        this->watchList.push(m);

    this->nextMovie();
}

void User::addToWatchList()
{
    Movie m = this->watchList.front();
    this->addMovie(m);
    this->populateList();
}

void User::addMovie(Movie m)
{
    this->service->addToWatchList(m);
}

void User::nextMovie()
{
    Movie currentMovie;
    this->watchList.pop();
    if(!this->watchList.empty())
        currentMovie = this->watchList.front();
    else
    {
        vector<Movie> movies = this->service->selectGenre(this->currentGenre);
        for (Movie m : movies)
            this->watchList.push(m);
    }
    this->ui.titleLineEdit->setText(QString::fromStdString(currentMovie.getTitle()));
    this->ui.genreLineEdit->setText(QString::fromStdString(currentMovie.getGenre()));
    this->ui.yearLineEdit->setText(QString::fromStdString(to_string(currentMovie.getYear())));
    this->ui.trailerLineEdit->setText(QString::fromStdString(currentMovie.getTrailer()));
    this->ui.likesLineEdit->setText(QString::fromStdString(to_string(currentMovie.getLikes())));

    string tr = currentMovie.getTrailer();
    /*LPCSTR trailer = tr.c_str();
    ShellExecuteA(NULL, "open", trailer, NULL, NULL, SW_SHOWNORMAL);*/
    string command = "start " + tr;
    system(command.c_str());
}

void User::hideAllExtra()
{
    this->ui.ratingLabel->hide();
    this->ui.likeRadioButton->hide();
    this->ui.likeRadioButton_2->hide();
    this->ui.thankRating->hide();

    this->ui.nextButton->hide();
    this->ui.addToWatchListButton->hide();
}

void User::closeEvent(QCloseEvent* event)
{
    emit close();
    QWidget::closeEvent(event);
    QApplication::quit();
}