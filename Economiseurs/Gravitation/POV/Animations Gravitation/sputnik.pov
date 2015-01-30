// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.1
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?[esp]
//

#version 3.1

#include "colors.inc"
#include "stars.inc"
#include "metals.inc"

global_settings
{
  assumed_gamma 1
}

// ----------------------------------------
camera
{
  location  <0.0, 0, -6>
  direction 1.5*z
 // right     4/3*x
  look_at   <1.5, 0.0,  0.0>
}
/*
sphere
{
        0, 1000
        texture { Starfield1 }
        hollow
}
*/
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  looks_like
        {
        sphere
                {
                0, 10
                pigment { Yellow filter 0.9 }
                }        
        }
  translate <-30, 30, -30>
}

#declare        Lumiere=
        light_source
                {
                0
                Red*20
                looks_like
                        {
                        sphere {0, 0.1
                        pigment { Red transmit 0.7 }}
                        }
                fade_distance 1
                fade_power 2
                translate -z*1.01
                rotate y*30       
                }
                
#declare Antenne=   
        union
                {
                sphere
                        {
                        <0, 0, -1>, 0.08
                        }
                cylinder
                        {
                        <0, 0, -1>,  <3.6, 0, -1.5>,  0.05
                        texture { T_Chrome_4A }
                        }
                }        
union
        {
        sphere
                {
                0, 1
                texture
                        {
                        checker texture{T_Chrome_4B}, texture { T_Chrome_3A }
                        turbulence 0.1
                        scale 0.3
                        }
                }
                union
                        {
                        torus   {
                                0.97,
                                0.05
                                }
                                
                        torus   {
                                0.97,
                                0.05
                                rotate x*90
                                }
                        }
                
                
        object  { Lumiere rotate x*45}                
        object  { Lumiere rotate x*135}                
        object  { Lumiere rotate x*225}                
        object  { Lumiere rotate x*315}                
        
        object  { Antenne rotate x*45}                
        object  { Antenne rotate x*135}                
        object  { Antenne rotate x*225}                
        object  { Antenne rotate x*315}
        
        rotate x*clock*360/4                
        }