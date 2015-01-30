///////////////////////////////////////////////////////////////////////////////
// CLPICouleur
//	Manipulation aisee des couleurs RGB
///////////////////////////////////////////////////////////////////////////////
#ifndef __LpiCouleur_h__
#define __LpiCouleur_h__

class	CLPICouleur	:	public	CObject
{
	DECLARE_SERIAL(CLPICouleur) ;
	public	:
		CLPICouleur() ;
		CLPICouleur( COLORREF ) ;
		CLPICouleur( int, int, int ) ;

		///////////////////////////////////////////////////////////////////////
		// Acces aux composantes de couleur
		///////////////////////////////////////////////////////////////////////
		int		RValue() const ;
		int		GValue() const ;
		int		BValue() const ;
		void	RValue( int ) ;
		void	GValue( int ) ;
		void	BValue( int ) ;

		operator	COLORREF() const ;
		CLPICouleur & operator	=	( COLORREF ) ;
		virtual void	Serialize( CArchive & ) ;

		///////////////////////////////////////////////////////////////////////
		//	Manipulation de la couleur
		///////////////////////////////////////////////////////////////////////
		void	PlusFonce( int	Pourcentage ) ;
		void	PlusClair( int	Pourcentage ) ;

		void	RPlusFonce( int	Pourcentage ) ;
		void	RPlusClair( int	Pourcentage ) ;
		void	GPlusFonce( int	Pourcentage ) ;
		void	GPlusClair( int	Pourcentage ) ;
		void	BPlusFonce( int	Pourcentage ) ;
		void	BPlusClair( int	Pourcentage ) ;
		
		CLPICouleur	CouleurLaPlusProche( CDC * ) const ;

		static	const	COLORREF	Noir	;
		static	const	COLORREF	Blanc	;
		static	const	COLORREF	Gris ;
		static	const	COLORREF	Rouge	;
		static	const	COLORREF	Vert	;
		static	const	COLORREF	Bleu	;
		static	const	COLORREF	Jaune	;
		static	const	COLORREF	Magenta ;
		static	const	COLORREF	Cyan ;
		static	const	COLORREF	JauneFonce	;
		static	const	COLORREF	RougeFonce	;
		static	const	COLORREF	VertFonce	;
		static	const	COLORREF	BleuFonce	;
		static	const	COLORREF	GrisFonce	;
		static	const	COLORREF	MagentaFonce ;
		static	const	COLORREF	CyanFonce ;
		

	private :
		COLORREF	_Couleur ;

		static int			ComposantePlusFoncee( int C, int P ) ;
		static int			ComposantePlusClaire( int C, int P ) ;
} ;

#endif
