
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

 
global_settings
{
  assumed_gamma 1.5
}

// ----------------------------------------
camera
{
  location  <0.0, 0, -3>
  direction 1.5*z
  right    x
  look_at   <0.0, 0.1,  0.0>
}


light_source{  <-30, 30, -50> color White*2}
/*
union
	{

#declare Seed=seed(1)
#declare Nb=0
#while (Nb<10) 
	box     
	        {
	        <0.6, 0.6, 0.8>, <-0.6, -0.6, -0.6>
	                    
		   scale < 0.4+rand(Seed)*0.2, 0.4+rand(Seed)*0.2, 0.4+rand(Seed)*0.>
		   translate x*0.5
		   rotate x*rand(Seed)*360
		   rotate y*rand(Seed)*360
		   rotate z*rand(Seed)*360
		   }
	#declare Nb=Nb+1
#end      

#while (Nb < 30 )
        sphere {
		   0, 1
		                    
		   scale < 0.4+rand(Seed)*0.2, 0.4+rand(Seed)*0.2, 0.4+rand(Seed)*0.>
		   translate x*0.5
		   rotate x*rand(Seed)*360
		   rotate y*rand(Seed)*360
		   rotate z*rand(Seed)*360
		   }
	#declare Nb=Nb+1
#end      

	//pigment { Gray40 }
	//finish { ambient 0.5 diffuse 0.8  }
	*/
	    
/*	    
	    
blob
        {                    
        threshold 0.1
        #declare Seed=seed(3)    ;
        #declare Nb=0          ;

        #while (Nb < 40 )
                sphere {
	                <-0.5 + rand(Seed), -0.5+rand(Seed), -0.5+rand(Seed)>,0.3+rand(Seed)*0.7, -1+rand(Seed)*2 }
		                    
	        #declare Nb=Nb+1 ;
        #end      

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

        pigment
                {
                ripples
                turbulence 1
                colour_map
                        {
                        [0 0.4 rgb<0.25, 0.2, 0.1> colour Black]                        
                        [0.6 1 colour Black colour rgb<0.72, 0.72, 0.6>]
                        }
                }
        finish { 
                roughness 3
                }
         rotate y*clock*360
         rotate z*30
         }
           //rotate y*180
           
      	    */
blob
{
  threshold 0.3
#declare Seed=seed(1)
#declare Nb=0 ;

#while (Nb < 10 )
        sphere {
	        <-0.5 + rand(Seed), -0.5+rand(Seed), -0.5+rand(Seed)>,0.6, 0.5+rand(Seed)*0.5}
		                    
	#declare Nb=Nb+1
#end      

#declare Nb=0 ;
#while (Nb < 10 )
        sphere {
	        <-0.5 + rand(Seed), -0.5+rand(Seed), -0.5+rand(Seed)>,0.4, -0.4-rand(Seed)*0.4}
		                    
	#declare Nb=Nb+1
#end      

                
        pigment
                {                
	        granite
	        colour_map
	                {
	                [0 rgb<0.3, 0.2, 0.2>]
	                [1 rgb<0.9, 0.8, 0.8>]
	                }
	        scale 1.5
	        }
	        
	rotate y*clock*360
	rotate x*-35
	rotate z*45
	}
