// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.1
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?[esp]
//

#version 3.1

#include "colors.inc"            
#include "stones.inc"

global_settings
{
  assumed_gamma 1.0
}

// ----------------------------------------
camera
{
  location  <0.0, 0, -4.5>
  direction 1.5*z
  right     4/3*x
  look_at   <0.0, 0.15,  0.0>
}


light_source
{
  <-10, 10, -10>
  color White
}
         
blob
        {                    
        threshold 0.4
#declare Seed=seed(1)    ;
#declare Nb=0          ;

#while (Nb < 40 )
        sphere {
	        <-0.5 + rand(Seed), -0.5+rand(Seed), -0.5+rand(Seed)>,0.3+rand(Seed)*0.7, -0.4+rand(Seed) }
		                    
	#declare Nb=Nb+1 ;
#end      

        
        pigment{
        image_map
                {
                gif "image6.gif" // the file to read (iff/gif/tga/png/sys)
                map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
                interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
                once
                } 
                   
           }               
        
        normal
        {   
        bump_map
                { // uses image color or index as bumpiness
                gif "image6.gif" // the file to read (iff/gif/tga/png/sys)
                map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
                interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
                // [use_color | use_index]
                once
                bump_size 3 
                } // bump_map
         }
           //rotate y*180
       }