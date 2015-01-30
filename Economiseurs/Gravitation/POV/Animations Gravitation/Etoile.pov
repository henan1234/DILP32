
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
  assumed_gamma 1.0
}


// ----------------------------------------
camera
{
  location  <0.0, 0, -3.5>
  direction 1.5*z
  right     x
  look_at   <0.0, 0.0,  0.0>
}


//light_source{  0 color White*5 }

        
#declare DensBleu=
  density {
    spherical
    //ramp_wave
    turbulence 5 
    frequency 10
    color_map {
      [0.0 color rgb <0.0, 0.0, 0.0>]
      [0.3 color Cyan ]
      [0.5 color Cyan*10]
    }
  }

#declare Density1=
  density {
    spherical
    ramp_wave
    color_map {
      [0.0 color rgb <0.0, 0.0, 0.0>]
      [0.2 color rgb <0.0, 1, 1>]
      [1.0 color rgb <2.0, 2.0, 2.1>]
    } 
  }

  
union
        {  
        sphere 
                { 0, 0.9
                pigment 
                        { 
                        crackle    
                        turbulence 1.5
                        color_map
                                {
                                [ 0 color rgbf<1, 1, 1, 0.9> ]
                                [ 0.9 color Cyan filter 0.5 ]
                                [ 0.95 color Black]
                                }  
                scale 0.4                        
                }
        //finish { ambient 0 diffuse 0 }
        interior
                { 
                media 
                        {
                        emission 15
                        intervals 10
                        samples 1, 8
                        confidence 0.0009
                        variance 1/1000000
                        density {  Density1 }
                        } 
                }
        hollow   
        rotate y*clock*360
        }


        sphere
                {
                0, 1
                pigment { granite   
                          turbulence 0.5
                          color_map
                                {
                                [ 0 color Cyan*2 ]
                                [ 0.25 color rgbf<1, 1, 1, 1> ]
                                
                                }  
                scale 5                       
                }
                hollow    
                rotate -y*clock*360
                }

        
        }                          



/*

sphere
    {
        0, 1.1
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
                        density {  DensBleu }
                        } 
                }
        hollow   

        rotate x*360*clock
        rotate y*45        
    }    
  */      