#include <cstdio>
#include <iostream>
#include "modules/phases.h"
#include <QApplication>
#include <fstream>
#include <any>
#include <QCoreApplication>
#include <QTimer>
#include <QSplashScreen>
#include <QThread>
#include <qmainwindow.h>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_DontUseNativeDialogs);

    QApplication app(argc, argv);

    QPixmap pixmap(":/images/StartUpScreen.png");

    pixmap = pixmap.scaled(500, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QSplashScreen splash(pixmap);
    splash.show();

    app.processEvents();

    QThread::sleep(2);

    QMainWindow window;
    window.resize(800, 600);
    window.show();

    splash.finish(&window);

    QTimer::singleShot(0, [&window] (){
        window.raise();
        window.activateWindow();
        StartUpProject(&window);
    });

    return app.exec();
};
