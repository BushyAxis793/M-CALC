#include "materialsgenre.h"
#include <QDebug>

MaterialsGenre::mGenre mg;

MaterialsGenre::MaterialsGenre()
{

}

MaterialsGenre::mGenre MaterialsGenre::GetGenre()
{
    return mg;
}
void MaterialsGenre::SetGenre(std::string genreName ,double genreDensity)
{
    mg.materialGenre = genreName;
    mg.materialDensity = genreDensity;
}
void MaterialsGenre::OpenFile()
{
    std::ifstream file;

    std::string genreName;
    double genreDensity;

    file.open("//Resources//Steel//SteelGenre.txt");

    if(file.is_open())
    {
            while(getline(file,genreName))
            {
                qDebug()<<QString::fromStdString(genreName);
            }
            qDebug()<<"plik otwarty";
            file.close();
    }
    qDebug()<<"Plik nie został otwarty";
}
