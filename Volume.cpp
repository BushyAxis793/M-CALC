#include "Volume.h"


//Obliczanie objêtoœci materia³u - definicje

//Prêt okr¹g³y
float Volume::CalculateRoundRod(float diameter_out ,float length)
{
	float r = diameter_out/2;
    float l = length;
    float circle_surface_area,  final_volume;
    
    circle_surface_area = M_PI*pow(r,2);
    
    final_volume = circle_surface_area*l;
  
    return final_volume/1000000;
}

//rura okr¹g³a
float Volume::CalculateRoundPipe(float diameter_out,float wall_thickness,float length)
{
	float r_out = diameter_out/2;
    float b = wall_thickness;
    float l = length;
    float diameter_in = diameter_out-2*b;
    float r_in = diameter_in/2;
    
    float circle_surface_area_out,circle_surface_area_in, volume_out,volume_in,final_volume; 
    
    circle_surface_area_out = M_PI*pow(r_out,2);
    
    circle_surface_area_in =  M_PI*pow(r_in,2);
    
    volume_out = circle_surface_area_out*l;
    
	volume_in = circle_surface_area_in*l;
    
    final_volume = volume_out - volume_in;
    
    return final_volume/1000000;
}

//prêt szeœciok¹tny
float Volume::CalculateHexagonalRod(float height, float length)
{
    float h = height;
    float l = length;
    float side;
    float final_volume;
    
    side = h/sqrt(3);
    
    final_volume = ((3*pow(side,2)*sqrt(3))/2)*l;
    
    return final_volume/1000000;
}

//rura szeœciok¹tna
float Volume::CalculateHexagonalPipe(float height,float diameter_in,float length)
{
    float h = height;
    float r_in = diameter_in/2;
    float l = length;
    float circle_surface_area_in, side, volume_in,volume_out,final_volume;
    
   	side = h/sqrt(3);
    
    volume_out = ((3*pow(side,2)*sqrt(3))/2)*l;
    
    circle_surface_area_in = M_PI*pow(r_in,2);
    
    volume_in = circle_surface_area_in * l;
    
    final_volume = volume_out - volume_in;
    
    return final_volume/1000000;
    
}

//prêt kwadratowy
float Volume::CalculateSquareRod(float side,float length)
{
    float a = side;
    float l = length;
    float final_volume;
    
    final_volume = pow(a,2)*l;
    
    return final_volume/1000000;
}

//blacha/plaskownik
float Volume::CalculatePlate(float thickness,float width,float length)
{
    float a = width;
    float b = thickness;
    float c = length;
    float final_volume;
    
    final_volume = a*b*c;
    
    return final_volume/1000000;
}

//profil kwadratowy
float Volume::CalculateSquareProfile(float height,float width,float wall_thickness,float length)
{
    float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float a_in = a-c*2;
    float b_in = b-c*2;
    float volume_in,volume_out,final_volume;
    
    volume_out = a*b*l;
    
    volume_in = a_in*b_in*l;
    
    final_volume = volume_out - volume_in;
    
    return final_volume/1000000;
}

//k¹townik
float Volume::CalculateAngleProfile(float height,float width,float wall_thickness,float length)
{
	float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float volume_1,volume_2,final_volume;
    
    volume_1 = a*c*l;
    
    volume_2 = (b-c)*c*l;
    
    final_volume = volume_1 + volume_2;
    
    return final_volume/1000000;

}

//ceownik
float Volume::CalculateCProfile(float height,float width,float wall_thickness,float length)
{
    float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float volume_1,volume_2,final_volume;
    
    volume_1 = (b-c)*c*l;
    
    volume_2 = a*c*l;
    
    final_volume = volume_1*2 + volume_2;
    
    return final_volume/1000000;
}

//teownik
float Volume::CalculateTProfile(float height,float width,float wall_thickness,float length)
{
	float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float volume_1,volume_2,final_volume;
    
    volume_1 = a*c*l;
    
    volume_2 = (b-c)*c*l;
    
    final_volume = volume_1 + volume_2;
    
    return final_volume/1000000;
}

//dwuteownik
float Volume::Calculate2TProfile(float height,float width,float wall_thickness,float length)
{
	float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float volume_1,volume_2,final_volume;
    
    volume_1 = (b-c)*c*l;
    
    volume_2 = a*c*l;
    
    final_volume = volume_1*2 + volume_2;
    
    return final_volume/1000000;

}

