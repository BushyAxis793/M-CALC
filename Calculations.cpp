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

void Calculations::SetDimension1(float dimension)
{
    dimension1 = dimension;
}

float Calculations::GetDimension1() const
{
    return dimension1;
}


void Calculations::SetDimension2(float dimension)
{
    dimension2 = dimension;
}

float Calculations::GetDimension2() const
{
    return dimension2;
}


void Calculations::SetDimension3(float dimension)
{
    dimension3 = dimension;
}

float Calculations::GetDimension3() const
{
    return dimension3;
}


void Calculations::SetDimension4(float dimension)
{
    dimension4 = dimension;
}

float Calculations::GetDimension4() const
{
    return dimension4;
}
