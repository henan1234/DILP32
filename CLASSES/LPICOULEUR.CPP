///////////////////////////////////////////////////////////////////////////////
// CLPICouleur
//	Manipulation aisee des couleurs RGB
///////////////////////////////////////////////////////////////////////////////
#include <afxwin.h>
#include "LpiClasses.h"

const	COLORREF	CLPICouleur::Noir		=	RGB(	0,		0,		0 ) ;
const	COLORREF	CLPICouleur::Blanc		=	RGB(	255,	255,	255 ) ;
const	COLORREF	CLPICouleur::Gris		=	RGB(	192,	192,	192 ) ;
const	COLORREF	CLPICouleur::Rouge		=	RGB(	255,	0,		0 ) ;
const	COLORREF	CLPICouleur::Vert		=	RGB(	0,		255,	0 ) ;
const	COLORREF	CLPICouleur::Bleu		=	RGB(	0,		0,		255 ) ;
const	COLORREF	CLPICouleur::Jaune		=	RGB(	255,	255,	0 ) ;
const	COLORREF	CLPICouleur::Magenta 	=	RGB(	255,	0,		255 ) ;
const	COLORREF	CLPICouleur::Cyan 		=	RGB(	0,		255,	255 ) ;
const	COLORREF	CLPICouleur::JauneFonce	=	RGB(	128,	128,	0 ) ;
const	COLORREF	CLPICouleur::RougeFonce	=	RGB(	128,	0,		0 ) ;
const	COLORREF	CLPICouleur::VertFonce	=	RGB(	0,		128,	0 ) ;
const	COLORREF	CLPICouleur::BleuFonce	=	RGB(	0,		0,		128 ) ;
const	COLORREF	CLPICouleur::GrisFonce	=	RGB(	128,	128,	128 ) ;
const	COLORREF	CLPICouleur::MagentaFonce=	RGB(	128,	0,		128 ) ;
const	COLORREF	CLPICouleur::CyanFonce	=	RGB(	0,		128,	128 ) ;


IMPLEMENT_SERIAL( CLPICouleur, CObject, 0 ) ;

CLPICouleur::CLPICouleur()
{
	_Couleur	=	Noir ;
}

CLPICouleur::CLPICouleur( COLORREF Couleur )
{
	_Couleur	=	Couleur ;
}


CLPICouleur::CLPICouleur( int R, int G, int B )
{
	_Couleur	=	RGB( R, G, B ) ;
}

///////////////////////////////////////////////////////////////////////
// Acces aux composantes de couleur
///////////////////////////////////////////////////////////////////////
int		CLPICouleur::RValue() const
{
	return GetRValue( _Couleur ) ;
}

int		CLPICouleur::GValue() const
{
	return GetGValue( _Couleur ) ;
}

int		CLPICouleur::BValue() const
{
	return GetBValue( _Couleur ) ;
}

void	CLPICouleur::RValue( int C )
{
	_Couleur	=	RGB( C, GetGValue( _Couleur ), GetBValue( _Couleur )) ;
}

void	CLPICouleur::GValue( int C )
{
	_Couleur	=	RGB( GetRValue( _Couleur ), C, GetBValue( _Couleur )) ;
}

void	CLPICouleur::BValue( int C )
{
	_Couleur	=	RGB( GetRValue( _Couleur ), GetGValue( _Couleur ), C ) ;
}

CLPICouleur::operator	COLORREF() const
{
	return _Couleur ;
}

CLPICouleur & CLPICouleur::operator	=( COLORREF C )
{
	_Couleur = C ;
	return *this ;
}

///////////////////////////////////////////////////////////////////////
//	Manipulation de la couleur
///////////////////////////////////////////////////////////////////////
void	CLPICouleur::PlusFonce( int	Pourcentage )
{
	RPlusFonce( Pourcentage ) ;
	GPlusFonce( Pourcentage ) ;
	BPlusFonce( Pourcentage ) ;
}

void	CLPICouleur::PlusClair( int	Pourcentage )
{
	RPlusClair( Pourcentage ) ;
	GPlusClair( Pourcentage ) ;
	BPlusClair( Pourcentage ) ;
}

void	CLPICouleur::RPlusFonce( int	Pourcentage )
{
	RValue( ComposantePlusFoncee( RValue(), Pourcentage )) ;
}

void	CLPICouleur::RPlusClair( int	Pourcentage )
{
	RValue( ComposantePlusClaire( RValue(), Pourcentage )) ;
}

void	CLPICouleur::GPlusFonce( int	Pourcentage )
{
	GValue( ComposantePlusFoncee( GValue(), Pourcentage )) ;
}

void	CLPICouleur::GPlusClair( int	Pourcentage )
{
	GValue( ComposantePlusClaire( GValue(), Pourcentage )) ;
}

void	CLPICouleur::BPlusFonce( int	Pourcentage )
{
	BValue( ComposantePlusFoncee( BValue(), Pourcentage )) ;
}

void	CLPICouleur::BPlusClair( int	Pourcentage ) 
{
	BValue( ComposantePlusClaire( BValue(), Pourcentage )) ;
}

CLPICouleur	CLPICouleur::CouleurLaPlusProche( CDC * pDc ) const
{
	return pDc->GetNearestColor( _Couleur ) ;
}

///////////////////////////////////////////////////////////////////////////////                  
// ComposantePlusFoncee
//	Rendre une composante plus foncee (tout en restant dans la plage 0..255
///////////////////////////////////////////////////////////////////////////////                  
int	CLPICouleur::ComposantePlusFoncee( int C, int Pct )
{
	ASSERT( Pct >= 0 ) ;
	ASSERT( Pct <= 100 ) ;

	C	-= ( C * Pct ) / 100  ;
	C	=	min( 255, max( 0, C )) ;
	return C ;
}


///////////////////////////////////////////////////////////////////////////////                  
// ComposantePlusClaire
//	Rendre une composante plus claire (tout en restant dans la plage 0..255
///////////////////////////////////////////////////////////////////////////////                  
int	CLPICouleur::ComposantePlusClaire( int C, int Pct )
{
	ASSERT( Pct >= 0 ) ;
	ASSERT( Pct <= 100 ) ;

	C	+= (( 255 - C ) * Pct) / 100 ;
	C	=	min( 255, max( 0, C )) ;
	return C ;
}

///////////////////////////////////////////////////////////////////////////////                  
// Serialisation
///////////////////////////////////////////////////////////////////////////////                  
void	CLPICouleur::Serialize( CArchive & ar )
{
	CObject::Serialize( ar ) ;
	if(	ar.IsLoading())
		{
		ar >> _Couleur ;
		}
	else
		{
		ar << _Couleur ;
		}
}
