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
  assumed_gamma 0.5
}

// ----------------------------------------
camera
{
  location  <0.0, 0, -4.6>
  direction z
  look_at   <0.0, 0.0,  0.0>
}

light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-30, 30, -30>
}

#declare Panneau=
box
        {
        <-0.5, 1, 0>, <0.5, -1, 0.1>
        
        pigment
                {
                hexagon Blue, Blue*2, Blue
                scale 0.1      
                rotate z*90
                rotate y*90
                }

        normal
                {
                bozo
                scale 0.2
                }                
        finish
                {
                phong 1
                phong_size 5
                }                
        translate -z*1.2
        }

union
        {        
        object { Panneau }
        object { Panneau rotate y*45}
        object { Panneau rotate y*90}
        object { Panneau rotate y*135}
        object { Panneau rotate y*180}
        object { Panneau rotate y*225}
        object { Panneau rotate y*270}
        object { Panneau rotate y*315}
        cylinder { 0, y*3, 0.05 texture { T_Chrome_4C }}        
        cone    {  -1*y,  0.5,
                   -2*y, 1.0
                   pigment {    
                                radial
                                colour_map
                                        {
                                        [0 Black]
                                        [1 White]
                                        }
                                frequency 8    
                           }                                        
                }

        rotate y*clock*360/8
        rotate z*45
        }