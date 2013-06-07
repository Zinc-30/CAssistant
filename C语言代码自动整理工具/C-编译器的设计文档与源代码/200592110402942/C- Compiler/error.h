#if !defined(AFX_ERROR_H__6A381C9B_C266_4DED_90BF_8296A513E8BF__INCLUDED_)
#define AFX_ERROR_H__6A381C9B_C266_4DED_90BF_8296A513E8BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	ERROR_INVALID_TYPE,
	ERROR_DECLARATION,
	ERROR_SEMICOLON_MISS
};

class _error
{
public:
	_error( int id, int param = 0, const CString& comment = _T("") ) :
	  m_id( id ), m_param( param ), m_strComment( comment ) {}
	~_error() {}

// Attributes
public:
	int		m_id;
	int		m_param;
	CString m_strComment;

// Operations
public:
	CString GetStrError();
};

#endif // !defined(AFX_ERROR_H__6A381C9B_C266_4DED_90BF_8296A513E8BF__INCLUDED_)
