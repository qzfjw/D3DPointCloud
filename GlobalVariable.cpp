#include "StdAfx.h"
#include "GlobalVariable.h"


CGlobalVariable::CGlobalVariable(void)
{
	m_edtModelStep = 15;
	m_edtModel_X = 13.67;
	m_edtModel_Y = 0;
    m_edtModel_Z = 0;
	m_chkX = TRUE;
	m_chkY = TRUE;
	m_chkZ = FALSE;
	pd3dDevice = NULL;

	for( int i = 0; i < meshes_.GetSize(); ++i )
       meshes_[i].Destroy();
    meshes_.RemoveAll();
	nActiveMesh_ = -1; 
}


CGlobalVariable::~CGlobalVariable(void)
{
	for( int i = 0; i < meshes_.GetSize(); ++i )
       meshes_[i].Destroy();
    meshes_.RemoveAll();
	nActiveMesh_ = -1;
}
