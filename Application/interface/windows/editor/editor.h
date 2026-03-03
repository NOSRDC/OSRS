//
// Created by Day Wo Saq on 1/29/26.
//

#ifndef
#define 

#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class editor;
}

QT_END_NAMESPACE

class editor : public QMainWindow {
    Q_OBJECT

public:
    explicit editor(QWidget *parent = nullptr);

    ~editor() override;

private:
    Ui::editor *ui;
};


#endif //