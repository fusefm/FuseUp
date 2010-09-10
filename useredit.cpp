#include "useredit.h"
#include <QMessageBox>

userEdit::userEdit(QWidget* parent, Qt::WindowFlags f, FuseMember* member): QDialog(parent, f)
{
  ui.setupUi(this);

  connect(ui.WristBandCheck, SIGNAL(stateChanged(int)), this, SLOT(merchSelectionChanged(int)));
  connect(ui.TShirtCheck, SIGNAL(stateChanged(int)), this, SLOT(merchSelectionChanged(int)));
  connect(ui.MembershipCheck, SIGNAL(stateChanged(int)), this, SLOT(merchSelectionChanged(int)));
  connect(ui.FusePackCheck, SIGNAL(stateChanged(int)), this, SLOT(merchSelectionChanged(int)));
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
      if(group == "production")
        ui.ProductionCheck->setCheckState(Qt::Checked);
      else if(group == "tv")
        ui.TVCheck->setCheckState(Qt::Checked);
      else if(group == "tech")
        ui.TechCheck->setCheckState(Qt::Checked);
      else if(group == "podcasting")
        ui.PodcastingCheck->setCheckState(Qt::Checked);
      else if(group == "events")
        ui.EventsCheck->setCheckState(Qt::Checked);
      else if(group == "marketing")
        ui.MarketingCheck->setCheckState(Qt::Checked);
      else if(group == "dj")
        ui.DJsCheck->setCheckState(Qt::Checked);
      else if(group == "music")
        ui.MusicCheck->setCheckState(Qt::Checked);
      else if(group == "news")
        ui.NewsCheck->setCheckState(Qt::Checked);
      else if(group == "presenters")
        ui.PresentersCheck->setCheckState(Qt::Checked);
      else if(group == "newmusic")
        ui.NewMusicCheck->setCheckState(Qt::Checked);
    }

    foreach(QString merch, member->merch)
    {
      if(merch == "wristBand")
        ui.WristBandCheck->setCheckState(Qt::Checked);
      else if(merch == "TShirt")
        ui.TShirtCheck->setCheckState(Qt::Checked);
      else if(merch == "membership")
        ui.MembershipCheck->setCheckState(Qt::Checked);
      else if(merch == "pack")
        ui.FusePackCheck->setCheckState(Qt::Checked);
    }
  }
}

void userEdit::merchSelectionChanged(int state)
{
  // First check if the fuse pack is checked.
  if(ui.FusePackCheck->checkState() == Qt::Checked)
  {
    ui.WristBandCheck->setCheckState(Qt::Unchecked);
    ui.WristBandCheck->setEnabled(false);
    ui.TShirtCheck->setCheckState(Qt::Unchecked);
    ui.TShirtCheck->setEnabled(false);
    ui.MembershipCheck->setCheckState(Qt::Unchecked);
    ui.MembershipCheck->setEnabled(false);

    // Set the total label to 10 quid.
    ui.TotalLabel->setText(QString::fromUtf8("Total: £10"));
    return;
  }
  else
  {
    ui.WristBandCheck->setEnabled(true);
    ui.TShirtCheck->setEnabled(true);
    ui.MembershipCheck->setEnabled(true);

    // Set the total label to 0 quid.
    ui.TotalLabel->setText(QString::fromUtf8("Total: £0"));
  }

  // Add up the totals if any others are checked.
  unsigned int total = 0;
  if(ui.WristBandCheck->checkState() == Qt::Checked)
    total += 1;
  if(ui.TShirtCheck->checkState() == Qt::Checked)
    total += 6;
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
  if(ui.ProductionCheck->checkState() == Qt::Checked)
    groupsReturnData += "production ";
  if(ui.TVCheck->checkState() == Qt::Checked)
    groupsReturnData += "tv ";
  if(ui.TechCheck->checkState() == Qt::Checked)
    groupsReturnData += "tech ";
  if(ui.PodcastingCheck->checkState() == Qt::Checked)
    groupsReturnData += "podcasting ";
  if(ui.EventsCheck->checkState() == Qt::Checked)
    groupsReturnData += "events ";
  if(ui.MarketingCheck->checkState() == Qt::Checked)
    groupsReturnData += "marketing ";
  if(ui.DJsCheck->checkState() == Qt::Checked)
    groupsReturnData += "dj ";
  if(ui.MusicCheck->checkState() == Qt::Checked)
    groupsReturnData += "music ";
  if(ui.NewsCheck->checkState() == Qt::Checked)
    groupsReturnData += "news ";
  if(ui.PresentersCheck->checkState() == Qt::Checked)
    groupsReturnData += "presenters ";
  if(ui.NewMusicCheck->checkState() == Qt::Checked)
    groupsReturnData += "newmusic ";

  MerchReturnData.clear();;
  if(ui.WristBandCheck->checkState() == Qt::Checked)
    MerchReturnData += "wristBand ";
  if(ui.TShirtCheck->checkState() == Qt::Checked)
    MerchReturnData += "TShirt ";
  if(ui.MembershipCheck->checkState() == Qt::Checked)
    MerchReturnData += "membership ";
  if(ui.FusePackCheck->checkState() == Qt::Checked)
    MerchReturnData += "pack ";

  // We're done.
  accept();
}

void userEdit::selectAllGroups()
{
  ui.DJsCheck->setCheckState(Qt::Checked);
  ui.MusicCheck->setCheckState(Qt::Checked);
  ui.NewMusicCheck->setCheckState(Qt::Checked);
  ui.NewsCheck->setCheckState(Qt::Checked);
  ui.PresentersCheck->setCheckState(Qt::Checked);
  ui.ProductionCheck->setCheckState(Qt::Checked);
  ui.TVCheck->setCheckState(Qt::Checked);
  ui.TechCheck->setCheckState(Qt::Checked);
  ui.PodcastingCheck->setCheckState(Qt::Checked);
  ui.EventsCheck->setCheckState(Qt::Checked);
  ui.MarketingCheck->setCheckState(Qt::Checked);
}


#include "useredit.moc"