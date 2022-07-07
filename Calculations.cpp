#include "Calculations.h"
#include "Currencies.h"

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

void Calculations::CalculateFinalEuroPrice()
{
    std::unique_ptr<Currency::Euro> currencyRate (new(Currency::Euro));

    if(currencyRate->GetEuroRate()!=0)
    {
        currencyRate->SetFinalPriceEuro(currencyRate->GetFinalPrice()/currencyRate->GetEuroRate());
        //finalPriceEuro = finalPrice/currencyRate.GetEuroRate();
    }
    else
    {
        currencyRate->SetFinalPriceEuro(0);
    }
}
