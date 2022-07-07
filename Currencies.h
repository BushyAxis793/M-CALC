#ifndef CURRENCIES_H
#define CURRENCIES_H


#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QList>
#include <QProcess>
#include <QRegularExpression>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtXml>
#include <QDebug>
#include <string.h>
#include <QDomElement>
#include <QDomDocument>
#include <QFile>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Connections.h"

namespace Currency {

    class Euro
    {


    private:
        Ui::MainWindow *ui;
        float euroRate=0;
        float finalPriceEuro = 0;
        float finalPrice = 0;
        QString const urlEuroString = "http://api.nbp.pl/api/exchangerates/rates/a/eur/?format=json";

    public:
        float GetEuroRate() const;
        void SetEuroRate(double);

        void SetFinalPriceEuro(float);
        float GetFinalPriceEuro() const;

        void SetFinalPrice(float);
        float GetFinalPrice() const;

        QString GetEuroUrl() const;

        void SaveEuroRate();


    };
}

#endif // CURRENCIES_H
