#include "FuseUp.h"
#include "useredit.h"
#include "uploaddialog.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QSqlDatabase>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QNetworkAccessManager>

FuseUp::FuseUp()
{
  ui.setupUi(this);
  
  // Setup shortcuts.
  ui.AddButton->setShortcut(QKeySequence(Qt::Key_A));
  ui.EditButton->setShortcut(QKeySequence(Qt::Key_F2));
  ui.DeleteButton->setShortcut(QKeySequence(Qt::Key_Delete));

  setupNewDatabase();

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
      QSqlQuery query(QSqlDatabase::database("main"));
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
  FuseMember mem;
  foreach(QTableWidgetItem* item, ui.UsersList->selectedItems())
  {
    switch(item->column())
    {
      case(0):
        mem.userID = item->text();
        break;
      case(1):
        mem.firstName = item->text();
        break;
      case(2):
        mem.lastName = item->text();
        break;
      case(3):
        mem.phoneNumber = item->text();
        break;
      case(4):
        mem.emailAddress = item->text();
        break;
      case(5):
        mem.groups = item->text().split(" ");
        break;
      case(6):
        mem.merch = item->text().split(" ");
        break;
    }
  }

  // Delete that ID for editing.
  userEdit dlg(this, 0, &mem);
  if(dlg.exec() == QDialog::Accepted)
  {
    QSqlQuery query(QSqlDatabase::database("main"));
    if(!query.exec("UPDATE user SET id=\'" + dlg.returnData.userID + "\' ,"
                    "firstName=\'"  + dlg.returnData.firstName + "\', "
                    "lastName=\'" + dlg.returnData.lastName + "\' , "
                    "phoneNumber=\'" + dlg.returnData.phoneNumber + "\' , "
                    "emailAddress=\'" +  dlg.returnData.emailAddress + "\' ,"
                    "groups=\'" + dlg.groupsReturnData + "\' , "
                    "merch=\'" + dlg.MerchReturnData + "\' "
                    "WHERE id= \'" + mem.userID + "\';"))
    {
      showQueryError(query);
    }
    updateUserList();
  }
}

void FuseUp::showAddDialog()
{
  userEdit dlg(this);
  if(dlg.exec() == QDialog::Accepted)
  {
    QSqlQuery query(QSqlDatabase::database("main"));
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

  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  uploadDialog *dlg = new uploadDialog(this);
  connect(manager, SIGNAL(finished(QNetworkReply*)), dlg, SLOT(uploadFinish(QNetworkReply*)));
  QFile *file = new QFile(databasePath, this);
  file->open(QFile::ReadOnly);
  manager->post(QNetworkRequest(QUrl("http://studio.fusefm.co.uk/dbupload/upload.php")), file);
  if(dlg->exec() == QDialog::Accepted)
  {
    // close the database.
    QSqlDatabase db = QSqlDatabase::database("main");
    db.close();

    // Move the database file.
    QDir dbDir(QDir::homePath());

    // Backup the old database.
    if(!dbDir.rename(".member.db", ".member.db." +
                 QDateTime::currentDateTime().toString(Qt::ISODate)))
        QMessageBox::warning(this, "Database move", "Could not backup old database.");

    // Remove the old connection.
    QSqlDatabase::removeDatabase("main");

    // Setup a new database.
    setupNewDatabase();
  }
  file->close();
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
  QSqlQuery query(QSqlDatabase::database("main"));
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
    IDItem->setFlags(IDItem->flags() &~ Qt::ItemIsEditable);
    FirstNameItem->setFlags(IDItem->flags());
    LastNameItem->setFlags(IDItem->flags());
    PhoneNumberItem->setFlags(IDItem->flags());
    EmailAddressItem->setFlags(IDItem->flags());
    MerchItem->setFlags(IDItem->flags());
    GroupsItem->setFlags(IDItem->flags());
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

void FuseUp::setupNewDatabase()
{
    // Create a database.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main");
    databasePath = QDir::homePath() + "//.member.db";
    db.setDatabaseName(databasePath);
    if(!db.open())
    {
      QMessageBox::critical(this, "Error opening database.",
                            "Error, could not open database: " + db.lastError().text());
    }

    // Create some tables and shiz.
    QSqlQuery query(QSqlDatabase::database("main"));
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
}

FuseUp::~FuseUp()
{} 

#include "FuseUp.moc"
