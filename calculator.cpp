#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    lcd_ = new QLCDNumber(12);
    lcd_->setSegmentStyle(QLCDNumber::Flat);
    lcd_->setMinimumSize(150, 50);

    QChar aButtons[4][4] = {
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {'0', '.', '=', '+'}
    };

    QGridLayout* topLayout = new QGridLayout;
    topLayout->addWidget(lcd_, 0, 0, 1, 4);
    topLayout->addWidget(createButton("CE"), 1, 3);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            topLayout->addWidget(createButton(aButtons[i][j]), i+2, j);
    setLayout(topLayout);
}

QPushButton* Calculator::createButton(const QString& str) {
    QPushButton* button = new QPushButton(str);
    button->setMinimumSize(40, 40);
    connect(button, &QPushButton::clicked, this, &Calculator::slotButtonClicked);
    return button;
}

void Calculator::slotButtonClicked() {
    QString str = qobject_cast<QPushButton*>(sender())->text();
    if (str == "CE") {
        stack_.clear();
        display_ = "";
        lcd_->display(0);
    } else if (str.contains(QRegExp("[0-9]"))) {
        display_ += str;
        lcd_->display(display_.toDouble());
    } else if (str == ".") {
        display_ += str;
        lcd_->display(display_);
    } else {
        if (stack_.size() > 1) {
            stack_.push_back(QString().setNum(lcd_->value()));
            calculate();
            stack_.clear();
            stack_.push_back(QString().setNum(lcd_->value()));
            if (str != "=") stack_.push_back(str);
        } else {
            stack_.push_back(QString().setNum(lcd_->value()));
            stack_.push_back(str);
            display_ = "";
        }
    }
}

void Calculator::calculate() {
    double operand2 = stack_.pop().toDouble();
    char operation = stack_.pop().toStdString()[0];
    double operand1 = stack_.pop().toDouble();
    double result = 0;


    switch (operation) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
    }

    lcd_->display(result);
}
