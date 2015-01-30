
// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3

#include "colors.inc"
#include "metals.inc"
#include "skies.inc"

global_settings { max_trace_level 5 }

// ----------------------------------------
camera
{
  location  <0, 0, -20>
  direction 1.5*z
  right     160/300*x
  look_at   <0.0, 0.0,  0.0>
  angle 90
}

sky_sphere { S_Cloud1 }
light_source
	{
	<-9, 9, -9>,  color White*5
	fade_power 2 fade_distance 8
	}
light_source
	{
	<9, 9, -9>,  color White*5
	fade_power 2 fade_distance 8
	}


#declare TextureBoite=
	texture
		{
		pigment {
				bozo
				turbulence 0.1
				color_map
					{
					[0 0.8 color SteelBlue*0.8 color SteelBlue]
					[0.8 color SteelBlue]
					}
				}
		finish { ambient 0.8 diffuse 0.7 }
		}

#declare	TextureCadre=
	texture
		{
		T_Silver_3B
		}

#declare TextureLien=
	texture
		{
		T_Gold_3D
		}
/*
difference
	{
	box {<-11, -11, -11>, <11, 11, 11> }
	box {<-10, -10, -10>, <10, 10, 10> }
	hollow
	texture { TextureBoite }
	}
*/
#declare Diametre=0.5
cylinder { < 10,  10,  10>, < 10, 10, -10>, Diametre texture { TextureCadre } }
cylinder { < 10,  10,  -10>, < 10, -10, -10>, Diametre texture { TextureCadre } }
cylinder { < 10,  -10,  -10>, < 10, -10, 10>, Diametre texture { TextureCadre } }
cylinder { < 10,  -10,  10>, < 10, 10, 10>, Diametre texture { TextureCadre } }

cylinder { <-10,  10,  10>, < -10, 10, -10>, Diametre texture { TextureCadre } }
cylinder { <-10,  10,  -10>, < -10, -10, -10>, Diametre texture { TextureCadre } }
cylinder { <-10,  -10,  -10>, < -10, -10, 10>, Diametre texture { TextureCadre } }
cylinder { <-10,  -10,  10>, < -10, 10, 10>, Diametre texture { TextureCadre } }

cylinder { <-10,  10,  10>, < 10, 10, 10>, Diametre texture { TextureCadre } }
cylinder { <-10,  10,  -10>, < 10, 10, -10>, Diametre texture { TextureCadre } }
cylinder { <-10,  -10,  -10>, < 10, -10, -10>, Diametre texture { TextureCadre } }
cylinder { <-10,  -10,  10>, < 10, -10, 10>, Diametre texture { TextureCadre } }

#declare DiametreAtome=1.5

#declare AtomeRouge=
	sphere
		{
		0, DiametreAtome
		texture {
				pigment { Red }
				finish { F_MetalC }
				}
		}
#declare AtomeBleu=
	sphere
		{
		0, DiametreAtome
		texture {
				pigment { Blue }
				finish { F_MetalC}
				}
		}

#declare PosAtome1=<5, 6, 2>
#declare PosAtome2=<-6, -3, -9>
#declare PosAtome3=<2, 0, 5>
#declare PosAtome4=<9, 3, -6>
#declare PosAtome5=<5, -4, -7>
#declare PosAtome6=<-4, -1, -1>
#declare PosAtome7=<-3, 7, -9>


object { AtomeRouge translate PosAtome1 }
object { AtomeRouge translate  PosAtome2 }
object { AtomeRouge translate PosAtome3 }
object { AtomeBleu translate  PosAtome4 }
object { AtomeBleu translate  PosAtome5 }
object { AtomeBleu translate  PosAtome6 }
object { AtomeRouge translate PosAtome7 }

#declare Diametre=0.3
cylinder{ PosAtome1, PosAtome3, Diametre texture { TextureLien }}
cylinder{ PosAtome3, PosAtome5, Diametre texture { TextureLien }}
cylinder{ PosAtome4, PosAtome7, Diametre texture { TextureLien }}
cylinder{ PosAtome5, PosAtome6, Diametre texture { TextureLien }}


