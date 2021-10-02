#include "materialsgenre.h"



MaterialsGenre::Genre mg;

MaterialsGenre::MaterialsGenre()
{

}

MaterialsGenre::Genre MaterialsGenre::GetGenre()
{
    return mg;
}
void MaterialsGenre::SetGenre(QString genreName ,double genreDensity)
{
    mg.materialGenre = genreName;
    mg.materialDensity = genreDensity;
}

