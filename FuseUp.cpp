#include "FuseUp.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <QSqlDatabase>
#include <QDir>
#include <QMessageBox>
#include <QSqlError>

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
}

FuseUp::~FuseUp()
{} 

#include "FuseUp.moc"
