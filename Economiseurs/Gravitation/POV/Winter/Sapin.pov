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
  location  <0.0, 0, -6.2>
  direction 2.8*z
  //right     4/3*x
  look_at   <-0.1, 0.2,  0.0>
}


background { Gray50 }

light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-30, 30, -30>
}

#declare TextureBoule =
      texture
      {      
         pigment
         {
            Red
         }      
         finish
         {
            ambient 0.6
            diffuse 0.8
            brilliance 0.1
            phong 2
            phong_size 10
            reflection rgb 0.2
         }
      }

#declare VertSapin=
        texture
                {
                pigment { 
                        bozo
                        color_map
                                {
                                [0 color White*2]
                                [0.4 color White*2]
                                [0.40001 color ForestGreen]
                                [0.70001 color ForestGreen*0.8]
                                }
                                
                        scale 0.1       
                        }
                }

#declare MorceauDeSapin=
        union
                {
                intersection
                        {
                        cone { 0, 1, <0, 1.2, 0>, 0 }
                        box { <-1.1, 0, -0.1>, <1.1, 1.3, 0.1> } 
                        texture { VertSapin }
                        }
                sphere { <1, -0.1, 0> 0.1 texture { TextureBoule }}
                light_source { <1.1, 0.1, 0> color Yellow*2 fade_power 3 fade_distance 0.2  }
                }

#declare NbTotal        =       10 ;
#declare EtageSapin=
        union
                {
                #declare Nb=0 ;
                #while ( Nb < NbTotal )         
                        object { MorceauDeSapin rotate y*(360/8*Nb)}
                        #declare Nb=Nb+1 ;
                #end
                }

#declare Sapin=
        union
                {
                object { EtageSapin }
                object { EtageSapin scale 0.7 translate y*0.7}
                object { EtageSapin scale 0.5 translate y*1.2}
                }
                
                
#declare Tronc=
        cylinder
                { 0, <0, -0.5, 0>, 0.2 pigment { Sienna }}
                
                                                                                
union
        {
        object { Sapin }
        object { Tronc }
        rotate y*clock*360/2
        rotate z*45
        rotate y*10
        }                
