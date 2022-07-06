#include"Currencies.h"



namespace Currency {

Connection::Status connectStatus;
Euro currencyRate;
Ui::MainWindow *ui;

QSettings settings;



float Euro::GetEuroRate() const{
    return euroRate;
}

void Euro::SetEuroRate(double rateValue){
    euroRate = rateValue;
}

QString Euro::GetEuroUrl() const{
    return urlEuroString;
}


void Euro::SaveEuroRate(){
    settings.setValue("euroRate",currencyRate.GetEuroRate());
    qDebug()<<"Zapisano!";
}






}

