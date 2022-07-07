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

void Euro::SetFinalPriceEuro(float price)
{
    finalPriceEuro = price;
}

float Euro::GetFinalPriceEuro() const
{
    return finalPriceEuro;
}

void Euro::SetFinalPrice(float price)
{
    finalPrice = price;
}

float Euro::GetFinalPrice() const
{
    return finalPrice;
}

void Euro::SaveEuroRate(){
    settings.setValue("euroRate",currencyRate.GetEuroRate());
    qDebug()<<"Zapisano!";
}






}

