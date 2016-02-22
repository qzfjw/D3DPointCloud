#pragma once
#include "mesharcball.h"

#define BUFFSIZE  1024
//#define D3D_FVF_CUSTOMVERTEX_POS_NORMAL (D3DFVF_XYZ | D3DFVF_NORMAL )
//struct CUSTOM_VERT_POS_NORMAL {
//	float x,y,z;
//	float nx,ny,nz;
//};

#define D3D_FVF_CUSTOMVERTEX_POS (D3DFVF_XYZ)
struct CUSTOM_VERT_POS{
	float x;
	float y;
	float z;
};
class CPlyMeshArcBall :
	public CMeshArcBall
{
public:
	CPlyMeshArcBall(void);
	virtual ~CPlyMeshArcBall(void);
	const CPlyMeshArcBall& operator=( const CPlyMeshArcBall& rhs );
	long GetSize()
	{
		return m_iVertex;
	};
	CUSTOM_VERT_POS *GetBuffer()
	{
		return m_pVB;
	};
public:
	HRESULT Create( LPCWSTR wszFileName, IDirect3DDevice9* pd3dDevice );
	void Render(LPDIRECT3DDEVICE9 pd3dDevice);
	void BuildBound();
private:
	int	  ReadLine(FILE*fp,char*buf);
	long  ReadVertexCount(FILE *fp);
	void  SkipHeader(FILE *fp);
	void  LoadD3D_VB(IDirect3DDevice9* pd3dDevice );
	float GetFloat(unsigned char *buf);
protected:
	long m_iVertex;    //# vertex 
	char buffer[BUFFSIZE];
	CUSTOM_VERT_POS *m_pVB;
	//short int *m_pIB;
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVB;
	//LPDIRECT3DINDEXBUFFER9  m_pD3DIB;
	CUSTOM_VERT_POS *m_pBoundVB;

};

