// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.1
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?[esp]
//

#version 3.1

#include "colors.inc"
#include "metals.inc"

global_settings
{
  assumed_gamma 1.0
}

// ----------------------------------------
camera
{
  location  <0.0, 0, -3.5>
  direction 1.5*z
  right     4/3*x
  look_at   <0.0, 0,  0.0>
}

sky_sphere
{
  pigment
  {
    Gray50
  }
}

light_source
{
  <-10, 10, -10>
  color White
}



#declare Rouge =
      texture
      {      
        pigment{
         image_map
                {
                gif "boule1.gif" // the file to read (iff/gif/tga/png/sys)
                map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
                }
                
                frequency 8
              }
              
         finish
         {
            ambient 0.6
            diffuse 0.5
            brilliance 0.1
            phong 2
            phong_size 10
            reflection rgb 0.3
         }
      }


#declare Jaune =
      texture
      {      
         pigment
         {
            color rgb <1.0, 1.0, 0.0>
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

union
        {
        sphere { 0.0, 1 
                texture { Rouge }
               }

        union
                {
                sphere { <0, 0.8, 0>, 0.3 }        
                cylinder { <0, 0.9, 0>, <0, 1.2, 0>, 0.25 }
                         
                torus
                        {
                        0.3, 0.05
                        rotate x*80
                        translate y*1.3
                        }
                texture { T_Gold_1B }                                                                           
                }
        
        rotate y*clock*360
        rotate z*60
        rotate y*-20        
        }        

#declare VertSapin=
        texture
                {
                pigment { 
                        bozo
                        color_map
                                {
                                [0.3 color <0.1, 0.5, 0>]
                                [0.7 color <0.1, 0.1, 0>]
                                }
                                
                        scale 0.05       
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
                sphere { <1, -0.1, 0> 0.1 pigment { Red } finish { phong 1 }}
                }

#declare EtageSapin=
        union
                {
                #declare Nb=0 ;
                #while ( Nb < 8 )         
                        object { MorceauDeSapin rotate y*(360/8*Nb) }
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
        translate <2, 2, -5>
        }                


box
        {
        <-20000, 0, -10>, <20000, -10000, -16> pigment { Black }
        }