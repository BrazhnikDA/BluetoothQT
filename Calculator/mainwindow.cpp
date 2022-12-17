#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Для цифр
    connect(ui->pushButton_1,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_2,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_3,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_4,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_5,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_6,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_7,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_8,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_9,    SIGNAL(clicked()),this,SLOT(click_number()));
    connect(ui->pushButton_null, SIGNAL(clicked()),this,SLOT(click_number()));

    // Для операций
    connect(ui->pushButton_C, SIGNAL(clicked()),this,SLOT(click_operation()));
    connect(ui->pushButton_del, SIGNAL(clicked()),this,SLOT(click_operation()));
    connect(ui->pushButton_minus, SIGNAL(clicked()),this,SLOT(click_operation()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this,SLOT(click_operation()));
    connect(ui->pushButton_multi, SIGNAL(clicked()),this,SLOT(click_operation()));
    connect(ui->pushButton_result, SIGNAL(clicked()),this,SLOT(click_operation()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click_number() {
    QPushButton *button = (QPushButton *)sender();

    ui->label->setText(ui->label->text() + button->text());
}

void MainWindow::click_operation() {
    QPushButton *button = (QPushButton *)sender();

    QString str = ui->label->text();

    if(button->text() == "C") {
        ui->label->setText("");
    }
    if(button->text() == "-" ||  button->text() == "+" || button->text() == "/" || button->text() == "*") {
        if(str[str.size()] != "-" || str[str.size()] != "+" || str[str.size()] != "/" || str[str.size()] != "*") {
            ui->label->setText(ui->label->text() + button->text());
        }
    }
    if(button->text() == "=") {
        QString res = QString::number(calculate(ui->label->text()));
        ui->label->setText(res);
    }

}

int MainWindow::calculate(QString str) {
    auto arr = str.split('-');
    auto arr2 = str.split('+');
    auto arr3 = str.split('*');
    auto arr4 = str.split('/');

    if(arr.length() > 1) {
        int num1 = std::stoi(arr[0].toStdString());
        int num2 = std::stoi(arr[1].toStdString());
        return num1 - num2;
    }

    if(arr2.length() > 1) {
        int num1 = std::stoi(arr2[0].toStdString());
        int num2 = std::stoi(arr2[1].toStdString());
        return num1 + num2;
    }

    if(arr3.length() > 1) {
        int num1 = std::stoi(arr3[0].toStdString());
        int num2 = std::stoi(arr3[1].toStdString());
        return num1 * num2;
    }

    if(arr4.length() > 1) {
        int num1 = std::stoi(arr4[0].toStdString());
        int num2 = std::stoi(arr4[1].toStdString());
        return num1 / num2;
    }
}

