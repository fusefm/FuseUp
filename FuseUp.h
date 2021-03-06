#ifndef FuseUp_H
#define FuseUp_H

#include <QtGui/QMainWindow>
#include <QSqlDatabase>
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
    QString databasePath;
    void updateUserList();
    void showQueryError(QSqlQuery& query);
    void setupNewDatabase();
    Ui::MainWindow ui;
};

#endif // FuseUp_H
