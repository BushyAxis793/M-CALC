#include "Density.h"



float Density::CalculateMaterialMass(float &materialDensity,float materialVolume)
{

    float finalMaterialMass = materialDensity * materialVolume;

    std::cout<<finalMaterialMass<<std::endl;
	
    return finalMaterialMass;
}

float Density::CalculateMaterialPrice(float &materialMass,float &massPrice)
{
    float finalMaterialPrice = materialMass * massPrice;
	
    return finalMaterialPrice;
}




