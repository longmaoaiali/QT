#include "widget.h"
#include "ui_widget.h"
#include <QSqlQueryModel>
#include <QSplitter>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

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


void Widget::on_sellTypeComboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "请选择类型"){
        //直接调用槽函数。当做普通方法调用
        on_sellCancelBtn_clicked();
    }else {
        ui->sellBrandComboBox->setEnabled(true);
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(QString("select name from brand where type='%1'").arg(arg1));
        qDebug()<<"select name from brand where type="+arg1;
        ui->sellBrandComboBox->setModel(model);
        ui->sellCancelBtn->setEnabled(true);
    }
}


void Widget::on_sellBrandComboBox_currentIndexChanged(const QString &arg1)
{
    ui->sellNumSpinBox->setValue(0);
    ui->sellNumSpinBox->setEnabled(false);
    ui->sellSumLineEdit->clear();
    ui->sellSumLineEdit->setEnabled(false);
    ui->sellOkBtn->setEnabled(false);

    QSqlQuery query;
    query.exec(QString("select price from brand where name='%1' and type='%2'").arg(arg1).arg(ui->sellTypeComboBox->currentText()));
    qDebug()<<"select price from brand where name= "+arg1+" and type= "+ui->sellTypeComboBox->currentText();
    query.next();
    ui->sellPriceLineEdit->setEnabled(true);
    ui->sellPriceLineEdit->setReadOnly(true);
    ui->sellPriceLineEdit->setText(query.value(0).toString());

    //查询库存
    query.exec(QString("select last from brand where name ='%1' and type ='%2'").arg(arg1).arg(ui->sellTypeComboBox->currentText()));
    qDebug()<<"select last from brand where name = "+arg1+" and type = "+ ui->sellTypeComboBox->currentText();
    query.next();
    int num = query.value(0).toInt();
    if(num==0){
        QMessageBox::information(this,tr("提示"),tr("商品已经销售完！"),QMessageBox::Ok);
    } else {
        ui->sellNumSpinBox->setEnabled(true);
        ui->sellNumSpinBox->setMaximum(num);
        ui->sellLastNumLabel->setText(tr("剩余数量:%1").arg(num));
        ui->sellLastNumLabel->setVisible(true);
    }
}




void Widget::on_sellNumSpinBox_valueChanged(int arg1)
{
    if(arg1 == 0){
        ui->sellSumLineEdit->clear();
        ui->sellSumLineEdit->setEnabled(false);
        ui->sellOkBtn->setEnabled(false);
    } else {
        ui->sellSumLineEdit->setEnabled(true);
        ui->sellSumLineEdit->setReadOnly(true);
        double sum = arg1 * ui->sellPriceLineEdit->text().toInt();
        ui->sellSumLineEdit->setText(QString::number(sum));
        ui->sellOkBtn->setEnabled(true);
    }
}



void Widget::on_sellOkBtn_clicked()
{
    //确认按键的click事件
    //根据type name value 更新数据库 last字段
    QString type = ui->sellTypeComboBox->currentText();
    QString name = ui->sellBrandComboBox->currentText();
    int value = ui->sellNumSpinBox->value();
    //剩余的数量
    int last = ui->sellNumSpinBox->maximum()-value;

    QSqlQuery query;
    //获取以前的销售量
    query.exec(QString("select sell from brand where name='%1' and type='%2'").arg(name).arg(type));
    query.next();
    //以前的销售量+现在销售数据量
    int sell = query.value(0).toInt()+value;

    //更新数据库 事务操作
    qDebug()<<"update SQL dataBase";
    QSqlDatabase::database().transaction();
    bool isSuccess = query.exec(QString("update brand set sell='%1', last='%2' where name = '%3' and type = '%4'").arg(sell).arg(last).arg(name).arg(type));

    if(isSuccess){
        QSqlDatabase::database().commit();
        QMessageBox::information(this,tr("提示"),tr("购买成功！"),QMessageBox::Ok);

//        writeXml();
//        showDailyList();

        on_sellCancelBtn_clicked();
    }else{
        QSqlDatabase::database().rollback();
    }
}

void Widget::on_sellCancelBtn_clicked()
{
    //UI组件进行初始化
    ui->sellTypeComboBox->setCurrentIndex(0);
    ui->sellBrandComboBox->clear();
    ui->sellBrandComboBox->setEnabled(false);
    ui->sellPriceLineEdit->clear();
    ui->sellPriceLineEdit->setEnabled(false);
    ui->sellNumSpinBox->setValue(0);
    ui->sellNumSpinBox->setEnabled(false);
    ui->sellSumLineEdit->clear();
    ui->sellSumLineEdit->setEnabled(false);
    ui->sellOkBtn->setEnabled(false);
    ui->sellCancelBtn->setEnabled(false);
    ui->sellLastNumLabel->setVisible(false);
}
