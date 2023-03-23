 #ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QRandomGenerator>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QtTest/QTest>>

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


private:
    Ui::Authorization *ui;
    QSqlDatabase* db;
    QSqlQuery query;
};
#endif // AUTHORIZATION_H
