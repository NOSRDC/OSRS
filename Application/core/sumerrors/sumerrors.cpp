//
// Created by Neemaxon on 01.03.2026.
//

#include <any>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include <QErrorMessage>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <qjsonobject.h>

using namespace std;

struct datatable {
    string name;
    string desc;
    string link;
};

vector<pair<float, datatable>> errors = {
    {
        0.1,
        {
            "name",
            "description",
            "no"
        }
    },
    {
        0.2,
        {
            "for devs",
            "this interface cannot be used with warning_type which = null",
            "no"
        }
    },
    {
        0.3,
        {
            "Maths cannot be count",
            "roblox file cannot be resolve(are planning in maths)",
            "no"
        }
    },
    {
        0.4,
        {
            "file cannot be read, its null",
            "try open file again",
            "no"
        }
    },
    {
        0.5,
        {
            "for devs",
            "file was reading successfully",
            "no"
        }
    },
    {
        0.6,
        {
            "file damaged",
            "file wasn't reading successfully",
            "no"
        }
    },
    {
        0.7,
        {
            "cannot read the API",
            "file cannot be found",
            "no"
        }
    },
};

string SumErrors(float warning_number) {
    cout << warning_number << "\n";
    int finded = 0;
    for (int i = 0; i < errors.size(); i++) {
        if (errors[i].first == warning_number) {
            finded = 1;
            QJsonObject obj;
            obj["name"] = QString::fromStdString(errors[i].second.name);
            obj["desc"] = QString::fromStdString(errors[i].second.desc);
            obj["link"] = QString::fromStdString(errors[i].second.link);
            return QJsonDocument(obj).toJson().toStdString();
        }
    }
    if (finded == 0) {
        QJsonObject obj;
        obj["name"] = QString::fromStdString(errors[1].second.name);
        obj["desc"] = QString::fromStdString(errors[1].second.desc);
        obj["link"] = QString::fromStdString(errors[1].second.link);
        return QJsonDocument(obj).toJson().toStdString();
    }
}