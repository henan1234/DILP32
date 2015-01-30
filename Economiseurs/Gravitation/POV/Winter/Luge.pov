// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.1
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?[esp]
//

#version 3.1

#include "colors.inc"
#include "WOODS.INC"    // Great wooden textures created by Dan Farmer and Paul Novak



global_settings
{
  assumed_gamma 1.0
}

// ----------------------------------------
camera
{
  location  <0.0, 0, -10.0>
  direction 1.5*z
  right     4/3*x
  look_at   <0.0, 0.0,  0.0>
}

light_source                                           
{
  <-10,10,-10>
  color White
}

sky_sphere
{
  pigment { Gray50 }
}

#declare Largeur=1 ;

#declare Patin=
union
        {
        intersection
                {
                torus{  0.8,  0.2 rotate x*90}
                box { <0, -1, -1>, <-1, 0.5, 1> }
                }
                
        cylinder { <0, -0.8, 0>, <6, -0.8, 0>, 0.2 }
        }
        
union
        {
        object { Patin translate z*-Largeur}
        object { Patin translate z*Largeur}
        cylinder { <0.5, -0.8, -Largeur>, <0.5, 0.4, -Largeur>, 0.2 }
        cylinder { <0.5, -0.8, Largeur>, <0.5, 0.4, Largeur>, 0.2 }
        
        cylinder { <0.5, -0.8, -Largeur>, <1.3, 0.4, -Largeur>, 0.1 }
        cylinder { <0.5, -0.8, Largeur>, <1.3, 0.4, Largeur>, 0.1 }
        
        cylinder { <4, -0.8, -Largeur>, <4, 0.4, -Largeur>, 0.2 }
        cylinder { <4, -0.8, Largeur>, <4, 0.4, Largeur>, 0.2 }
        
        cylinder { <4, -0.8, -Largeur>, <3.2, 0.4, -Largeur>, 0.1 }
        cylinder { <4, -0.8, Largeur>, <3.2, 0.4, Largeur>, 0.1 }
        
        box { <0.2, 0.4, -Largeur*1.1>, <4.5, 0.6, Largeur*1.1> }
        
        translate x*-2.5
        
        texture { T_Wood1 }

        rotate clock*360       
        }        