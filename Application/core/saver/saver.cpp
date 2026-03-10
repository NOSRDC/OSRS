//
// Created by Neemaxon on 03.03.2026.
//

#include "../sources/modules/interface.h"
#include <fstream>
#include <iostream>
#include <lz4.h>
#include <QJsonDocument>
#include <string>
#include <fast_obj.h>

#include "../file/file.h"
#include "../../ram/rammanager.h"

#include <QErrorMessage>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QMainWindow>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

QString FolderX = "";

void StartSaveFile(QMainWindow* window) {
    using namespace std;

    QString Folder = SaveFileAs(window);
};
