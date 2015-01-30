// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.1
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?[esp]
//

#version 3.1

#include "colors.inc"

global_settings
{
  assumed_gamma 1.0
}

// ----------------------------------------
camera
{
  location  <-1.0, 0.5, -7.2>
  direction 1.5*z
  right     4/4*x
  look_at   <0.0, -0.5,  0.0>
}

sky_sphere
{
  pigment
  {
    Gray50
  }
}

light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-10, 10, -10>
}

#declare Neige=
        texture
                {
                pigment { rgb<0.95, 0.99, 1> }
                normal  { bumps 0.4 scale 0.1 }
                finish  { ambient 0.2 }
                }

union
        {                
        
        // tete
        sphere { <0, 0.1, 0>, 1 texture {Neige} }
        cone   { <0, 0, -1>, 0.2, <0, 0, -2>, 0 pigment { Red }}           
        
        // Corps
        sphere { <0, -1.5, 0>, 1.5 texture { Neige }}
        
        // yeux
        sphere { <0.4, 0.4, -0.8> 0.2 pigment { Black }}
        sphere { <-0.4, 0.4, -0.8> 0.2 pigment { Black }}
        
        // echarpe
        cylinder { <0, -0.3, 0>, <0, -0.5, 0>, 1.1 pigment  { Red }} 
        
        // Balai
        cylinder { <1.4, -1.5, -0.2>, <1.6, 0.6, -0.52>, 0.1 pigment { Sienna }}
        cylinder { <1.55, 0.6, -0.52>, <1.65, 0.6, -0.52>, 0.5 pigment { gradient z frequency 4 colour_map { [0 Yellow] [1 Black] }}}
        
        
        union
               {                                          
                cylinder { <0, 0.7, 0>, <0, 1.5, 0>, 0.7 }
                cylinder { <0, 0.7, 0>, <0, 0.8, 0>, 1.1 }
                pigment { Black }
                finish { phong 1 phong_size 10 }
                rotate x*15                
                rotate y*clock*360
                }
        
        rotate z*sin(clock*pi*4)*10
        rotate y*-15
        }        