#include "startup.h"
#include "ui_startup.h"

startup::startup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Startup)
{
    ui->setupUi(this);
}

startup::~startup()
{
    delete ui;
}
