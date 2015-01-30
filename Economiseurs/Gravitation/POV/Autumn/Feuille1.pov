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
  location  <0.0, 0, -5.0>
  direction 1.5*z
  right     4/3*x
  look_at   <0.0, 0.0,  0.0>
}

background
{
 Sienna
}

light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-30, 30, -30>
}

#declare        MoitiePartieFeuille=
        intersection
                {
                cylinder { <0, -0.01, 0>, <0, 0.01, 0>, 1 }
                box { <-1, -1, -1>, <0, 1, 1> }
                }

#declare PartieFeuille=
merge
        {
        object  {MoitiePartieFeuille rotate z*-5}
        object  {MoitiePartieFeuille rotate z*-5 rotate y*180}
        scale <0.5, 0.5, 1>
        translate z*0.8
        }
        

union
        {
        object  { PartieFeuille}
        object  { PartieFeuille rotate y*60 }
        object  { PartieFeuille rotate y*-60 }
        object  { PartieFeuille rotate y*120 }
        object  { PartieFeuille rotate y*-120 }
        cylinder { 0, <-0.05, 0, -1>, 0.05 }
        rotate x*-90
        translate y*-0.4
        pigment { ForestGreen }
        rotate clock*360
        }        