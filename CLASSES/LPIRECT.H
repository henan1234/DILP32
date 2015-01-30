///////////////////////////////////////////////////////////////////////////////
//	CLPIClientRect
//	Un CRect construit directement avec les dimension d'une zone client
///////////////////////////////////////////////////////////////////////////////

#ifndef __LPIRECT_H__
#define __LPIRECT_H__

class	CLPIRect : public CRect
{
	public	:
		CLPIRect()	{} ;
		CLPIRect( int x, int y, int x2, int y2 ) : CRect( x, y, x2, y2 ) {} ;
		CLPIRect( CWnd * ) ;
		operator	CRect( void ) const ;
		
		void	Serialize( CArchive & ) ;		
} ;


#endif
