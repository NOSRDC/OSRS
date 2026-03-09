//
// Created by Neemaxon on 27.02.2026.
//

#include <any>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include <QErrorMessage>
#include <QPushButton>
#include <QVBoxLayout>
#include <QByteArray>
#include <QWidget>
#include <qstring.h>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include "../../core/sumerrors/sumerrors.h"

using namespace std;

int Warning_Window(string name, string description, string link) {
    QString parametername = "Warning: " + QString::fromStdString(name) + ".";
    QString parameterdescription = "Warning: " + QString::fromStdString(name) + ". Description: " + QString::fromStdString(description) + ". if link avaliable: " + QString::fromStdString(link) + ". Ok ?";

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(
        nullptr,
        parametername,
        parameterdescription,
        QMessageBox::Ok | QMessageBox::Cancel
    );

    if (reply == QMessageBox::Ok) {
        return 1;
    } else {
        return 0;
    }
}

void Error_Window(string name, string description, string link) {
    QString parametername = "Error: " + QString::fromStdString(name) + ".";
    QString parameterdescription = "Error: " + QString::fromStdString(name) + ". Description: " + QString::fromStdString(description) + ". if link avaliable: " + QString::fromStdString(link) + ".";

    QMessageBox::critical(nullptr,parametername , parameterdescription);
}

void Console_Output(string name, string description, string link) {
    string text = "Output: " + name + ". Description: " + description + ". if link avaliable: " + link + ".";
    cout << "\n" << text << "\n";
}

void Widget(string warning_type, float warning_number) {
    int finded = 0;
    if (warning_type == "error") {
        string jsonStr = SumErrors(warning_number);

        QJsonDocument doc = QJsonDocument::fromJson(
            QByteArray::fromStdString(jsonStr)
        );

        QJsonObject obj = doc.object();

        string v1 = obj["name"].toString().toStdString();
        string v2 = obj["desc"].toString().toStdString();
        string v3 = obj["link"].toString().toStdString();

        finded = 1;

        Error_Window(v1,v2,v3);
    }

    if (warning_type == "console") {
        string jsonStr = SumErrors(warning_number);

        QJsonDocument doc = QJsonDocument::fromJson(
            QByteArray::fromStdString(jsonStr)
        );

        QJsonObject obj = doc.object();

        string v1 = obj["name"].toString().toStdString();
        string v2 = obj["desc"].toString().toStdString();
        string v3 = obj["link"].toString().toStdString();

        finded = 1;

        Console_Output(v1,v2,v3);
    }

    if (warning_type == "warning") {
        string jsonStr = SumErrors(warning_number);

        QJsonDocument doc = QJsonDocument::fromJson(
            QByteArray::fromStdString(jsonStr)
        );

        QJsonObject obj = doc.object();

        string v1 = obj["name"].toString().toStdString();
        string v2 = obj["desc"].toString().toStdString();
        string v3 = obj["link"].toString().toStdString();

        finded = 1;

        Warning_Window(v1,v2,v3);
    }
    if (finded == 0) {
        string jsonStr = SumErrors(0.2);

        QJsonDocument doc = QJsonDocument::fromJson(
            QByteArray::fromStdString(jsonStr)
        );

        QJsonObject obj = doc.object();

        string v1 = obj["name"].toString().toStdString();
        string v2 = obj["desc"].toString().toStdString();
        string v3 = obj["link"].toString().toStdString();

        Error_Window(v1,v2,v3);
    }
}

