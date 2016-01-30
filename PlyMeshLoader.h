#ifndef _PLYMESHLOADER_H_
#define _PLYMESHLOADER_H_
#pragma once
#include <d3d9.h>

#define BUFFSIZE  1024
//#define D3D_FVF_CUSTOMVERTEX_POS_NORMAL (D3DFVF_XYZ | D3DFVF_NORMAL )
//struct CUSTOM_VERT_POS_NORMAL {
//	float x,y,z;
//	float nx,ny,nz;
//};

#define D3D_FVF_CUSTOMVERTEX_POS (D3DFVF_XYZ)
struct CUSTOM_VERT_POS{
	float x,y,z;
};


class CPlyMeshLoader
{
private:
	
	int	  ReadLine(FILE*fp,char*buf);
	long  ReadVertexCount(FILE *fp);
	void  SkipHeader(FILE *fp);
	void  LoadD3D_VB();
	
public:
	LRESULT LoadFromFile(IDirect3DDevice9 *pDevice,char*filename,int type); //type=0:文本文件,type=1:二进制文件
	CPlyMeshLoader();
	void Render();
	void  LostDevice();
	void  ResetDevice();
	virtual ~CPlyMeshLoader(void);
private:
	long m_iVertex;    //# vertex 
	CUSTOM_VERT_POS *m_pVB;
	short int *m_pIB;

	char buffer[BUFFSIZE];

	LPDIRECT3DVERTEXBUFFER9 m_pD3DVB;
	LPDIRECT3DINDEXBUFFER9  m_pD3DIB;
	IDirect3DDevice9 *m_pDevice;
};
#endif // _PLYMESHLOADER_H_
