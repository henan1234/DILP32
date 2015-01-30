
// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3

#include "colors.inc"
#include "stones.inc"

global_settings
{
  assumed_gamma 1.0
}

// ----------------------------------------
camera
{
  location  <0.0,0, -4.7>
  direction 1.5*z
  right     x
  look_at   <0.0, 0.0,  0.0>
}

light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-30, 30,-30>
}

 
blob
{
  threshold 0.1
  sphere { <0,   0.2,    0>, 1.2, 2 }
  sphere { <0.2,   0.2,    0>, 1.2, 2 }
  sphere { <0, -0.6, 0>, 1, 2 }
  
  sphere { <0, -0.5, -0.8>, 0.6, -0.5 }
  sphere { <0.4, -0.7, -0.7>, 0.4, -1 }
  
  sphere { <-0.8, 0.2, -0.5>, 0.4, -1 }
  sphere { <0.1 0.5, 0.8>, 0.4, -1 }
  
        pigment
                {                
	        wrinkles
	        colour_map
	                {
	                [0.7 rgb<0.2, 0.05, 0.05>]
	                [0.95 rgb<0.72, 0.7, 0.7>]
	                }
	        scale 0.5
	        }

        normal { dents 3 turbulence 0.4 }	          
  rotate x*360*clock
  
  rotate z*20        
}
