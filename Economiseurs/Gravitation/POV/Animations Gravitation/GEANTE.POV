
// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3

#include "colors.inc"

// ----------------------------------------
camera
{
  location  <0.0, 1, -3>
  direction 1.5*z
  right    x
  look_at   <0.0, 0.0,  0.0>
}


light_source{  <-30, 30, -20> color White*3 }

#declare	Cyan=rgb<0,0.2,1>
#declare	Blue=rgb<0,0,1>
#declare	Surface=
	texture
		{
		pigment
			{
			image_map
				{
				gif "jupiter.gif"
				map_type 1
				interpolate 2
				once
				}
			}
		finish { diffuse 0.5 }
		}
		
union
{        
sphere { 0, 1 texture { Surface }}

rotate z*5

rotate y*clock*360+10
rotate x*10
rotate z*10
}
