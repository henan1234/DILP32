
// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3

#include "colors.inc"      

global_settings
{
  assumed_gamma 1.5
}


// ----------------------------------------
camera
{
  location  <2, 0, -10>
  direction z
  right     290/91*x
  look_at   <0.6, -0.78,  0.0>
  angle 10
}


light_source{ <0, 0, 0>  color White*5 }

        
#declare DensJaune=
  density {
    spherical
    ramp_wave
    turbulence 5 
    frequency 10
    color_map {
      [0.0 color rgbt <0.0, 0.0, 0.0, 1>]
      [0.2 color Yellow transmit 0.8]
      [0.4 color Yellow*5 transmit 0.5]
    }
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

  
union
        {
        // Interieur
        sphere 
                { 0, 1.01
                pigment 
                        { 
                        crackle    
                        turbulence 0.8
                        color_map
                                {
                                [ 0 color rgbf<1, 1, 1, 0.9> ]
                                [ 0.9 color Red filter 0.5 ]
                                [ 0.95 color Black]
                                }  
                scale 0.2                        
                }
        finish { ambient 0 diffuse 0 }
        interior
                { 
                media 
                        {
                        emission 5
                        intervals 5
                        samples 1, 4
                        confidence 0.9999
                        variance 1/100
                        density {  Density1 }
                        } 
                }
        hollow   
        rotate y*clock*360
        }

        // Surface
        sphere
                {
                0, 1.04
                pigment { granite   turbulence 0.5
                          color_map
                                {
                                [ 0 color Yellow*2 ]
                                [ 0.25 color rgbf<1, 1, 1, 1> ]
                                
                                }  
                scale 5                       
                }
                hollow    
                rotate -y*clock*360
                }

        
        }                          




// Protuberances
sphere
    {
        0, 1.08
        pigment { White transmit 1 }
        
        interior
                { 
                media 
                        {
                        emission 1
                        intervals 5
                        samples 1, 8
                        confidence 0.9999
                        variance 1/2
                        density {  DensJaune }
                        } 
                }
        hollow   

        rotate x*360*clock
        rotate y*45        
    }                         
          
// create a TrueType text shape
text
{
  ttf             // font type (only TrueType format for now)
  "C:\WINNT\Fonts\arialbd.ttf",  // Microsoft Windows-format TrueType font file name
  "GRAVITATION",      // the string to create
  1,              // the extrusion depth
  0               // inter-character spacing
  
  pigment { Cyan }
  scale 0.21
  rotate y*-10
  
  translate <0.1, -0.7, -1>
  
  
  finish { phong 1 phong_size 10 ambient 0.3 }
}
 
 
text
{
  ttf             // font type (only TrueType format for now)
  "C:\WINNT\Fonts\arial.ttf",  // Microsoft Windows-format TrueType font file name
  "Screen saver",      // the string to create
  0.5,              // the extrusion depth
  0               // inter-character spacing
  
  pigment { Cyan }
  scale 0.17
  rotate y*-10
  
  translate <0.5, -0.9, -1>
  
  finish { phong 1 phong_size 10 ambient 0.3 }
}
