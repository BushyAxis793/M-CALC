#ifndef MATERIALSGENRE_H
#define MATERIALSGENRE_H

#include <string>
#include <fstream>
#include <iostream>
#include <QString>

class MaterialsGenre
{
public:
    const QString STEEL_GENRE = ":/Resources/MaterialGenres/Steel/SteelGenre.txt";
    const QString ALUMINIUM_GENRE = ":/Resources/MaterialGenres/Aluminium/AluminiumGenre.txt";
    const QString STAINLESSSTEEL_GENRE = ":/Resources/MaterialGenres/StainlessSteel/StainlessSteelGenre.txt";
    const QString PLASTIC_GENRE = ":/Resources/MaterialGenres/Plastic/PlasticsGenre.txt";
    const QString CASTIRON_GENRE = ":/Resources/MaterialGenres/CastIron/CastIronGenre.txt";
    const QString BRONZE_GENRE = ":/Resources/MaterialGenres/Bronze/BronzeGenre.txt";
    const QString COPPER_GENRE = ":/Resources/MaterialGenres/Copper/CopperGenre.txt";
    const QString BRASS_GENRE = ":/Resources/MaterialGenres/Brass/BrassGenre.txt";
    const QString LEAD_GENRE = ":/Resources/MaterialGenres/Lead/LeadGenre.txt";

    struct Genre
    {
        QString materialGenre;
        double materialDensity;
    };

    MaterialsGenre();
    Genre GetGenre();
    void SetGenre(QString,double);

};

#endif // MATERIALSGENRE_H
