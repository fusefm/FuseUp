#include "FuseUp.h"
#include "useredit.h"

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
  if(!query.exec("CREATE TABLE IF NOT EXISTS user("
                 "id TEXT,"
                 "firstName TEXT,"
                 "lastName TEXT,"
                 "phoneNumber TEXT,"
                 "emailAddress TEXT,"
                 "merch TEXT,"
                 "groups TEXT);"))
  {
    showQueryError(query);
  }

  updateUserList();

  // Connect the buttons to their slots.
  connect(ui.AddButton, SIGNAL(pressed()), this, SLOT(showAddDialog()));
  connect(ui.EditButton, SIGNAL(pressed()), this, SLOT(editDatabaseUser()));
  connect(ui.DeleteButton, SIGNAL(pressed()), this, SLOT(deleteDatabaseUser()));
  connect(ui.UploadButton, SIGNAL(pressed()), this, SLOT(uploadDatabase()));
}

void FuseUp::deleteDatabaseUser()
{
  foreach(QTableWidgetItem* item, ui.UsersList->selectedItems())
  {
    if(item->column() == 0)
    {
      // we found the column.. delete the record...
      if(QMessageBox::question(this, "Confirm Deletion",
                            "Are you sure you want to delete this user?",
                               QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;
      QSqlQuery query;
      if(!query.exec("DELETE FROM user WHERE id=\'" + item->text() + "\';"))
      {
        showQueryError(query);
      }
      updateUserList();
      return;
    }
  }
}

void FuseUp::editDatabaseUser()
{

}

void FuseUp::showAddDialog()
{
  userEdit dlg(this);
  if(dlg.exec() == QDialog::Accepted)
  {
    QSqlQuery query;
    if(!query.exec("INSERT INTO user VALUES (\'" + dlg.returnData.userID + "\' , \'"  +
                    dlg.returnData.firstName + "\', \'" + dlg.returnData.lastName + "\' , \'" +
                    dlg.returnData.phoneNumber + "\' , \'" +  dlg.returnData.emailAddress + "\' , \'" +
                    dlg.groupsReturnData + "\' , \'" + dlg.MerchReturnData + "\')"))
    {
      showQueryError(query);
    }
    updateUserList();
  }
}

void FuseUp::uploadDatabase()
{

}

void FuseUp::showQueryError(QSqlQuery& query)
{
  QMessageBox::critical(this, "SQL Error",
                        "Error, there was a SQLITE problem: " +
                        query.lastError().text());
}

void FuseUp::updateUserList()
{
  ui.UsersList->clearContents();
  QSqlQuery query;
  // Populate the view with any retained data.
  if(!query.exec("SELECT * FROM user;"))
  {
    showQueryError(query);
  }


  int fIDuserID = query.record().indexOf("id");
  int fIDFirstName = query.record().indexOf("firstName");
  int fIDLastName = query.record().indexOf("lastName");
  int fIDPhoneNumber = query.record().indexOf("phoneNumber");
  int fIDEmailAddress = query.record().indexOf("emailAddress");
  int fIDMerch = query.record().indexOf("merch");
  int fIDGroups = query.record().indexOf("groups");

  for(int i = 0; query.next(); i++)
  {
    ui.UsersList->setRowCount(i + 1);
    QTableWidgetItem* IDItem = new QTableWidgetItem(query.value(fIDuserID).toString());
    QTableWidgetItem* FirstNameItem = new QTableWidgetItem(query.value(fIDFirstName).toString());
    QTableWidgetItem* LastNameItem = new QTableWidgetItem(query.value(fIDLastName).toString());
    QTableWidgetItem* PhoneNumberItem = new QTableWidgetItem(query.value(fIDPhoneNumber).toString());
    QTableWidgetItem* EmailAddressItem = new QTableWidgetItem(query.value(fIDEmailAddress).toString());
    QTableWidgetItem* MerchItem = new QTableWidgetItem(query.value(fIDMerch).toString());
    QTableWidgetItem* GroupsItem = new QTableWidgetItem(query.value(fIDGroups).toString());
    ui.UsersList->setItem(i, 0, IDItem);
    ui.UsersList->setItem(i, 1, FirstNameItem);
    ui.UsersList->setItem(i, 2, LastNameItem);
    ui.UsersList->setItem(i, 3, PhoneNumberItem);
    ui.UsersList->setItem(i, 4, EmailAddressItem);
    ui.UsersList->setItem(i, 5, MerchItem);
    ui.UsersList->setItem(i, 6, GroupsItem);
  }
  ui.UsersList->resizeColumnsToContents();
}


FuseUp::~FuseUp()
{} 

#include "FuseUp.moc"
