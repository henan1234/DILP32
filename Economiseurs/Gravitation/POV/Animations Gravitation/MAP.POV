#include "colors.inc"

// set viewer's position in the scene
camera
{
orthographic
  location  <0.0, 0.0, -30.0> // position of camera <X Y Z>
  direction z            // which way are we looking <X Y Z> & zoom
  up        y                // which way is +up <X Y Z>
  right     x            // which way is +right <X Y Z> and aspect ratio
  look_at   <0.0, 0.0,  0.0> // point center of view at this point <X Y Z>
}


// create a regular point light source
light_source
{  < 0, 0, -20 >   color White }

plane {
		z, 0
		pigment
			{
			bozo turbulence 2
			colour_map
				{ [0 1 color Sienna*2 color Black ]
				}

			scale 0.1
			}
		}
