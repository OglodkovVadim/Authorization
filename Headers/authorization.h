 #ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QRandomGenerator>
#include <QSqlRecord>
#include <QCryptographicHash>

QT_BEGIN_NAMESPACE
namespace Ui { class Authorization; }
QT_END_NAMESPACE

class Authorization : public QWidget
{
    Q_OBJECT

public:
    Authorization(QWidget *parent = nullptr);
    ~Authorization();

    void signIn();

    void signUp();

private slots:
    void on_hide_clicked();

    void on_change_clicked();

    void on_sign_clicked();


    void on_login_input_textChanged(const QString &arg1);

    void on_password_input_textChanged(const QString &arg1);

private:
    Ui::Authorization *ui;
    QSqlDatabase* db;
    QSqlQuery query;
};
#endif // AUTHORIZATION_H
