#include "useredit.h"

userEdit::userEdit(QWidget* parent, Qt::WindowFlags f, FuseMember* member): QDialog(parent, f)
{
  ui.setupUi(this);

  if(!member)
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
