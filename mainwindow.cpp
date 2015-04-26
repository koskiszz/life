#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    field(new FieldWidget(this))
{
    ui->setupUi(this);
    ui->fieldLayout->addWidget(field);
}

MainWindow::~MainWindow()
{
    delete ui;
}
