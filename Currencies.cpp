#include"Currencies.h"



namespace Currency {

Connection::Status connectStatus;
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


    if(connectStatus.GetConnectionStatus())
    {
        ui->euroRateTextBox->setText(QString::number(currencyRate.GetEuroRate(),'f',2));
    }
    else
    {
        currencyRate.SetEuroRate(settings.value("euroRate",currencyRate.GetEuroRate()).toFloat());
        ui->euroRateTextBox->setText(QString::number(currencyRate.GetEuroRate(),'f',2));

    }


}


void Euro::SaveEuroRate(){
    settings.setValue("euroRate",currencyRate.GetEuroRate());
}






}

