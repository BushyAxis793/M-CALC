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

QList<MaterialsGenre::Genre> genreStructList;
Volume v;
Density d;
Surface_Area sa;
Coating_Area ca;
QSettings settings("P.W.U.H. METPOL","M-CALC");
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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenFile(":/Resources/MaterialGenres/Aluminium/AluminiumGenre.txt");
    materialDensity = genreStructList[0].materialDensity;

    //Wypełnianie comboboxów
    LoadComboboxes();

    //Akceptacja tylko liczb
    AcceptOnlyDouble();

    PreloadSummary();

    LoadEuroRate();

}

void MainWindow::SaveEuroRate()
{
    settings.setValue("euroRate",euroRate);
}

void MainWindow::LoadEuroRate()
{
    euroRate = settings.value("euroRate",euroRate).toFloat();
    ui->euroRateTextBox->setText(QString::number(euroRate,'f',2));
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
        SwitchMaterialType();

        break;
    case 1://Rura okrągła
        ui->dimension1Label->setText("Średnica wew. [mm]");
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
        SwitchMaterialType();

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
        SwitchMaterialType();

        break;
    case 3://Rura sześciokątna
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Średnica zew. [mm]");
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
        SwitchMaterialType();

        break;
    case 4://Pręt kwadratowy
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension1TextBox->setText("");
        ui->dimension2Label->setText("Długość [mm]");
        ui->dimension2TextBox->setText("");

        ui->dimension3Label->setVisible(false);
        ui->dimension3TextBox->setVisible(false);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);

        SwitchMaterialType();

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
        SwitchMaterialType();

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
        SwitchMaterialType();

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

        SwitchMaterialType();

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
        SwitchMaterialType();

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

        break;
    case 1://Stal
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->STEEL_GENRE);


        break;
    case 2://Stal nierdzewna
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->STAINLESSSTEEL_GENRE);


        break;
    case 3://Plastik
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->PLASTIC_GENRE);


        break;
    case 4://Żeliwo
        ui->chooseMaterialGenreComboBox->clear();
        genreStructList.clear();
        OpenFile(mg->CASTIRON_GENRE);


        break;

    }

    delete mg;
}

void MainWindow::on_chooseMaterialTypeComboBox_currentIndexChanged(int index)
{

    //SwitchMaterialType();
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

void MainWindow::on_chooseMaterialGenreComboBox_currentIndexChanged(int index)
{

}

void MainWindow::SetMaterialDensity()
{

    for (int i=0;i<=ui->chooseMaterialGenreComboBox->currentIndex() ;i++ ) {

        materialDensity = genreStructList[i].materialDensity;

    }

}

#pragma region DIMENSIONS: Text Boxes Change Value{

void MainWindow::on_dimension1TextBox_textEdited(const QString &arg1)
{
    QString tempString = ui->dimension1TextBox->text();
    tempString.replace(",",".");
    dim1 = tempString.toFloat();

    CalculateMass();
    CalculateFinalEuroPrice();
}

void MainWindow::on_dimension2TextBox_textEdited(const QString &arg1)
{
    QString tempString = ui->dimension2TextBox->text();
    tempString.replace(",",".");
    dim2 = tempString.toFloat();


    CalculateMass();
    CalculateFinalEuroPrice();
}

void MainWindow::on_dimension3TextBox_textEdited(const QString &arg1)
{
    QString tempString = ui->dimension3TextBox->text();
    tempString.replace(",",".");
    dim3 = tempString.toFloat();

    CalculateMass();
    CalculateFinalEuroPrice();
}

void MainWindow::on_dimension4TextBox_textEdited(const QString &arg1)
{

    QString tempString = ui->dimension4TextBox->text();
    tempString.replace(",",".");
    dim4 = tempString.toFloat();

    CalculateMass();
    CalculateFinalEuroPrice();
}

void MainWindow::on_materialPriceTextBox_textEdited(const QString &arg1)
{
    QString tempString = ui->materialPriceTextBox->text();
    tempString.replace(",",".");
    materialPrice = tempString.toFloat();

    CalculateMass();
    CalculateFinalEuroPrice();
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
    CalculateFinalEuroPrice();

    SwitchCoatType();
}


void MainWindow::on_coatPriceTextBox_textEdited(const QString &arg1)
{
    QString tempString = ui->coatPriceTextBox->text();
    tempString.replace(",",".");
    coatingPrice = tempString.toFloat();

    SwitchCoatType();
    CalculateFinalPrice();


}


void MainWindow::on_euroRateTextBox_textEdited(const QString &arg1)
{
    QString tempString = ui->euroRateTextBox->text();
    tempString.replace(",",".");
    euroRate = tempString.toFloat();

    CalculateFinalEuroPrice();
}

