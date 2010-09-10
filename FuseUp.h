#ifndef FuseUp_H
#define FuseUp_H

#include <QtGui/QMainWindow>
#include <QSqlQuery>
#include "ui_main.h"
class FuseUp : public QMainWindow
{
Q_OBJECT
public:
    FuseUp();
    virtual ~FuseUp();

private slots:
    void showAddDialog();
    void editDatabaseUser();
    void deleteDatabaseUser();
    void uploadDatabase();
private:

    void showQueryError(QSqlQuery& query);
    Ui::MainWindow ui;
};

#endif // FuseUp_H
