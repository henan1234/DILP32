#version 3

#include "colors.inc"

global_settings
{
  assumed_gamma 1.5
}

// ----------------------------------------
camera
{
  location  <0.0, 3, -1.5>
  direction 1.5*z
  right     x
  look_at   <0.0, 0.0,  0.0>
}

light_source
{
  0*x // light's position (translated below)
  color White
  translate <-30, 30,-10>
}


#declare Density1=
  density {
    spherical
    scallop_wave
    turbulence 1
    color_map 
        {
        [0.0 color rgb <0.0, 0.0, 0.0>]
        [0.5 color rgb <0.0, 0.1, 0.1>]
        [0.7 color rgb <0.5, 0.9, 1>]
        }
  }


#declare Density2=
  density {
    spherical
    turbulence 3
    color_map {
      [0.0 color rgb <0.0, 0.0, 0.0>]
      [0.01 color rgb <0.1, 0.1, 0.1>]
      [0.2 color rgb <0.9, 0.9, 0.9>]
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
                        emission 0.4
                        intervals 2
                        samples 1, 8
                        confidence 0.9999
                        variance 1/2
                        density {  Density1 }
                        } 
                }
        hollow   

        rotate x*360*clock
        rotate y*45        
    }    
    
sphere
    {
        0, 0.7
        pigment { White transmit 1 }
        
        interior
                { 
                media 
                        {
                        emission 0.4
                        intervals 5
                        samples 1, 8
                        confidence 0.9999
                        variance 1/2
                        density {  Density2 }
                        } 
                }
        hollow   

        rotate x*360*clock
        rotate y*45        
    }
    
blob
{
  threshold 0.3
  sphere { < 0.2,   0,    0>, 0.7, 1 }
  sphere { <-0.2,  0.2, 0>, 0.6, 1 }
  sphere { <0, -0.1, 0.2>, 0.5, 1}

                pigment { granite
                          turbulence 0.8
                          color_map
                                {
                                [0 Cyan]
                                [0.5 Gray20]
                                [0.9 Black]
                                }
                }
               normal { wrinkles 4 scale 0.5 }
               
        rotate x*360*clock
        rotate y*40               

        }


