#include <cstdio>
#include <iostream>
#include "modules/phases.h"
#include <QApplication>
#include <fstream>
#include <any>
#include <QTimer>
#include <qmainwindow.h>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_DontUseNativeDialogs);

    QApplication app(argc, argv);

    QMainWindow window;
    window.show();

    QTimer::singleShot(0, [&window](){
        window.raise();
        window.activateWindow();
        startup(&window);
    });

    return app.exec();
};
