#include "Calculations.h"

Calculations::MaterialGenre mg;

Calculations::MaterialGenre Calculations::GetGenre()
{
	return mg;
}

void Calculations::SetGenre(string name, string genre, double density)
{
    mg.materialName = name;
    mg.materialGenreName = genre;
    mg.materialDensity = density;
}
