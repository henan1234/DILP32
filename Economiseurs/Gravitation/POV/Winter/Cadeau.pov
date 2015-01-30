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
  location  <0.0, 0, -5.2>
  direction 1.5*z
  right     4/3*x
  look_at   <0.0, 0.0,  0.0>
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
  <-10, 10, -20>
  color White
}

#declare
        TextureRuban=
        texture
        {
        pigment { Yellow }
        finish { phong 1 phong_size 10 }
        }
                
#declare TexturePapier=
        texture
        {
        pigment { 
                leopard
                color_map
                  { 
                  [0.5 rgb<0.9, 0, 0> ]
                  [0.5 rgb<0, 0, 0.9> ]
                  }
                scale 0.1
                  
                }
                  
        normal { bumps 0.1 }
        normal { dents 1 scale 0.1 } 
        finish { phong 1 phong_size 10 }
        }                


union
{                 
difference
        {
        cylinder { <0.4, 1.2, -0.2>, <0.4, 1.2, 0.2>, 0.4 }
        cylinder { <0.4, 1.2, -0.3>, <0.4, 1.2, 0.3>, 0.37 }
        texture { TextureRuban }
        }
difference
        {
        cylinder { <-0.4, 1.2, -0.2>, <-0.4, 1.2, 0.2>, 0.4 }
        cylinder { <-0.4, 1.2, -0.3>, <-0.4, 1.2, 0.3>, 0.37 }
        texture { TextureRuban }
        }

box
        {
        <-0.2, -1.01, -1.01>, <0.2, 1.01, 1.01>
        texture { TextureRuban }
        }
        
box
        {
        < -1.01, -0.2,-1.011>, <1.01, 0.2, 1.011>
        texture { TextureRuban }
        }
        

box
        {
        <-1, -1, -1>, <1, 1, 1>
        texture { TexturePapier }
        }
        
        rotate clock*360        
}