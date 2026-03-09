//
// Created by Neemaxon on 08.03.2026.
//

#include <QString>
#include <string>
#include <fstream>
#include "../../../ram/rammanager.h"

using namespace std;

void ReparseRBXMK(QString path) {
    string FilePath = path.toStdString();

    fstream File(FilePath);

    StartUpClearObjects();


}





