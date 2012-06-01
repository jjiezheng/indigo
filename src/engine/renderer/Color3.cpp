#include "Color3.h"

Color3 Color3::BLACK  =  Color3(0, 0, 0);
Color3 Color3::WHITE  =  Color3(1, 1, 1);
Color3 Color3::RED    =  Color3(1, 0, 0);
Color3 Color3::GREEN  =  Color3(0, 1, 0);
Color3 Color3::BLUE   =  Color3(0, 0, 1);

Color3::Color3(float r_, float g_, float b_) 
	: r(r_), g(g_), b(b_) {
  
}

Color3::Color3()
: r(0), g(0), b(0) { }
