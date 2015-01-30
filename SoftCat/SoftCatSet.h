// SoftCatSet.h : interface of the CSoftCatSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOFTCATSET_H__20C5DF35_BAF8_4ED1_8645_A6DEB410CFB1__INCLUDED_)
#define AFX_SOFTCATSET_H__20C5DF35_BAF8_4ED1_8645_A6DEB410CFB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSoftCatSet : public CRecordset
{
public:
	CSoftCatSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSoftCatSet)

// Field/Param Data
	//{{AFX_FIELD(CSoftCatSet, CRecordset)
	long	m_Numero;
	CString	m_Nom;
	CString	m_Description;
	long	m_NumeroDeMedia;
	CString	m_FichierIcone;
	int	m_IndexIcone;
	long	m_Numero2;
	CString	m_Nom2;
	CString	m_Description2;
	CByteArray	m_MotCles;
	long	m_N_;
	CString	m_Nom3;
	CTime	m_Date;
	CString	m_Support;
	CString	m_Commentaire;
	int	m_Icone;
	CString	m_MotCle;
	long	m_NoFichier;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftCatSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTCATSET_H__20C5DF35_BAF8_4ED1_8645_A6DEB410CFB1__INCLUDED_)

