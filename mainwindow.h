#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QMessageBox>
#include "apihandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void requestDone(ApiHandler::Data pData);
    void showErrorMessage(QString pErrorMessage);

private:
    Ui::MainWindow *ui;
    QMap<QString,QString> mCountryCodeMap;
    QString mCityName;
    ApiHandler* mApiHandler = nullptr;

private slots:
    void getWeather();
};
#endif // MAINWINDOW_H
