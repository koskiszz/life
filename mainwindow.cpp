#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    field(new FieldWidget(this))
{
    ui->setupUi(this);
    ui->fieldLayout->addWidget(field);

    connect(ui->buttonStart, SIGNAL(clicked()), field, SLOT(start()));
    connect(ui->buttonStop,  SIGNAL(clicked()), field, SLOT(stop()));
    connect(ui->buttonClear, SIGNAL(clicked()), field, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
