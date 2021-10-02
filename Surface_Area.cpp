#include "Surface_Area.h"

//Obliczanie pola powierchni materia³u  - definicje

//prêt okr¹g³y
float Surface_Area::CalculateRoundRod(float diameter_out,float length)
{

    float r = diameter_out/2;
    float l = length;
    float circle_surface_area, side_surface, final_surface_area;
    
    circle_surface_area = M_PI*pow(r,2);
    
    side_surface = 2*M_PI*r*l;
    
    final_surface_area = 2*circle_surface_area + side_surface;
  
    return final_surface_area/10000;
}

//rura okr¹g³a
float Surface_Area::CalculateRoundPipe(float diameter_out,float wall_thickness,float length)
{
    float r_out = diameter_out/2;
    float b = wall_thickness;
    float l = length;
    float diameter_in = diameter_out-2*b;
    float r_in = diameter_in/2;
    
    float circle_surface_area_out, side_surface_out,final_surface_area_out, 
    circle_surface_area_in,side_surface_in,final_surface_area_in, 
    final_surface_area;
    
    circle_surface_area_out = M_PI*pow(r_out,2);
    
    side_surface_out = 2*M_PI*r_out*l;
    
    circle_surface_area_in = M_PI*pow(r_in,2);
    
    side_surface_in = 2*M_PI*r_in*l;
    
    final_surface_area_out = 2*circle_surface_area_out + side_surface_out;
    
    final_surface_area_in = 2*circle_surface_area_in + side_surface_in;
    
    final_surface_area = final_surface_area_out - final_surface_area_in;
    
    return final_surface_area/10000;
    
}

//prêt szeœciok¹tny
float Surface_Area::CalculateHexagonalRod(float height, float length)
{
    float h = height;
    float l = length;
    float side;
    float final_surface_area;
    
    side = h/sqrt(3);
    
    final_surface_area = (3*pow(side,2)*sqrt(3))/2;
    
    return final_surface_area/10000;
}

//rura szeœciok¹tna
float Surface_Area::CalculateHexagonalPipe(float height,float diameter_in,float length)
{
    float h = height;
    float r_in = diameter_in/2;
    float l = length;
    float circle_surface_area, side_surface, final_surface_area_in,final_surface_area_out,final_surface_area;
    
    
    circle_surface_area = M_PI*pow(r_in,2);
    
    side_surface = 2*M_PI*r_in*l;
    
    final_surface_area_in = 2*circle_surface_area + side_surface;
    
    final_surface_area_out =  CalculateHexagonalRod(h,l);
    
    final_surface_area = final_surface_area_out - final_surface_area_in;
    
    return final_surface_area/10000;
    
}

//prêt kwadratowy
float Surface_Area::CalculateSquareRod(float side,float length)
{
    float a = side;
    float l = length;
    float side_surface,square_surface,final_surface_area;
    
    square_surface = 2*pow(a,2);
    
    side_surface = (a*l)*4;
    
    final_surface_area = square_surface + side_surface;
    
    return final_surface_area/10000;
}

//blacha/plaskownik
float Surface_Area::CalculatePlate(float thickness,float width,float length)
{
    float a = width;
    float b = thickness;
    float c = length;
    float final_surface_area;
    
    final_surface_area = 2*a*b+2*a*c+2*b*c;
    
    return final_surface_area/10000;
}

//profil kwadratowy
float Surface_Area::CalculateSquareProfile(float height,float width,float wall_thickness,float length)
{
    float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float a_in = a-c*2;
    float b_in = b-c*2;
    float final_surface_area_out,final_surface_area_in,final_surface_area;
    
    final_surface_area_out = 2*a*b+2*a*l+2*b*l;
    
    final_surface_area_in = 2*a_in*b_in+2*a_in*l+2*b_in*l;
    
    final_surface_area = final_surface_area_out- final_surface_area_in;
    
    return final_surface_area/10000;
}

//k¹townik
float Surface_Area::CalculateAngleProfile(float height,float width,float wall_thickness,float length)
{
	float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float final_surface_area_1,final_surface_area_2,final_surface_area;
    
    final_surface_area_1 = 2*a*c+2*a*l+2*c*l;
    
    final_surface_area_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    final_surface_area = final_surface_area_1 + final_surface_area_2;
    
    return final_surface_area/10000;

}

//ceownik
float Surface_Area::CalculateCProfile(float height,float width,float wall_thickness,float length)
{
    float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float final_surface_area_1,final_surface_area_2,final_surface_area,c_profile_surface_area;
    
    final_surface_area_1 = 2*a*c+2*a*l+2*c*l;
    
    final_surface_area_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    final_surface_area = final_surface_area_1 + 2*final_surface_area_2;
    
    return final_surface_area/10000;
}

//teownik
float Surface_Area::CalculateTProfile(float height,float width,float wall_thickness,float length)
{
	float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float final_surface_area_1,final_surface_area_2,final_surface_area;
    
    final_surface_area_1 = 2*a*c+2*a*l+2*c*l;
    
    final_surface_area_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    final_surface_area = final_surface_area_1 + final_surface_area_2;
    
    return final_surface_area/10000;
}

//dwuteownik
float Surface_Area::Calculate2TProfile(float height,float width,float wall_thickness,float length)
{
    float a = height;
    float b = width;
    float c = wall_thickness;
    float l = length;
    float final_surface_area_1,final_surface_area_2,final_surface_area,c_profile_surface_area;
    
    final_surface_area_1 = 2*a*c+2*a*l+2*c*l;
    
    final_surface_area_2 = 2*(b-c)*c+2*(b-c)*l+2*c*l;
    
    final_surface_area = final_surface_area_1 + 2*final_surface_area_2;
    
    return final_surface_area/10000;
}


