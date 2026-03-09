#include <iostream>
#include "interface.h"
#include "../../file/file.h"
#include "../../../render/rendermanager.h"
#include "../../saver/saver.h"

#include <QString>
#include <QFileInfo>
#include <qmainwindow.h>

using namespace std;

int instudio = false;

QString OpenFileX(QMainWindow* window) {
    cout << "openfilex called" << '\n';

    QString file = importfile(window);

    return file;
};

void StartUpProject(QMainWindow* window) {

    // startup bools for choose interface
    instudio = true;

    // start 3d engine
    StartUpFilament(window);

    // test save file
    savefile(window);
};

// for another C++ scripts
bool is() {
    if (instudio) {
        return true;
    } else {
        return false;
    }
};