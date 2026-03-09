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

QString selectfilepath(QMainWindow* window) {
    QString filePath = QFileDialog::getSaveFileName(
        window,
        "Save rbxmk file",
        QDir::homePath() + "/name.rbxmk",
        "rbxmk Files (*.rbxmk)"
    );

    return filePath;
};

QString openfile(QMainWindow* window) {
    QString file = QFileDialog::getOpenFileName(
        window,
        "select a file for import from the original Roblox Studio",
        QDir::homePath(),
        "rbxmk (*.rbxmk)"
    );
    return file;
};

QString exportfile(QMainWindow* window) {
    QString filePath = QFileDialog::getSaveFileName(
        window,
        "export from rbxmk-studio",
        QDir::homePath() + "/name.rbxl",
        "rbxl (*.rbxl);; rbxlx (*.rbxlx)"
    );

    return filePath;
};

QString importfile(QMainWindow* window) {
    QString file = QFileDialog::getOpenFileName(
        window,
        "select a file for open",
        QDir::homePath(),
        "rbxl (*.rbxl);;rbxlx (*.rbxlx)"
    );
    return file;
};
