#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Authorization)
{
    ui->setupUi(this);

    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
    db->setHostName("127.0.0.1");
    db->setUserName("postgres");
    db->setPassword("1234");
    db->setPort(3000);
    if (!db->open())
        qDebug() << db->lastError();
    else {
        qDebug() << "data base opened sucessful";
        query = QSqlQuery(*db);
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS Users(Id TEXT, Login TEXT, Password TEXT)")) {
        qDebug() << query.lastError();
    }
    ui->login_input->setPlaceholderText("example@example.ex");
    ui->password_input->setPlaceholderText("password");

}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_hide_clicked()
{
    if (ui->password_input->echoMode() == QLineEdit::Normal) {
        ui->password_input->setEchoMode(QLineEdit::Password);
        ui->hide->setStyleSheet("QToolButton {"
                                "border: none;"
                                "background-color:none;"
                                "image: url(:/image/hide);"
                            "}"

                            "QToolButton:hover {"
                                "image: url(:/image/hideHover);"
                            "}"

                            "QToolButton:pressed {"
                                "image: url(:/image/hide);"
                            "}");
    }
    else {
        ui->password_input->setEchoMode(QLineEdit::Normal);
        ui->hide->setStyleSheet("QToolButton {"
                                "border: none;"
                                "background-color:none;"
                                "image: url(:/image/show);"
                            "}"

                            "QToolButton:hover {"
                                "image: url(:/image/showHover);"
                            "}"

                            "QToolButton:pressed {"
                                "image: url(:/image/show);"
                            "}");
    }
}

void Authorization::on_change_clicked()
{
    QString str = 0;
    if (ui->change->text() == "Sign In") {
        str = "Sign In";
        ui->change->setText("Sign Up");
        ui->change_text->setText("Already have account?");
    }
    else  {
        str = "Sign Up";
        ui->change->setText("Sign In");
        ui->change_text->setText("Don't have account?");
    }

    ui->label->setText(str);
    ui->sign->setText(str);
}

QString hashPassword(QString str)
{
    return QString("%1").arg(QString(QCryptographicHash::hash(str.toUtf8(),QCryptographicHash::Sha1).toHex()));
}

void Authorization::signUp()
{
    query.prepare("INSERT INTO Users (Id, Login, Password) "
              "VALUES (:id, :login, :password)");
    query.bindValue(":id", QRandomGenerator::global()->generate());
    query.bindValue(":login", ui->login_input->text());
    query.bindValue(":password", hashPassword(ui->password_input->text()));
    query.exec();
}

void Authorization::signIn()
{
    query.prepare("SELECT id FROM Users WHERE login = :login AND password = :password");
    query.bindValue(":login", ui->login_input->text());
    query.bindValue(":password", hashPassword(ui->password_input->text()));
    query.exec();

    if (query.size() > 0)
        while(query.next())
            qDebug() << query.value(0).toString();
    else
        qDebug() << "Invalid login or password!";
}

void Authorization::on_sign_clicked()
{
    if (ui->login_input->text() == "")
        ui->login_widget->setStyleSheet("QWidget#login_widget {border: 1px solid red;}");
    else if (ui->password_input->text() == "")
        ui->password_widget->setStyleSheet("QWidget#password_widget {border: 1px solid red;}");
    else {
        ui->sign->text() == "Sign Up" ? signUp() : signIn();
        ui->login_widget->setStyleSheet("QWidget#login_widget {border-bottom: 1px solid #eee}");
        ui->password_widget->setStyleSheet("QWidget#password_widget {border-bottom: 1px solid #eee}");
    }
}


void Authorization::on_login_input_textChanged(const QString &arg1)
{
    ui->login_widget->setStyleSheet("QWidget#login_widget {"
                                   "background-color:none;"
                                   "border-bottom: 1px solid #eee;"
                               "}");
}


void Authorization::on_password_input_textChanged(const QString &arg1)
{
    ui->password_widget->setStyleSheet("QWidget#password_widget {"
                                      "background-color: none;"
                                      "border-bottom: 1px solid #eee;"
                                  "}");
}

