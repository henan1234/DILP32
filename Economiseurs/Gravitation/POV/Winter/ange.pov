// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.1
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?[esp]
//

#version 3.1

#include "colors.inc"
#include "metals.inc"

global_settings
{
  assumed_gamma 1.0
}

// ----------------------------------------
camera
{
  location  <0.0, 0, -3.3>
  direction 1.5*z
  right     4/3*x
  look_at   <0.0, 0,  0.0>
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
  <-10, 10, -10>
  color White
}

union
{
// Le corps
cone
    {
    <0,0,0>, 0.2
    <0, -1, 0>, 0.6
    pigment
        {
        radial
        frequency 20
        colour_map
                {
                [0.5 White]
                [1 SteelBlue]
                }        
        }
    }
    
// La tete
sphere
        {
        <0, 0.2, 0>, 0.3
        pigment { Flesh }
        }

// Les yeux
sphere
        {
        <0.12, 0.3, -0.3>, 0.025 pigment { Black }
        } 
sphere
        {
        <-0.12, 0.3, -0.3>, 0.025 pigment { Black }
        }
        
cylinder
        {
        <0, 0.15, -0.27>, <0, 0.15, 0.1> 0.1 pigment { Black }
        }                
        
// L'aureole
/*cylinder
        {
        <0, 0.5, 0.2>, <0, 0.55, 0.25>, 0.4
        texture { T_Gold_2A }
        }
*/

torus { 0.3, 0.05 
        rotate x*70
        translate <0, 0.5, 0.2>
        texture { T_Gold_2A }
        }
                
light_source
        {
        <0, 0.5, -0.1>
        color White
        fade_power 1
        fade_distance 2
        looks_like
                {
                sphere {0 0.4 pigment { Yellow transmit 0.9 }}
                }
        }        
                
        
// Les ailes        
difference
        {
        cylinder    { <0, 0, 0.2>, <0, 0, 0.3>, 1 }
        
        union
                {
                box { <-1, -1, 0.19>, <1,1,0.33> rotate z*45 translate y}
                cylinder { <0, -0.1, 0.19>, <0, -0.1, 2.1>, 0.5 scale <1.1, 0.8, 1> }
                }
                                         
        texture {
                radial
                frequency 40
                texture_map
                        {
                        [0 T_Gold_1A]
                        [0.9 pigment { Black }]
                        }
                        
                rotate x*90         
                }

        rotate x*-10        
        translate y*0.2
        }

        translate y*0.1        
        
        rotate y*360*clock
}        