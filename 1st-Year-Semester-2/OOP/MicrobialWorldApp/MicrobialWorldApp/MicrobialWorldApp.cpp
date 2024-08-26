#include "MicrobialWorldApp.h"

MicrobialWorldApp::MicrobialWorldApp(QAbstractItemModel* model, QWidget *parent)
    : QMainWindow(parent), model{ model }
{
    ui.setupUi(this);
    ui.bacteriaTableView->setModel(this->model);
}

MicrobialWorldApp::~MicrobialWorldApp()
{}


