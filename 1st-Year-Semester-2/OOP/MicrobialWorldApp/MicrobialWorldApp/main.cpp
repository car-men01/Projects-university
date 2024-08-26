#include "MicrobialWorldApp.h"
#include <QtWidgets/QApplication>
#include <memory>
#include <qsortfilterproxymodel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a window for each biologist using the BacteriumModel

    // create a repository
    Repository repo{ "bacteria.txt" , "biologists.txt"};

    



 //  

 //   // create a window for each biologist
    for (auto& biologist : repo.getBiologists())
    {
        // create a model
        BacteriumModel* model = new BacteriumModel{ repo };

        // create a proxy model
        QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
        // set the source model for the proxy model
        proxyModel->setSourceModel(model);

        //the window will show all bacteria havind the species that the biologist is interested in using proxyModel->setFilterRegExp();
        proxyModel->setFilterRegExp(QString::fromStdString(biologist.getExpertise()));


        proxyModel->setFilterKeyColumn(1);

		MicrobialWorldApp* w = new MicrobialWorldApp{ proxyModel };
        w->setWindowTitle(QString::fromStdString(biologist.getName()));
		w->show();
	}


    /*MicrobialWorldApp w{ model };
    w.show();*/
    return a.exec();
}
