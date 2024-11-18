#pragma once
#include "ui_AdminGUI.h"
#include "Services.h"
#include <QtWidgets/QMainWindow>

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    Admin(QWidget* parent = nullptr);
    ~Admin();

private:
    Ui::AdminMenu ui;
    Repository* repo;
    Services* service;

    void connectSignalsAndSlots();

    void populateTable();
    void addMovie();
    void updateMovie();
    void deleteMovie();

    void listItemClicked();
    int getSelectedIndex();

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent* event) override;
};