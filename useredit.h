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
  Q_OBJECT
  public:
    userEdit(QWidget* parent = 0, Qt::WindowFlags f = 0, FuseMember* member = 0);
    bool pressOk;
    FuseMember returnData;
    QString groupsReturnData;
    QString MerchReturnData;

  private slots:
    void merchSelectionChanged(int state);
    void OkButtonPress();
    void selectAllGroups();
  private:
    Ui::UserAddDialog ui;
};

#endif // USEREDIT_H
