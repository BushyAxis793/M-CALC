#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materialsgenre.h"
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QList>
#include<QProcess>
#include "Coating_Area.h"
#include "Density.h"
#include "Surface_Area.h"
#include "Volume.h"

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



QList<MaterialsGenre::Genre> genreStructList;
Volume v;
Density d;
Surface_Area sa;
Coating_Area ca;
QSettings settings("P.W.U.H. METPOL","M-CALC");
QString tempString;
double materialDensity=0;
float materialSurfaceArea=0;
float materialVolume=0;
float materialCoatingArea=0;
float materialMass=0;
float materialCost=0;
float materialPrice=0;
float coatingCost=0;
float coatingPrice=0;
float finalPrice=0;
float finalPriceEuro=0;
float dim1=0,dim2=0,dim3=0,dim4=0,price=0;
float euroRate = 0;

int numberOfZeroGenre=0;
bool isConnection;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    OpenFile(":/Resources/MaterialGenres/Aluminium/AluminiumGenre.txt");

    //Wypełnianie comboboxów
    LoadComboboxes();

    //Akceptacja tylko liczb
    AcceptOnlyDouble();

    PreloadSummary();


    DownloadEuroRate();








}

void MainWindow::DownloadEuroRate()
{
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,[&](QNetworkReply * reply)
    {
            if(reply->bytesAvailable())
            {
                isConnection=true;
            }else
            {
                isConnection=false;
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
                      euroRate = midValue.toDouble();
                      LoadEuroRate();

                  }
              }
          }



    });


   manager->get(QNetworkRequest(QUrl("http://api.nbp.pl/api/exchangerates/rates/a/eur/?format=json")));
}



void MainWindow::SaveEuroRate()
{
    settings.setValue("euroRate",euroRate);
}

void MainWindow::LoadEuroRate()
{
    if(isConnection)
    {
        ui->euroRateTextBox->setText(QString::number(euroRate,'f',2));
    }
    else
    {
        euroRate = settings.value("euroRate",euroRate).toFloat();
        ui->euroRateTextBox->setText(QString::number(euroRate,'f',2));

    }
}

MainWindow::~MainWindow()
{
    SaveEuroRate();
    delete ui;
}

void MainWindow::CalculateFinalEuroPrice()
{
    if(euroRate!=0)
    {
        finalPriceEuro = finalPrice/euroRate;
    }
    else
    {
        finalPriceEuro =0;
    }
    ui->finalPriceEuroTextBox->setText(QString::number(finalPriceEuro,'f',4));
}

void MainWindow::PreloadSummary()
{

    ui->euroRateTextBox->setText(QString::number(euroRate,'f',2));
    ui->finalPriceEuroTextBox->setText(QString::number(0,'f',4));
    ui->materialMassTextBox->setText(QString::number(0,'f',4));
    ui->materialCostTextBox->setText(QString::number(0,'f',4));
    ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
}

void MainWindow::CalculateFinalPrice()
{
    if(ui->coatCheckBox->isChecked())
    {
        ui->coatTypeComboBox->setEnabled(true);
        ui->coatPriceTextBox->setEnabled(true);
        finalPrice = materialCost + coatingCost;
        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->coatCostTextBox->setText(QString::number(coatingCost,'f',4));

    }
    else
    {
        ui->coatTypeComboBox->setEnabled(false);
        ui->coatPriceTextBox->setEnabled(false);
        finalPrice = materialCost;
        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->coatCostTextBox->setText(QString::number(0,'f',4));

    }
}

float MainWindow::ReplaceComma(QString tempString)
{
    tempString.replace(",",".");
    return tempString.toFloat();
}

void MainWindow::on_coatCheckBox_stateChanged()
{
    CalculateFinalPrice();
    CalculateFinalEuroPrice();
}

void MainWindow::on_chooseMaterialShapeComboBox_currentIndexChanged(int index)
{

    switch(ui->chooseMaterialShapeComboBox->currentIndex())
    {
    case 0://Pręt okrągły
        ui->dimension1Label->setText("Średnica zew. [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Długość [mm]");
        ui->dimension2TextBox->setText("");

        ui->dimension3Label->setVisible(false);
        ui->dimension3TextBox->setVisible(false);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);

        dim1=0;
        dim2=0;


        break;
    case 1://Rura okrągła
        ui->dimension1Label->setText("Średnica zew. [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Grubość ściany [mm]");
        ui->dimension2TextBox->setText("");
        ui->dimension3Label->setText("Długość [mm]");
        ui->dimension3TextBox->setText("");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);


        dim1=0;
        dim2=0;
        dim3=0;


        break;
    case 2://Pręt sześciokątny
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Długość [mm]");
        ui->dimension2TextBox->setText("");

        ui->dimension3Label->setVisible(false);
        ui->dimension3TextBox->setVisible(false);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);

        dim1=0;
        dim2=0;


        break;
    case 3://Rura sześciokątna
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Średnica wew. [mm]");
        ui->dimension2TextBox->setText("");
        ui->dimension3Label->setText("Długość [mm]");
        ui->dimension3TextBox->setText("");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);

        dim1=0;
        dim2=0;
        dim3=0;


        break;
    case 4://Pręt kwadratowy
        ui->dimension1Label->setText("Szerokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Długość [mm]");
        ui->dimension2TextBox->setText("");

        ui->dimension3Label->setVisible(false);
        ui->dimension3TextBox->setVisible(false);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);

        dim1=0;
        dim2=0;

        break;
    case 5://Blacha/Płaskownik
        ui->dimension1Label->setText("Grubość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension2TextBox->setText("");
        ui->dimension3Label->setText("Długość [mm]");
        ui->dimension3TextBox->setText("");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);

        dim1=0;
        dim2=0;
        dim3=0;


        break;
    case 6://Profil kwadratowy
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension2TextBox->setText("");
        ui->dimension3Label->setText("Grubość ściany [mm]");
        ui->dimension3TextBox->setText("");
        ui->dimension4Label->setText("Długość [mm]");
        ui->dimension4TextBox->setText("");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(true);
        ui->dimension4TextBox->setVisible(true);

        dim1=0;
        dim2=0;
        dim3=0;
        dim4=0;


        break;
    case 7://Kątownik/Teownik
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension2TextBox->setText("");
        ui->dimension3Label->setText("Grubość ściany [mm]");
        ui->dimension3TextBox->setText("");
        ui->dimension4Label->setText("Długość [mm]");
        ui->dimension4TextBox->setText("");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(true);
        ui->dimension4TextBox->setVisible(true);

        dim1=0;
        dim2=0;
        dim3=0;
        dim4=0;

        break;
    case 8://Ceownik/Dwuteownik
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension2TextBox->setText("");
        ui->dimension3Label->setText("Grubość ściany [mm]");
        ui->dimension3TextBox->setText("");
        ui->dimension4Label->setText("Długość [mm]");
        ui->dimension4TextBox->setText("");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(true);
        ui->dimension4TextBox->setVisible(true);

        dim1=0;
        dim2=0;
        dim3=0;
        dim4=0;


        break;
    }
}

void MainWindow::LoadComboboxes()
{
    ui->coatTypeComboBox->addItem("Anodowanie");
    ui->coatTypeComboBox->addItem("Cynkowanie");
    ui->coatTypeComboBox->addItem("Hartowanie");
    ui->coatTypeComboBox->addItem("Czernienie");

    //Wypełnianie comboboxa kształtu materiału

    ui->chooseMaterialShapeComboBox->addItem("Pręt okrągły");
    ui->chooseMaterialShapeComboBox->addItem("Rura okrągła");
    ui->chooseMaterialShapeComboBox->addItem("Pręt sześciokątny");
    ui->chooseMaterialShapeComboBox->addItem("Rura sześciokątna");
    ui->chooseMaterialShapeComboBox->addItem("Pręt kwadratowy");
    ui->chooseMaterialShapeComboBox->addItem("Blacha/Płaskownik");
    ui->chooseMaterialShapeComboBox->addItem("Profil zamknięty");
    ui->chooseMaterialShapeComboBox->addItem("Kątownik/Teownik");
    ui->chooseMaterialShapeComboBox->addItem("Ceownik/Dwuteownik");

    //Wypełnianie comboboxa rodzaju materiału
    ui->chooseMaterialTypeComboBox->addItem("Aluminium");
    ui->chooseMaterialTypeComboBox->addItem("Stal");
    ui->chooseMaterialTypeComboBox->addItem("Stal nierdzewna");
    ui->chooseMaterialTypeComboBox->addItem("Plastik");
    ui->chooseMaterialTypeComboBox->addItem("Żeliwo");
    ui->chooseMaterialTypeComboBox->addItem("Brąz");
    ui->chooseMaterialTypeComboBox->addItem("Miedź");
    ui->chooseMaterialTypeComboBox->addItem("Mosiądz");
    ui->chooseMaterialTypeComboBox->addItem("Ołów");
}

void MainWindow::AcceptOnlyDouble()
{
    ui->coatPriceTextBox->setValidator(new QDoubleValidator(0,100,2,this));
    ui->dimension1TextBox->setValidator(new QDoubleValidator(0,100,2,this));
    ui->dimension2TextBox->setValidator(new QDoubleValidator(0,100,2,this));
    ui->dimension3TextBox->setValidator(new QDoubleValidator(0,100,2,this));
    ui->dimension4TextBox->setValidator(new QDoubleValidator(0,100,2,this));
    ui->materialPriceTextBox->setValidator(new QDoubleValidator(0,100,2,this));
    ui->euroRateTextBox->setValidator(new QDoubleValidator(0,100,2,this));
    ui->quantityMaterialTextBox->setValidator(new QIntValidator(1,9999,this));

}

void MainWindow::SwitchMaterialType()
{
    MaterialsGenre *mg = new MaterialsGenre();

    switch(ui->chooseMaterialTypeComboBox->currentIndex())
    {
    case 0://Aluminium
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->ALUMINIUM_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();

        break;
    case 1://Stal
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->STEEL_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();

        break;
    case 2://Stal nierdzewna
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->STAINLESSSTEEL_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();

        break;
    case 3://Plastik
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->PLASTIC_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();

        break;
    case 4://Żeliwo
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->CASTIRON_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();

        break;

    case 5: //Brąz
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->BRONZE_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        break;

    case 6: //Miedź
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->COPPER_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        break;

    case 7: //Mosiądz
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->BRASS_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        break;

    case 8: //Ołów
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->LEAD_GENRE);
        SetMaterialDensity();
        CalculateMass();
        numberOfZeroGenre=2;
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        break;

    }

    delete mg;
}

void MainWindow::OpenFile(QString filePath)
{
    MaterialsGenre *mg = new MaterialsGenre();

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Cant open file";
    }


    while(!file.atEnd())
    {
        QString line = file.readLine();
        QStringList list = line.split(" ");
        int i=0;
        int j=1;

        for(; i<list.size();i++)
        {
            ui->chooseMaterialGenreComboBox->addItem(list[i]);
            mg->SetGenre(list[i],list[j].toDouble());
            i++;
        }
        for(; j<list.size();j++)
        {
            j++;

        }
        genreStructList.append(mg->GetGenre());



    }

    file.close();

    delete mg;

}

void MainWindow::SetMaterialDensity()
{
    for (int i=0;i<=ui->chooseMaterialGenreComboBox->currentIndex() ;i++ ) {

        materialDensity = genreStructList[i].materialDensity;
        CalculateMass();
    }
}

#pragma region DIMENSIONS: Text Boxes Change Value{

void MainWindow::on_dimension1TextBox_textEdited(const QString &arg1)
{
    tempString = ui->dimension1TextBox->text();
    dim1 = ReplaceComma(tempString);

    CalculateMass();
    SwitchCoatType();
    CalculateFinalPrice();
    CalculateFinalEuroPrice();

}

void MainWindow::on_dimension2TextBox_textEdited(const QString &arg1)
{
    tempString = ui->dimension2TextBox->text();
    dim2 = ReplaceComma(tempString);


    CalculateMass();
    SwitchCoatType();
    CalculateFinalPrice();
    CalculateFinalEuroPrice();
    CalculateMaterialNeeded();
    if(ui->quantityMaterialTextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));


}

void MainWindow::on_dimension3TextBox_textEdited(const QString &arg1)
{
    tempString = ui->dimension3TextBox->text();
    dim3 = ReplaceComma(tempString);

    CalculateMass();
    SwitchCoatType();
    CalculateFinalPrice();
    CalculateFinalEuroPrice();
    CalculateMaterialNeeded();
    if(ui->quantityMaterialTextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));

}

void MainWindow::on_dimension4TextBox_textEdited(const QString &arg1)
{

    tempString = ui->dimension4TextBox->text();
    dim4 = ReplaceComma(tempString);

    CalculateMass();
    SwitchCoatType();
    CalculateFinalPrice();
    CalculateFinalEuroPrice();
    CalculateMaterialNeeded();
    if(ui->quantityMaterialTextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));

}

void MainWindow::on_materialPriceTextBox_textEdited(const QString &arg1)
{
    tempString = ui->materialPriceTextBox->text();
    materialPrice = ReplaceComma(tempString);

    CalculateMass();
    SwitchCoatType();
    CalculateFinalPrice();
    CalculateFinalEuroPrice();

    if(tempString!="")
    {
        ui->materialPriceEuroTextBox->setEnabled(false);
    }
    else
    {
        ui->materialPriceEuroTextBox->setEnabled(true);
    }
}

void MainWindow::on_materialPriceEuroTextBox_textEdited(const QString &arg1)
{
    float materialPriceEuro=0;
    tempString = ui->materialPriceEuroTextBox->text();
    materialPriceEuro = ReplaceComma(tempString);
    materialPrice = materialPriceEuro*euroRate;



    CalculateMass();
    SwitchCoatType();
    CalculateFinalPrice();
    CalculateFinalEuroPrice();

    if(tempString!="")
    {
        ui->materialPriceTextBox->setEnabled(false);
    }
    else
    {
        ui->materialPriceTextBox->setEnabled(true);
    }
}

#pragma endregion}

void MainWindow::CalculateMass()
{
    switch(ui->chooseMaterialShapeComboBox->currentIndex())
    {
    case 0://Pret

        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateRoundRod(dim1,dim2));
        materialSurfaceArea = sa.CalculateRoundRod(dim1,dim2);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 1://Rura okragla
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateRoundPipe(dim1,dim2,dim3));
        materialSurfaceArea = sa.CalculateRoundPipe(dim1,dim2,dim3);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 2:// Pret szesciokatny
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateHexagonalRod(dim1,dim2));
        materialSurfaceArea = sa.CalculateHexagonalRod(dim1,dim2);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 3://Rura szesciokatna
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateHexagonalPipe(dim1,dim2,dim3));
        materialSurfaceArea = sa.CalculateHexagonalPipe(dim1,dim2,dim3);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 4://Pret kwadratory
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateSquareRod(dim1,dim2));
        materialSurfaceArea = sa.CalculateSquareRod(dim1,dim2);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 5://Blacha/Plaskownik
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculatePlate(dim1,dim2,dim3));
        materialSurfaceArea = sa.CalculatePlate(dim1,dim2,dim3);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 6://Profil zamkniety
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateSquareProfile(dim1,dim2,dim3,dim4));
        materialSurfaceArea = sa.CalculateSquareProfile(dim1,dim2,dim3,dim4);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 7://Katownik
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateAngleProfile(dim1,dim2,dim3,dim4));
        materialSurfaceArea = sa.CalculateAngleProfile(dim1,dim2,dim3,dim4);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    case 8://Ceownik
        materialMass = d.CalculateMaterialMass(materialDensity,v.CalculateCProfile(dim1,dim2,dim3,dim4));
        materialSurfaceArea = sa.CalculateCProfile(dim1,dim2,dim3,dim4);
        materialCost = d.CalculateMaterialPrice(materialMass,materialPrice);
        finalPrice = materialCost;


        ui->finalPriceTextBox->setText(QString::number(finalPrice,'f',4));
        ui->materialMassTextBox->setText(QString::number(materialMass,'f',4));
        ui->materialCostTextBox->setText(QString::number(materialCost,'f',4));

        CalculateFinalEuroPrice();

        break;
    }
}

void MainWindow::SwitchCoatType()
{
    switch (ui->coatTypeComboBox->currentIndex())
    {
    case 0:
        coatingCost = ca.CalculateAnodizingCost(materialSurfaceArea,coatingPrice);
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        ui->coatCostTextBox->setText(QString::number(coatingCost,'f',4));
        break;
    case 1:
        coatingCost = ca.CalculateGalvanizingCost(materialMass,coatingPrice);
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        ui->coatCostTextBox->setText(QString::number(coatingCost,'f',4));
        break;
    case 2:
        coatingCost = ca.CalculateHardeningCost(materialMass,coatingPrice);
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        ui->coatCostTextBox->setText(QString::number(coatingCost,'f',4));
        break;
    case 3:
        coatingCost = ca.CalculateBlackeningCost(materialMass,coatingPrice);
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
        ui->coatCostTextBox->setText(QString::number(coatingCost,'f',4));
        break;
    }
}

void MainWindow::on_coatTypeComboBox_currentIndexChanged(int index)
{
    CalculateFinalEuroPrice();

    SwitchCoatType();
}

void MainWindow::on_coatPriceTextBox_textEdited(const QString &arg1)
{
    tempString = ui->coatPriceTextBox->text();
    coatingPrice = ReplaceComma(tempString);

    SwitchCoatType();
    CalculateFinalPrice();
}

void MainWindow::on_euroRateTextBox_textEdited(const QString &arg1)
{
    tempString = ui->euroRateTextBox->text();
    euroRate = ReplaceComma(tempString);

    CalculateFinalEuroPrice();
}

void MainWindow::on_chooseMaterialGenreComboBox_currentIndexChanged(int index)
{
    if(ui->chooseMaterialGenreComboBox->currentIndex()==0)
    {
        numberOfZeroGenre++;
        qDebug()<<numberOfZeroGenre;

        if(numberOfZeroGenre>2)
        {
            SetMaterialDensity();
            SwitchCoatType();
            CalculateFinalPrice();
            CalculateFinalEuroPrice();
        }
    }
    else
    {
        SetMaterialDensity();
        SwitchCoatType();
        CalculateFinalPrice();
        CalculateFinalEuroPrice();
    }

}

void MainWindow::on_chooseMaterialTypeComboBox_currentIndexChanged(int index)
{
    SwitchMaterialType();
    SwitchCoatType();

}





void MainWindow::on_quantityMaterialTextBox_textEdited(const QString &arg1)
{
    if(ui->quantityMaterialTextBox->text()!="")
    {
        ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',0));
        CalculateMaterialNeeded();
    }
    else
    {
        ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
    }



}

void MainWindow::CalculateMaterialNeeded()
{
    auto quantity = ui->quantityMaterialTextBox->text().toInt();
    float tempVal{0};

    switch (ui->chooseMaterialShapeComboBox->currentIndex()) {
    case 0:
        tempVal = quantity*dim2;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension2TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));

        break;
    case 1:
        tempVal = quantity*dim3;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension3TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;
    case 2:
        tempVal = quantity*dim2;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension2TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;
    case 3:
        tempVal = quantity*dim3;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension3TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;
    case 4:
        tempVal = quantity*dim2;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension2TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;
    case 5:
        tempVal = quantity*dim3;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension3TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;
    case 6:
        tempVal = quantity*dim4;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension4TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;
    case 7:
        tempVal = quantity*dim4;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension4TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;
    case 8:
        tempVal = quantity*dim4;
        ui->amountMaterialNeededTextBox->setText(std::to_string(tempVal).c_str());
        ui->amountMaterialNeededTextBox->setText(QString::number(tempVal,'f',0));
        if(ui->dimension4TextBox->text()=="") ui->amountMaterialNeededTextBox->setText(QString::number(0,'f',4));
        break;


    }

}
