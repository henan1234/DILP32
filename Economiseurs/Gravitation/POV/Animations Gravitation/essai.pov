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
  location  <0.0, 0.5, -3.0>
  direction z
  right     x
  look_at   <0.0, 0.0,  0.0>
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
    ramp_wave
    color_map {
      [0.0 color rgb <0.0, 0.0, 0.0>]
      [0.2 color rgb <1.0, 0.3, 0.1>]
      [1.0 color rgb <1.0, 1.0, 0.1>]
    } 
  }

#declare Density2=
  density {
    boxed
    ramp_wave
    color_map {
      [0.0 color rgb <0.0, 0.0, 0.0>]
      [0.2 color rgb <0.1, 1.0, 0.3>]
      [1.0 color rgb <0.1, 1.0, 1.0>]
    } 
  }
sphere { 0, 1
  pigment { bozo    
            turbulence 0.3
                        color_map
                        {
                                [ 0 color rgbf<1, 1, 1, 1> ]
                                [ 1 color Red filter 0.9 ]
                        }  
           scale 0.1                        
          }
  finish { ambient 0 diffuse 0 }
  interior { 
    media {
      
      emission 5
      intervals 5
      samples 1, 10
      confidence 0.9999
      variance 1/1
      density {  Density1
      }
    } 
  }
  hollow 
}

sphere
        {
        0, 1.2
        pigment { granite    
            turbulence 0.3
                        color_map
                        {
                                [ 0 color Yellow*2 ]
                                 
                                [ 0.2 color rgbf<1, 1, 1, 1> ]
                                
                        }  
           scale 5                       
          }
          
          hollow
        }