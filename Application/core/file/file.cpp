//
// Created by Neemaxon on 28.02.2026.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <any>
#include <vector>

#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QDebug>

using namespace std;

QString SaveFileAs(QMainWindow* window) {
    QString filePath = QFileDialog::getSaveFileName(
        window,
        "export from rbxmk-studio",
        QDir::homePath() + "/name.rbxl",
        "rbxl (*.rbxl);; rbxlx (*.rbxlx)"
    );

    return filePath;
};

QString OpenFile(QMainWindow* window) {
    QString file = QFileDialog::getOpenFileName(
        window,
        "select a file for open",
        QDir::homePath(),
        "rbxl (*.rbxl);;rbxlx (*.rbxlx)"
    );
    return file;
};
