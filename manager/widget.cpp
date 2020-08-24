#include "widget.h"
#include "ui_widget.h"
#include <QSqlQueryModel>
#include <QSplitter>
#include <QSqlError>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(750,500);
    ui->stackedWidget->setCurrentIndex(0);
    QSqlQueryModel *typeModel =  new QSqlQueryModel(this);
    //从type table选中name字段，并设置进复选框
    typeModel->setQuery("select name from type");
    if (typeModel->lastError().isValid())
        qDebug() << typeModel->lastError();

    ui->sellTypeComboBox->setModel(typeModel);

    QSplitter *splitter = new QSplitter(ui->managePage);
    splitter->resize(700,360);
    splitter->move(0,50);
    splitter->addWidget(ui->toolBox);
    splitter->addWidget(ui->dailyList);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,1);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_sellTypeComboBox_currentIndexChanged(int index)
{

}
