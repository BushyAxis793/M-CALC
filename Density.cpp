#include "Density.h"



float Density::CalculateMaterialMass(float materialDensity,float materialVolume)
{

    float finalMaterialMass = materialDensity * materialVolume;

    std::cout<<finalMaterialMass<<std::endl;
	
    return finalMaterialMass;
}

float Density::CalculateMaterialPrice(float materialMass,float massPrice)
{
    float finalMaterialPrice = materialMass * massPrice;
	
    return finalMaterialPrice;
}

void Density::SetMaterialDensity(float density)
{
    materialDensity = density;
}

float Density::GetMaterialDensity() const
{
    return materialDensity;
}


void Density::SetMaterialMass(float mass)
{
    materialMass = mass;
}

float Density::GetMaterialMass() const
{
    return materialMass;
}

