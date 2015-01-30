// MosaiqueDoc.h : interface of the CMosaiqueDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOSAIQUEDOC_H__8987664C_40B7_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_MOSAIQUEDOC_H__8987664C_40B7_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CImage ;

class CMosaiqueDoc : public CDocument
{
protected: // create from serialization only
	CMosaiqueDoc();
	DECLARE_DYNCREATE(CMosaiqueDoc)

// Attributes
public:

	void OnCloseDocument()  ;
	int NbImages() ;
	CImage * GetImage(int i) ;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMosaiqueDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Deplace( int IndiceDepart, int IndiceArrivee );
	BOOL PlusBas( int Indice );
	BOOL PlusHaut( int Indice );
	void NbColonnes( int NbColonnes );
	void NbLignes (int NbLignes );
	int _NbLignes;
	int NbColonnes();
	int NbLignes();
	BOOL AjouteImage( const char * pImage );
	virtual ~CMosaiqueDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMosaiqueDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int _NbColonnes;
	CObArray _Images ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_MOSAIQUEDOC_H__8987664C_40B7_11D1_AEF5_444553540000__INCLUDED_)
