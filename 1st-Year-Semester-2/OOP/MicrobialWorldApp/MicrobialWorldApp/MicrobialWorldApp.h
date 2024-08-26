#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MicrobialWorldApp.h"
#include <QAbstractItemModel>
#include "BacteriumModel.h"

class MicrobialWorldApp : public QMainWindow
{
    Q_OBJECT

public:
    MicrobialWorldApp(QAbstractItemModel* model, QWidget *parent = nullptr);
    ~MicrobialWorldApp();

private:
    Ui::MicrobialWorldAppClass ui;
    QAbstractItemModel* model;
};
