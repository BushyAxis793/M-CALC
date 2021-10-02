#include "Calculations.h"

Calculations::MaterialGenre mg;

Calculations::MaterialGenre Calculations::GetGenre()
{
	return mg;
}

void Calculations::SetGenre(string name, string genre, double density)
{
	mg.material_name = name;
	mg.material_genre_name = genre;
	mg.material_density = density;
}
