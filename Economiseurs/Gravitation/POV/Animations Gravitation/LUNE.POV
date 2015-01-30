
// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3

#include "colors.inc"
#include "stones.inc"


// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3

#include "colors.inc"

// ----------------------------------------
camera
{
  location  <0.0, 0, -3.2>
  direction 1.5*z
  right     x
  look_at   <0.0, 0.0,  0.0>
}

light_source
{
  0*x // light's position (translated below)
  color White*3
  translate <-30, 30,-30>
}

#declare	Cratere=torus{ 0.7 0.999 scale y*0.6}
#declare	R1=seed(0)

difference{
			sphere { 0, 1 }
			union
				{
#declare		Nb=0
#while			( Nb < 200 )
				object { Cratere scale	rand(R1)*0.1+0.01
						 translate y
						 rotate x*rand(R1)*360
						 rotate y*rand(R1)*360
						 rotate z*rand(R1)*360
					   }
				#declare	Nb=Nb+1
#end
				}

/*			pigment { bozo turbulence 2
					  colour_map { 	[0 color <0.45, 0.4, 0.1>]
					  				[0.1 0.1 color <0.45, 0.4, 0.1> color <0.55, 0.5, 0.2>]
					  				[0.1 color <0.55, 0.5, 0.2>]
									[0.5 color <0.65, 0.55, 0.3>]
					  			   [0.5  1 color <0.65, 0.55, 0.3> color <0.95, 0.85, 0.6>]
					  			}
					}
			finish { ambient 0.1 diffuse 0.6 crand 0.1 }*/
			texture { T_Grnt11a scale 2}

			rotate y*clock*360
			rotate x*-30
			}

