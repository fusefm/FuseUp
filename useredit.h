#ifndef USEREDIT_H
#define USEREDIT_H

#include <QtGui/QDialog>
#include "ui_userEdit.h"

struct FuseMember
{
  QString userID;
  QString firstName;
  QString lastName;
  QString emailAddress;
  QString phoneNumber;
  QStringList merch;
  QStringList groups;
};

class userEdit : public QDialog
{
  public:
    userEdit(QWidget* parent = 0, Qt::WindowFlags f = 0, FuseMember* member = 0);

  private:
    Ui::UserAddDialog ui;
};

#endif // USEREDIT_H
