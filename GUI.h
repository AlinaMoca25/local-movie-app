#pragma once

#include "Services.h"
#include <QtWidgets/QMainWindow>
#include "ui_MovieGUI.h"
#include "Admin.h"
#include "User.h"

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget* parent = nullptr);
    ~GUI();

private:
    Ui::MainWindow ui;
    Admin *admin;
    User* user;
    Services service;

    void connectSignalsAndSlots();

    void openAdmin();
    void openUser();
};