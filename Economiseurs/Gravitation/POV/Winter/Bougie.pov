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
  location  <0.0, 0.5, -4.0>
  direction 1.5*z
  right     4/3*x
  look_at   <0.0, 0.0,  0.0>
}

sky_sphere
{
  pigment
  {
    gradient y
    color_map { [0.0 color blue 0.6] [1.0 color rgb 1] }
  }
}

light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-30, 30, -30>
}

#declare Density1=
  density {
    spherical
    //scallop_wave
    turbulence 1
    color_map 
        {
        [0.0 color Yellow]
        [0.2 color Red transmit 0.8]
        [0.7 color Red transmit 1]
        }
  }






sphere
    {
        0, 1
        pigment { White transmit 1 }
        
        interior
                { 
                media 
                        {
                        emission Yellow
                        intervals 2
                        samples 1, 10
                        density {  Density1 }
                        } 
                }
        hollow   

        rotate x*360*clock
        rotate y*45        
    }    