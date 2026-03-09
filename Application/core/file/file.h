//
// Created by Neemaxon on 01.03.2026.
//

#ifndef FILE_H
#define FILE_H

#include <QString>

#include <QMainWindow>

QString selectfilepath(QMainWindow* window);

QString openfile(QMainWindow* window);

QString exportfile(QMainWindow* window);

QString importfile(QMainWindow* window);

#endif //