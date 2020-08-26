#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDomDocument>
#include <QStandardItemModel>

namespace Ui {

class Widget;
}



class Widget : public QWidget
{
    Q_OBJECT

public:
    enum DateTimeType{Time, Date, DateTime};
    QString getDataTime(DateTimeType type);
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_sellTypeComboBox_currentIndexChanged(const QString &arg1);

    void on_sellBrandComboBox_currentIndexChanged(const QString &arg1);

    void on_sellNumSpinBox_valueChanged(int arg1);

    void on_sellOkBtn_clicked();

    void on_sellCancelBtn_clicked();

    void on_typeComboBox_currentIndexChanged(QString type);

    void on_updateBtn_clicked();

    void on_manageBtn_clicked();

    void on_chartBtn_clicked();

private:
    Ui::Widget *ui;
    QDomDocument doc;
    QStandardItemModel *chartModel;

    bool docRead();
    bool docWrite();
    void writeXml();
    void createNodes(QDomElement &date);
    void showDailyList();

    void createChartModelView();
    void showChart();
};

#endif // WIDGET_H
