#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class startup;
}
QT_END_NAMESPACE

class startup : public QWidget {
    Q_OBJECT

public:
    explicit startup(QWidget *parent = nullptr);
    ~startup() override;

private:
    Ui::startup *ui;
};
