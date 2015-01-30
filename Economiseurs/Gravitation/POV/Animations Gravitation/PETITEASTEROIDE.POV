
#version 3

#include "colors.inc"

 
// ----------------------------------------
camera
{
  location  <0.0, 1, -3	>
  direction 1.5*z
  right    x
  look_at   <0.0, 0.0,  0.0>
}


light_source{  <-30, 30, -30> color White*2}
light_source{  <0, 30, -60> color White}

// Couleurs brunes
#declare	Couleur1=rgb <0.4, 0.3, 0.2>
#declare	Couleur2=rgb <0.5, 0.4, 0.3>



// Couleurs grisatres
#declare	Gris1=rgb< 0.4, 0.45, 0.4>
#declare	Gris2=rgb< 0.31, 0.35, 0.31>

#declare Texture1=
        texture 
                { 
                pigment 
                        {
                        bozo turbulence 0.3
			colour_map
			        {
				[0.3 colour Couleur1 ]
				[0.3 0.5 colour Couleur1 colour Couleur2]
				[0.5 colour Couleur2 ]
				[1 colour Couleur2]
				}
			}
		normal { bumps 12 }
		finish { ambient 0.4 }
                }

                
#declare Texture2=
        texture 
                {
                pigment 
                        {	
                        marble turbulence 0.1
                        colour_map
                                {
                                [0 color Gris1]
                                [0.3 colour Gris1]
                                [0.5 colour Gris2]
                                [1 colour Gris2]
                                }
                        }
                normal { bumps 2 }
                finish { ambient 0.4 }
                }
                
#declare	
Surface=
        texture
                { 
                bozo turbulence 2
	        texture_map 
	                {	
	                [ 0 Texture1]
			[ 0.4 Texture1]
			[ 0.4001 Texture2]
			[ 1 Texture2]
			}
		}

#declare	Banquise=texture { pigment { White } finish { ambient 0.7}}

sphere { 0, 1

         texture
                {
        		
        	gradient y turbulence 0.2
        	    texture_map {
        				      [0.85 Surface ]
        				      [0.995 Banquise  ]    //this is a texture identifier
        				     }
        		frequency 1
        		}
	rotate y*clock*360
	rotate x*-15
	}


