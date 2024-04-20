#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStack>
#include <QLCDNumber>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget { Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    QPushButton* createButton(const QString& str);
    void calculate();

public slots:
    void slotButtonClicked();

private:
    QLCDNumber* lcd_;
    QStack<QString> stack_;
    QString display_;
};
#endif
