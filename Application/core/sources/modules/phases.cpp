#include <iostream>
#include "interface.h"
#include "../../file/file.h"
#include "../../../render/rendermanager.h"

#include <QString>
#include <QFileInfo>
#include <qmainwindow.h>

using namespace std;

int instudio = false;
int ingame = false;

QString openfilex(QMainWindow* window) {
    cout << "openfilex called" << '\n';

    QString file = openfile(window);

    return file;
};

void startup(QMainWindow* window) {

    // startup bools for choose interface
    instudio = true;
    ingame = false;

    // start 3d engine
    start3d(window);

    // open file
    QString startopenfile = openfilex(window);

    if (!startopenfile.isEmpty()) {
        loadwidgeterror("console", 0.5);
    };
};

// for another C++ scripts
bool is() {
    if (instudio && not ingame) {
        return true;
    } else {
        return false;
    }
};