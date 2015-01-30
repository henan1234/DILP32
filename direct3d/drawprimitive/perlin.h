
#if !defined _PERLIN_H_INCLUDED_
#define _PERLIN_H_INCLUDED_

#define D3D_OVERLOADS

#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <float.h>
#include <d3d.h>

#include "d3dutils.h"

float 		PerlinNoise1D (D3DVECTOR & vec);
float 		PerlinTurbulence1D (D3DVECTOR & point, int terms);
D3DVECTOR	PerlinNoise3D (D3DVECTOR & vec);
D3DVECTOR	PerlinTurbulence3D (D3DVECTOR & point, int terms);

#endif	// _PERLIN_H_INCLUDED_


