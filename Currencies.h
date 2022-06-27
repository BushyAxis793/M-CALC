#ifndef CURRENCIES_H
#define CURRENCIES_H


#include <QSettings>
#include <QString>
#include <QMainWindow>
#include <QDomElement>
#include <QDomDocument>
#include <QFile>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QList>
#include <QProcess>
#include <QRegularExpression>



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Connections.h"

namespace Currency {

    class Euro
    {
    private:
        float euroRate=0;
        QString const urlEuroString = "http://api.nbp.pl/api/exchangerates/rates/a/eur/?format=json";
        QNetworkAccessManager *manager;
    public:
        float GetEuroRate() const;
        void SetEuroRate(float);

        QString GetEuroUrl() const;

        void LoadEuroRate(Ui::MainWindow *ui);

        void DownloadEuroRate();
    };
}

#endif // CURRENCIES_H
