#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_adopt_a_pet_a10.h"

class Qt_adopt_a_pet_a10 : public QMainWindow
{
    Q_OBJECT

public:
    Qt_adopt_a_pet_a10(QWidget *parent = nullptr);
    ~Qt_adopt_a_pet_a10();

private:
    Ui::Qt_adopt_a_pet_a10Class ui;
};
