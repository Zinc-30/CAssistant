// error.cpp : implementation file
//

#include "stdafx.h"
#include "error.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString _error::GetStrError()
{
	CString ret = _T("");

	switch( m_id ) {
	case ERROR_INVALID_TYPE:
		ret.Format( "error in line %d: invalid type '%s'", m_param, m_strComment );
		break;

	case ERROR_DECLARATION:
		ret.Format( "error in line %d: '%s' is reserved", m_param, m_strComment );
		break;

	case ERROR_SEMICOLON_MISS:
		ret.Format( "error in line %d: missing ';' after identifier \"%s\"", m_param, m_strComment );
		break;
	}

	return ret;
}
