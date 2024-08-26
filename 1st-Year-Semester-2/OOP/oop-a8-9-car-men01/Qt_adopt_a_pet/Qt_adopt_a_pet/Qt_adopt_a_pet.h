#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_adopt_a_pet.h"

class Qt_adopt_a_pet : public QMainWindow
{
    Q_OBJECT

public:
    Qt_adopt_a_pet(QWidget *parent = nullptr);
    ~Qt_adopt_a_pet();

private:
    Ui::Qt_adopt_a_petClass ui;
};
