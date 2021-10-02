#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materialsgenre.h"
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QList>
#include "Coating_Area.h"
#include "Density.h"
#include "Surface_Area.h"
#include "Volume.h"


QList<MaterialsGenre::Genre> genreStructList;
Volume v;
Density d;
Surface_Area sa;
Coating_Area ca;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Wypełnianie comboboxów
    LoadComboboxes();

    //Akceptacja tylko liczb
    AcceptOnlyDouble();



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_coatCheckBox_stateChanged()
{
    if(ui->coatCheckBox->isChecked())
    {
        ui->coatTypeComboBox->setEnabled(true);
        ui->coatPriceTextBox->setEnabled(true);
    }
    else
    {
        ui->coatTypeComboBox->setEnabled(false);
        ui->coatPriceTextBox->setEnabled(false);
    }
}


void MainWindow::on_chooseMaterialShapeComboBox_currentIndexChanged(int index)
{
    switch(ui->chooseMaterialShapeComboBox->currentIndex())
    {
    case 0://Pręt okrągły
        ui->dimension1Label->setText("Średnica zew. [mm]");
        ui->dimension2Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(false);
        ui->dimension3TextBox->setVisible(false);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);

        qDebug()<<v.CalculateRoundRod((ui->dimension1TextBox->text().toFloat()),ui->dimension2TextBox->text().toFloat());//Dokończyć




        break;
    case 1://Rura okrągła
        ui->dimension1Label->setText("Średnica zew. [mm]");
        ui->dimension2Label->setText("Grubość ściany [mm]");
        ui->dimension3Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);
        break;
    case 2://Pręt sześciokątny
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension2Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(false);
        ui->dimension3TextBox->setVisible(false);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);
        break;
    case 3://Rura sześciokątna
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension2Label->setText("Średnica zew. [mm]");
        ui->dimension3Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);
        break;
    case 4://Pręt kwadratowy
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension2Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(false);
        ui->dimension3TextBox->setVisible(false);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);
        break;
    case 5://Blacha/Płaskownik
        ui->dimension1Label->setText("Grubość [mm]");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension3Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(false);
        ui->dimension4TextBox->setVisible(false);
        break;
    case 6://Profil kwadratowy
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension3Label->setText("Grubość ściany [mm]");
        ui->dimension4Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(true);
        ui->dimension4TextBox->setVisible(true);
        break;
    case 7://Kątownik/Teownik
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension3Label->setText("Grubość ściany [mm]");
        ui->dimension4Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(true);
        ui->dimension4TextBox->setVisible(true);
        break;
    case 8://Ceownik/Dwuteownik
        ui->dimension1Label->setText("Wysokość [mm]");
        ui->dimension2Label->setText("Szerokość [mm]");
        ui->dimension3Label->setText("Grubość ściany [mm]");
        ui->dimension4Label->setText("Długość [mm]");

        ui->dimension3Label->setVisible(true);
        ui->dimension3TextBox->setVisible(true);
        ui->dimension4Label->setVisible(true);
        ui->dimension4TextBox->setVisible(true);
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
}

void MainWindow::on_chooseMaterialTypeComboBox_currentIndexChanged(int index)
{
    MaterialsGenre *mg = new MaterialsGenre();

    switch(ui->chooseMaterialTypeComboBox->currentIndex())
    {
    case 0://Aluminium
        ui->chooseMaterialGenreComboBox->clear();
        OpenFile(mg->ALUMINIUM_GENRE);
        break;
    case 1://Stal
        ui->chooseMaterialGenreComboBox->clear();
        OpenFile(mg->STEEL_GENRE);
        break;
    case 2://Stal nierdzewna
        ui->chooseMaterialGenreComboBox->clear();
        OpenFile(mg->STAINLESSSTEEL_GENRE);
        break;
    case 3:
        ui->chooseMaterialGenreComboBox->clear();
        OpenFile(mg->PLASTIC_GENRE);
        break;
    case 4:
        ui->chooseMaterialGenreComboBox->clear();
        OpenFile(mg->CASTIRON_GENRE);
        break;

    }

    delete mg;
}


void MainWindow::OpenFile( QString filePath)
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

