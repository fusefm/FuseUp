#include "FuseUp.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QSqlDatabase>
#include <QDir>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>

FuseUp::FuseUp()
{
  ui.setupUi(this);
  
  // Setup shortcuts.
  ui.AddButton->setShortcut(QKeySequence(Qt::Key_A));
  ui.EditButton->setShortcut(QKeySequence(Qt::Key_F2));
  ui.DeleteButton->setShortcut(QKeySequence(Qt::Key_Delete));
  
  // Create a database.
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QString databasePath = QDir::homePath() + "//.member.db";
  db.setDatabaseName(databasePath);
  if(!db.open())
  {
    QMessageBox::critical(this, "Error opening database.", 
			  "Error, could not open database: " + db.lastError().text());
  }
  
  // Create some tables and shiz.
  QSqlQuery query;
  if(!query.exec("CREATE TABLE IF NOT EXISTS mailingLists("
                                   "id INTEGER PRIMARY KEY,"
                                                "name TEXT);"))
  {
    showQueryError(query);
  }

  if(!query.exec("CREATE TABLE IF NOT EXISTS user("
                 "id TEXT,"
                 "firstName TEXT,"
                 "lastName TEXT,"
                 "phoneNumber TEXT,"
                 "emailAddress TEXT);"))
  {
    showQueryError(query);
  }

  if(!query.exec("CREATE TABLE IF NOT EXISTS userMailingLists("
                 "userID INTEGER,"
                 "mailingListID INTEGER);"))
  {
    showQueryError(query);
  }

  if(!query.exec("CREATE TABLE IF NOT EXISTS merch("
                 "id INTEGER PRIMARY KEY,"
                 "name TEXT,"
                 "cost INTEGER);"))
  {
    showQueryError(query);
  }
  
  if(!query.exec("CREATE TABLE IF NOT EXISTS userMerch("
                "userid INTEGER,"
                "merchID INTEGER);"))
  {
    showQueryError(query);
  }

  // Populate the view with any retained data.
  if(!query.exec("SELECT * FROM user;"))
  {
    showQueryError(query);
  }

  ui.UsersList->setRowCount(2);
  int fIDuserID = query.record().indexOf("id");
  int fIDFirstName = query.record().indexOf("firstName");
  int fIDLastName = query.record().indexOf("lastName");
  int fIDPhoneNumber = query.record().indexOf("phoneNumber");
  int fIDEmailAddress = query.record().indexOf("emailAddress");

  for(int i = 0; query.next(); i++)
  {
    QTableWidgetItem* IDItem = new QTableWidgetItem(query.value(fIDuserID).toString());
    QTableWidgetItem* FirstNameItem = new QTableWidgetItem(query.value(fIDFirstName).toString());
    QTableWidgetItem* LastNameItem = new QTableWidgetItem(query.value(fIDLastName).toString());
    QTableWidgetItem* PhoneNumberItem = new QTableWidgetItem(query.value(fIDPhoneNumber).toString());
    QTableWidgetItem* EmailAddressItem = new QTableWidgetItem(query.value(fIDEmailAddress).toString());
    ui.UsersList->setItem(i, 0, IDItem);
    ui.UsersList->setItem(i, 1, FirstNameItem);
    ui.UsersList->setItem(i, 2, LastNameItem);
    ui.UsersList->setItem(i, 3, PhoneNumberItem);
    ui.UsersList->setItem(i, 4, EmailAddressItem);
  }
}

void FuseUp::showQueryError(QSqlQuery& query)
{
  QMessageBox::critical(this, "SQL Error",
                        "Error, there was a SQLITE problem: " +
                        query.lastError().text());
}


FuseUp::~FuseUp()
{} 

#include "FuseUp.moc"
