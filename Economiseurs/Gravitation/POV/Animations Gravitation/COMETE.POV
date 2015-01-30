
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
  location  <0.0, 0, -2.5>
  direction 1.5*z
  right    x
  look_at   <0.0, 0.0,  0.0>
}


light_source{  <-30, 30, -30> color White*10}

#declare	Object=blob
					{
					  threshold 0.1
					  sphere { x*(-0.5), 1, 1 }
					  sphere { x*0.3, 0.7, 0.9 }
					  sphere { <0.3, 0.2, 0.1>, 0.6, 0.9 }
					  scale 2
					}

object{ Object scale 1.5
		pigment { White transmit 1 }
		halo
			{	emitting spherical_mapping cubic turbulence 0.5
				  colour_map{
				  			[0 colour rgbt <1,1,1,1> ]
							[0.1 colour rgbt <0, 1, 1, 0.8>]
							[0.2 colour rgbt <0,1,1, 0.5>]
							[0.3 colour rgbt <1, 1, 1, 0.5>]
							[0.6 colour rgbt <1,1,1,0> ]

				  			}
			}
			hollow

			rotate z*clock*360
			rotate x*45
	   }

