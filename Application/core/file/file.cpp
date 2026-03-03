//
// Created by Neemaxon on 28.02.2026.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <any>
#include <vector>

#include <qstring.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <QMainWindow>
#include <qdebug.h>

using namespace std;

QString openfile(QMainWindow* window) {
    QString file = QFileDialog::getOpenFileName(
        window,
        "select a file for import from the original Roblox Studio",
        QDir::homePath(),
        "RBXL (*.rbxl);;RBXLX (*.rbxlx)"
    );
    return file;
};
