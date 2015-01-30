
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
  location  <0.0, 0, -4.2>
  direction 1.5*z
  right    x
  look_at   <0.0, 0.0,  0.0>
}


light_source{  <-30, -10, -10> color White*2}

#declare	Cyan=rgb<0,0.2,1>
#declare	Blue=rgb<0,0,1>


#declare        Texture1=
        texture
                {       
                pigment { White }         
                finish { ambient 0.1 }                        
                
                }
                
                
#declare        Texture2=
        texture
                {
                  pigment{       
                        agate
                        turbulence 0.5
                        color_map
                        {
                                [ 0 Cyan]
                                [ 0.5 Cyan+Blue]
                                [ 1 Blue ]
                        } 
                        }
                  finish { ambient 0.1 }                        
                      
                }
                
                
                
#declare	Surface=
        texture {
                wood
                turbulence 0.05
                texture_map
                        {
                                [0 Texture2]
                                [0.4 Texture1]
                                [0.4 Texture1]
                                [1 Texture2]
                        }
                rotate x*90                        
                scale 0.5                                
                }

#declare	TextureAnneau=
        texture{
                pigment
                        {
        		wood       
        		turbulence 0.01
			colour_map 
			        {
				[0 0.2 colour rgbt<1.4,1,0,1> colour rgbt<1.4,1,0,0.6> ]
				[0.25 0.9 colour rgb <0.4,1,1,0.6> colour rgbt <1.4,0.5,0,0.5> ]
				[0.9 1 colour rgbt<1,1,1,0.1> transmit 0.4 colour rgbt<1,1,1,1>]
				}
										
                        }
        }
        
#declare	Anneau=disc{  0  z, 3, 1.6
						  texture { TextureAnneau }
						  rotate x*90
						}

union
{
sphere { 0, 0.7 texture { Surface }}

object	{ Anneau scale 0.55 }
rotate y*clock*360

rotate x*350 rotate z*45 

}

