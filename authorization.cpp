#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);
}

Authorization::~Authorization()
{
    delete ui;
}


void Authorization::on_hide_clicked()
{
    if (ui->password->echoMode() == QLineEdit::Normal) {
        ui->password->setEchoMode(QLineEdit::Password);
        ui->hide->setStyleSheet("image: url(:/image/hide);");
    }
    else {
        ui->password->setEchoMode(QLineEdit::Normal);
        ui->hide->setStyleSheet("image: url(:/image/show);");
    }
}


void Authorization::on_change_clicked()
{
    if (ui->change->text() == "Sign In") {
        ui->label->setText("Sign In");
        ui->sign->setText("Sign In");
        ui->change->setText("Sign Up");
    }
    else {
        ui->label->setText("Sign Up");
        ui->sign->setText("Sign Up");
        ui->change->setText("Sign In");
    }
}

