// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.1
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?[esp]
//

#version 3.1

#include "colors.inc"
#include "stones.inc"
#include "stars.inc"

global_settings
{
  assumed_gamma 1
}
  // set the maximum ray tracing bounce depth (1...20) [5]
#declare NBMAX=6 ;

#max_trace_level 10


sphere
        {
        0, 100 hollow
        texture { Starfield4 }
        }
       
        
// ----------------------------------------

camera
{
        angle 80
  location  <0.0, 1, -2.0>
  direction 1.5*z
  right     500/120*x
  look_at   <-2, 1,  10.0>
}


light_source
{
  0*x // light's position (translated below)
  color White * 2
  translate <-90, 20, 5>
}

// uses image color index as height, extends along X-Z axes
// from <0 0 0> to <1 1 1>

height_field
{
  gif       "sol.gif"
  smooth
  translate <-0.5, 0, -0.5>
  scale <5, 1, 3>
  
  texture
        {
        pigment
                {
                granite
                turbulence 0.5 
                colour_map
                        {
                        [0 rgb<0.6, 0.5, 0.5>]
                        [1 Black]
                        }
                scale 0.1                        
                }
               
              finish
                {  
                roughness 1
                ambient 0.01 
                }                
        }
}

#declare BleuOcean1=    rgb <105/256, 111/256, 188/256>
#declare BleuOcean2=    rgb <97/256,98/256,165/256>
#declare VertTerre1=    rgb<108, 112, 53>/256
#declare VertTerre2=    rgb<87,110,52>/256 
#declare MarronTerre=   rgb<120,110,80>/256
#declare JauneDesert=   rgb<176,147,100>/256

#declare	Banquise=texture { pigment { White } finish { ambient 0.7 crand 0.1 }}
#declare	TextureTerre=
	texture
		{
		pigment
			{          
			crackle 
			turbulence 1
			colour_map
				{
				[0 colour VertTerre1 ]
				[0.1 colour VertTerre2 ]
				[0.55 color JauneDesert]
				[0.6 color MarronTerre]
				}
			}
		normal { bumps  1 turbulence 1 }
		finish { ambient 0.2 }
		}

// Couleur des oceans
#declare Ocean=
	texture
		{
		pigment
			{
			ripples turbulence 0.5
			colour_map
				{
				[0 1 color BleuOcean1 color BleuOcean2]
				}
			}
		finish { /*ambient 0.2 reflection 0.5 */ phong 1 phong_size 20}
		normal { waves 0.1 frequency 10000 }
		scale 10
		}


               
#declare TextureNuages=
        texture
                {
                pigment
                        {
                        wrinkles
                        turbulence 1.5
                        colour_map
                                {
                                //[0.3 White transmit 1 ]
                                [0.1 White transmit 0.1]
                                [0.6 White transmit 1 ]
                                } 
                        frequency 5
                        }
                }                

   union
        {
        sphere
                {
                0, 10
                texture
                        {
                        bozo
                        turbulence 2.5
                        texture_map                
                                {  
                                [0 Ocean]
                                [0.5 Ocean]
                                [0.55 TextureTerre]
                                }
                        scale 5
                        }
                }
        sphere  {
                0, 10.1
                pigment { Cyan transmit 0.99 }
                }
       

                        
#declare Rayon=10.01 ;
#declare Nb=0
#declare R1=seed(0) ;
#while ( Nb < NBMAX )
                                    
#declare Nuages=
        texture
                {
                spiral1 2
                sine_wave
                turbulence 0.2
                texture_map
                        {
                        [0.2 + Nb / 20 pigment { White transmit 1 }]
                        [0.7 + Nb / 20 TextureNuages ]
                        }
                scale 0.5
                }     
                

        sphere
                {
                0, 1
                texture { Nuages }
                
                hollow
                rotate y*220 
                rotate x*-20
                
                scale Rayon
                rotate y*200
                rotate x*-20
                }
 #declare Nb=Nb+1 ;
 #declare Rayon=Rayon+0.03   ;
#end

        
        translate <12, 2, 20>
        }
                        

