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
#include "sub//cryptoeditor.h"
#include "sub/lz4editor.h"

#include <QErrorMessage>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <Qstring>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

void savefile(QMainWindow* window) {
    using namespace std;

    QString Folder = selectfilepath(window);

    string RbxmkFile = StartUpAllFromTableObjects();

    QByteArray JsonData = QByteArray::fromStdString(RbxmkFile);
    QByteArray Compressed = CompressLZ4(JsonData);
    QByteArray Encrypted = EncryptAES(Compressed);

    ofstream File(Folder.toStdString(), ios::binary);

    File.write(Encrypted.data(), Encrypted.size());

    File.close();
};
