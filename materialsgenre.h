#ifndef MATERIALSGENRE_H
#define MATERIALSGENRE_H

#include <string>
#include <fstream>
#include <iostream>

class MaterialsGenre
{
public:
    struct mGenre
    {
        std::string materialGenre;
        double materialDensity;
    };


    MaterialsGenre();
    mGenre GetGenre();
    void SetGenre(std::string,double);
    void OpenFile();
};

#endif // MATERIALSGENRE_H
