#include "StdAfx.h"
#include "DXUT.h"
#include "PlyMeshLoader.h"


CPlyMeshLoader::CPlyMeshLoader()
{
	m_iVertex = 0;
	m_pVB = NULL;
	m_pIB = NULL;

	m_pD3DVB = NULL;
	m_pD3DIB = NULL;

}


LRESULT CPlyMeshLoader::LoadFromFile(IDirect3DDevice9 *pDevice,char*filename,int type)
{
	
	FILE	 *fp;
	if ((fp = fopen(filename, "rb")) == NULL) 
	{ 
		printf("open file error!\n");
		return -1;
	}

	long vn = ReadVertexCount(fp);//read #vertex
	if( m_pVB != NULL )
	{
		free( m_pVB );
		m_pVB = NULL;
	}
	SkipHeader(fp);//skip remain header
	//printf("%ld\n",vn);

	m_pVB = ( CUSTOM_VERT_POS*)malloc(vn*sizeof(CUSTOM_VERT_POS));//read vertex data 
	CUSTOM_VERT_POS*pVertex=m_pVB;
	//long rvn = fread((void*)m_pVB,sizeof(CUSTOM_VERT_POS),vn,fp);

	//memcpy( pVerts, m_pVB, m_iNumRows*m_iNumCols*sizeof(CUSTOM_VERT_POS_NORMAL_TEXTURE0) );

	float F6[6];
	double maxx=DBL_MIN,maxy=DBL_MIN,maxz=DBL_MIN;
	double minx=DBL_MAX,miny=DBL_MAX,minz=DBL_MAX;

	for(long i=0; (i<vn)&&!feof(fp); i++)
	{
		float *p;
		fread((void*)F6,sizeof(float),6,fp);//读取6个浮点数
		p=F6;

		if(*p>maxx)maxx=*p;
		else if(*p<minx)minx=*p;
		pVertex->x = *p++;

		if(*p>maxy)maxy=*p;
		else if(*p<miny)miny=*p;
		pVertex->y = *p++;

		if(*p>maxz)maxz=*p;
		else if(*p<minz)minz=*p;
		pVertex->z = *p++;

		pVertex++;

	}
	//D3DXVECTOR3 v3max(maxx,maxy,maxz);
	//D3DXVECTOR3 v3min(minx,miny,minz);
	//D3DXVECTOR3 dis(1.0f/(maxx-minx),1.0f/(maxy-miny),1.0f/(maxz-minz));
	double dx=1.0/(maxx-minx),dy=1.0/(maxy-miny),dz=1.0/(maxz-minz);


	pVertex=m_pVB;
	for(long i=0; i<vn; i++)
	{
		pVertex->x = -1.0f + (pVertex->x - minx)*dx*2.0;
		pVertex->y = -1.0f + (pVertex->y - miny)*dy*2.0;
		pVertex->z = -1.0f + (pVertex->z - minz)*dz*2.0;
		pVertex++;
	}

	m_iVertex = vn;
	m_pDevice = pDevice;
	LoadD3D_VB();

	fclose(fp);

	return 0;

}

void CPlyMeshLoader::Render()
{
	m_pDevice->SetStreamSource(0, m_pD3DVB, 0, sizeof(CUSTOM_VERT_POS));
	m_pDevice->SetIndices(NULL);
	m_pDevice->SetFVF(D3D_FVF_CUSTOMVERTEX_POS);
	//pD3DDevice->SetIndices(g_pIB);
	//pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_iNumRows*g_iNumCols, 0, (g_iNumRows-1)*(g_iNumCols-1)*2)))
	m_pDevice->DrawPrimitive(D3DPT_POINTLIST,0, m_iVertex);
				

}
void  CPlyMeshLoader::LostDevice()
{
	SAFE_RELEASE(m_pD3DVB);

}
void  CPlyMeshLoader::ResetDevice()
{
	LoadD3D_VB();
}
void CPlyMeshLoader::LoadD3D_VB()
{
	int iResult = -1;

	SAFE_RELEASE(m_pD3DVB);
	iResult = m_pDevice->CreateVertexBuffer( m_iVertex*sizeof(CUSTOM_VERT_POS), 
											 D3DUSAGE_WRITEONLY, 
											 D3D_FVF_CUSTOMVERTEX_POS, 
											 D3DPOOL_DEFAULT, 
											 &m_pD3DVB, 
											 NULL );
	if( iResult != D3D_OK )
	{
		printf( "Create VB Failed\n" );
	}

	//now fill VB
	VOID *pVerts = NULL;
	iResult = m_pD3DVB->Lock( 0, m_iVertex*sizeof(CUSTOM_VERT_POS), (void **)&pVerts, 0 );
	if( iResult != D3D_OK )
	{
		printf( "Fill VB fail\n" );
	}
	memcpy( pVerts, m_pVB,  m_iVertex*sizeof(CUSTOM_VERT_POS) );
	m_pD3DVB->Unlock();
}

CPlyMeshLoader::~CPlyMeshLoader(void)
{
	SAFE_DELETE(m_pVB);
	SAFE_DELETE(m_pIB);
	SAFE_RELEASE(m_pD3DVB);
	SAFE_RELEASE(m_pD3DIB);
}

int CPlyMeshLoader::ReadLine(FILE*fp,char*buf)
{	
	char c;
	int n=0;
	while(!feof(fp))
	{
		c = fgetc(fp);
		//int ungetc(int c,FILE * stream);
		if(c!='\n' && c!='\r')
		{
			*buf++ = c;
			n++;
		}
		else
			break;
	}
	*buf='\0';
	return n;
}

long  CPlyMeshLoader::ReadVertexCount(FILE *fp)
{
	int n=0;
	long vn = 0;
	char *p;
	while(!feof(fp))
	{
		n =  ReadLine(fp,buffer);
		//printf("%d\n",n);
		p = strstr(buffer,"element vertex");
		if(p!=NULL)
		{
			p = buffer + (p - buffer) + strlen("element vertex");
			sscanf_s(p,"%ld",&vn);
			
			return vn;
		}
		
	}
	return -1;

}

void CPlyMeshLoader::SkipHeader(FILE *fp)
{
	int n=0;
	char*p;
	while(!feof(fp))
	{
		n =  ReadLine(fp,buffer);
		//printf("%d\n",n);
		p = strstr(buffer,"end_header");
		if(p!=NULL)
			break;
	}

}