#ifndef UPLOADDIALOG_H
#define UPLOADDIALOG_H

#include <QtGui/QDialog>
#include "ui_uploadDialog.h"
#include <QNetworkReply>

class uploadDialog : public QDialog
{
  Q_OBJECT
  public:
    uploadDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);
  public slots:
    void uploadFinish(QNetworkReply* reply);

  private:
    Ui::uploadDialog ui;
};

#endif // UPLOADDIALOG_H
