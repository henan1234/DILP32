
// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3

#include "colors.inc"
#include "skies.inc"

// ----------------------------------------
camera
{
  location  <0.0, 1, -3.2>
  direction 1.5*z
  right    x
  look_at   <0.0, 0.0,  0.0>
}


//light_source{  <-30, 30, -30> color White*3}
light_source{  <-30, 0, -10> color White*3}

#declare BleuOcean1=    rgb <105/256, 121/256, 198/256>
#declare BleuOcean2=    rgb <97/256,98/256,155/256>
#declare VertTerre1=    rgb<108, 112, 53>/256
#declare VertTerre2=    rgb<97,120,62>/256 
#declare MarronTerre=   rgb<120,110,80>/256
#declare JauneDesert=   rgb<176,147,100>/256

#declare	Banquise=texture { pigment { White } finish { ambient 0.7 crand 0.1 }}
#declare	Terre=
	texture
		{
		pigment
			{          
			crackle 
			turbulence 2
			colour_map
				{
				[0 colour VertTerre1 ]
				[0.1 colour VertTerre2 ]
				[0.55 color JauneDesert]
				[0.6 color MarronTerre]
				}
			}
		finish { ambient 0.4 }
		}

// Couleur des oceans
#declare Ocean=
	texture
		{
		pigment
			{
			bozo turbulence 1
			colour_map
				{
				[0 1 color BleuOcean1 color BleuOcean2]
				}
			}
		finish { ambient 0.4 reflection 0.5 phong 1 }
		normal { waves 0.1 frequency 10000 }
		}

// Melange des deux textures pour faire une alternance terre/ocean
#declare	TerreOcean=
            
	texture
		{
		material_map
			{
			gif "carte.gif"
			once map_type 1
			interpolate 2
			texture { Terre}
			texture { Ocean}
			}
		}

union
{
sphere { 0, 1

		 texture {
    			    gradient y 
    			    turbulence 0.1
			    texture_map {
			  	        [0.9 TerreOcean  ]
					[0.97 Banquise  ]
					}
				frequency 1
				}
		}

// Atmhosphere avec des nuages
sphere {
		0, 1.03
		pigment 
		        { 
		        ripples 
		        turbulence 0.95
		        scale 0.2
			colour_map
			        {
	  			[0 colour rgbt < 1,1,1,1> ]
				[0.2 colour Blue transmit 1 ]
				[0.6 colour Gray90 transmit 0.6]
				[0.7 colour Gray70 ]
				[0.8 colour Gray80]
	  			}
        		}
		
		hollow
	   }
rotate y*280
rotate y*clock*360
rotate x*-10
rotate z*23
}
