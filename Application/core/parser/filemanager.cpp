//
// Created by Neemaxon on 04.03.2026.
//

#include <fstream>
#include <iostream>
#include <QFile>
#include <QFileInfo>
#include "binary/BinaryFormat.h"
#include "xml/XmlFormat.h"

#include <QByteArray>

using namespace std;

void parse(QString path) {
    QFile File(path);

    QFileInfo Info(File);

    QString Extension = Info.suffix();

    if (Extension == ".rbxl") {
        ReparseRBXL(path);
    } else if (Extension == ".rbxlx") {

    }
}
