#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Authorization; }
QT_END_NAMESPACE

class Authorization : public QWidget
{
    Q_OBJECT

public:
    Authorization(QWidget *parent = nullptr);
    ~Authorization();

private slots:
    void on_hide_clicked();

    void on_change_clicked();

private:
    Ui::Authorization *ui;
};
#endif // AUTHORIZATION_H
