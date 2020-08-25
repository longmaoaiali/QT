#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_sellTypeComboBox_currentIndexChanged(const QString &arg1);

    void on_sellBrandComboBox_currentIndexChanged(const QString &arg1);

    void on_sellNumSpinBox_valueChanged(int arg1);

    void on_sellOkBtn_clicked();

    void on_sellCancelBtn_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
