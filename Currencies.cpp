#include"Currencies.h"



namespace Currency {

Connection::Status connectSta;
Euro currencyRate;
Ui::MainWindow *ui;

QSettings settings;

float Euro::GetEuroRate() const{
    return euroRate;
}

void Euro::SetEuroRate(float rateValue){
    euroRate = rateValue;
}

QString Euro::GetEuroUrl() const{
    return urlEuroString;
}

void Euro::LoadEuroRate(Ui::MainWindow *ui){


    if(connectSta.GetConnectionStatus())
    {
        ui->euroRateTextBox->setText(QString::number(currencyRate.GetEuroRate(),'f',2));
    }
    else
    {
        currencyRate.SetEuroRate(settings.value("euroRate",currencyRate.GetEuroRate()).toFloat());
        ui->euroRateTextBox->setText(QString::number(currencyRate.GetEuroRate(),'f',2));

    }


}

void Euro::DownloadEuroRate(){

     manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,[&](QNetworkReply * reply)
            {


                if(reply->bytesAvailable())
                {
                    connectSta.SetConnectionStatus(true);
                }else
                {
                    connectSta.SetConnectionStatus(false);
                }

                QString  stringData = reply->readAll();
                QFile file("temp.json");
                QTextStream stream(&file);
                if(file.open(QIODevice::WriteOnly|QIODevice::Text))
                {
                    stream<<stringData;
                }

                file.close();

                QJsonDocument doc = QJsonDocument::fromJson(stringData.toUtf8());

                QJsonObject rootObj = doc.object();


                QJsonValue rates = rootObj.value("rates");

                if (rates.type() == QJsonValue::Array) {

                    QJsonArray ratesArray = rates.toArray();

                    for (int i = 0; i < ratesArray.count(); i++) {

                        QJsonValue ratesChild = ratesArray.at(i);

                        if (ratesChild.type() == QJsonValue::Object) {

                            QJsonObject ratesObj = ratesChild.toObject();

                            QJsonValue midValue = ratesObj.value("mid");
                            currencyRate.SetEuroRate(midValue.toDouble());
                            //LoadEuroRate();
                            currencyRate.LoadEuroRate(ui);

                        }
                    }
                }



            });


    manager->get(QNetworkRequest(QUrl(currencyRate.GetEuroUrl())));
}


}

