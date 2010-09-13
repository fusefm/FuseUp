#include "uploaddialog.h"
#include <QMessageBox>

uploadDialog::uploadDialog(QWidget* parent, Qt::WindowFlags f): QDialog(parent, f)
{
  ui.setupUi(this);
  setFixedSize(size());
}

void uploadDialog::uploadFinish(QNetworkReply* reply)
{
  if(reply->error() == QNetworkReply::NoError)
  {
    QMessageBox::information(this, "Upload", "The file has been successfully uploaded.");
    accept();
  }
  else
  {
    QMessageBox::critical(this, "Upload", "The upload has failed. Please contact support.");
    reject();
  }
}

#include "uploaddialog.moc"