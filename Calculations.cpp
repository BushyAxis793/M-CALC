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

void Calculations::CalculateFinalEuroPrice(Currency::Euro &currency)
{

    if(currency.GetEuroRate()!=0)
    {
        currency.SetFinalPriceEuro(currency.GetFinalPrice()/currency.GetEuroRate());
        //finalPriceEuro = finalPrice/currencyRate.GetEuroRate();
    }
    else
    {
        currency.SetFinalPriceEuro(0);
    }
}
