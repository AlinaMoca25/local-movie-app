#include "GUI.h"

GUI::GUI(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->connectSignalsAndSlots();
}

GUI::~GUI()
{}

void GUI::connectSignalsAndSlots()
{
    QObject::connect(this->ui.adminButton, &QPushButton::clicked, this, &GUI::openAdmin);
    QObject::connect(this->ui.userButton, &QPushButton::clicked, this, &GUI::openUser);
}

void GUI::openAdmin()
{
    hide();
    admin = new Admin(this);
    admin->show();
}

void GUI::openUser()
{
    hide();
    user = new User(this);
    user->show();
}