#include "useredit.h"
#include <QMessageBox>

userEdit::userEdit(QWidget* parent, Qt::WindowFlags f, FuseMember* member): QDialog(parent, f)
{
  ui.setupUi(this);

  connect(ui.MembershipCheck, SIGNAL(stateChanged(int)), this, SLOT(merchSelectionChanged(int)));
  connect(ui.OKButton, SIGNAL(pressed()), this, SLOT(OkButtonPress()));
  connect(ui.selectAllGroupsButton, SIGNAL(pressed()), this, SLOT(selectAllGroups()));
  connect(ui.ClearButton, SIGNAL(pressed()), this, SLOT(reject()));


  if(member)
  {
    ui.FirstNameText->setText(member->firstName);
    ui.LastNameText->setText(member->lastName);
    ui.IDNumberText->setText(member->userID);
    ui.PhoneNumberText->setText(member->phoneNumber);
    ui.EmailAddressText->setText(member->emailAddress);

    foreach(QString group, member->groups)
    {
      if(group == "fiction")
        ui.FictonCheck->setCheckState(Qt::Checked);
      else if(group == "documentary")
        ui.DocumentaryCheck->setCheckState(Qt::Checked);
      else if(group == "news")
        ui.NewsCheck->setCheckState(Qt::Checked);
      else if(group == "entertainment")
        ui.EntertainmentCheck->setCheckState(Qt::Checked);
      else if(group == "actors")
        ui.ActorsCheck->setCheckState(Qt::Checked);
      else if(group == "crew")
        ui.CrewCheck->setCheckState(Qt::Checked);
    }

    foreach(QString merch, member->merch)
    {
      if(merch == "membership")
        ui.MembershipCheck->setCheckState(Qt::Checked);
    }
  }
}

void userEdit::merchSelectionChanged(int state)
{

  // Add up the totals if any others are checked.
  unsigned int total = 0;
  if(ui.MembershipCheck->checkState() == Qt::Checked)
    total += 5;
  QString totalText = QString::fromUtf8("Total: £");
  totalText += QString::number(total);
  ui.TotalLabel->setText(totalText);

}

void userEdit::OkButtonPress()
{
  // Ensure that all the data is entered.
  if(ui.FirstNameText->text().isEmpty() ||
     ui.LastNameText->text().isEmpty() ||
     ui.IDNumberText->text().isEmpty() ||
     ui.EmailAddressText->text().isEmpty())
  {
    QMessageBox::critical(this, "Error", "You must provide at least: "
                                          "First name, Last name, Email address & Student ID");
    return;
  }

  if(ui.IDNumberText->text().length() != 7)
  {
    QMessageBox::critical(this, "Error", "Please ensure that the User ID is 7 digits in length.");
    return;
  }
  
  // Construct a struct to return back.
  returnData.firstName = ui.FirstNameText->text();
  returnData.lastName = ui.LastNameText->text();
  returnData.userID = ui.IDNumberText->text();
  returnData.emailAddress = ui.EmailAddressText->text();
  returnData.phoneNumber = ui.PhoneNumberText->text();

  groupsReturnData.clear();
  if(ui.FictonCheck->checkState() == Qt::Checked)
    groupsReturnData += "fiction ";
  if(ui.DocumentaryCheck->checkState() == Qt::Checked)
    groupsReturnData += "documentary ";
  if(ui.NewsCheck->checkState() == Qt::Checked)
    groupsReturnData += "news ";
  if(ui.EntertainmentCheck->checkState() == Qt::Checked)
    groupsReturnData += "entertainment ";
  if(ui.ActorsCheck->checkState() == Qt::Checked)
    groupsReturnData += "actors ";
  if(ui.CrewCheck->checkState() == Qt::Checked)
    groupsReturnData += "crew ";

  MerchReturnData.clear();;
  if(ui.MembershipCheck->checkState() == Qt::Checked)
    MerchReturnData += "membership ";

  // We're done.
  accept();
}

void userEdit::selectAllGroups()
{
  ui.FictonCheck->setCheckState(Qt::Checked);
  ui.DocumentaryCheck->setCheckState(Qt::Checked);
  ui.NewsCheck->setCheckState(Qt::Checked);
  ui.EntertainmentCheck->setCheckState(Qt::Checked);
  ui.ActorsCheck->setCheckState(Qt::Checked);
  ui.CrewCheck->setCheckState(Qt::Checked);
}


#include "useredit.moc"