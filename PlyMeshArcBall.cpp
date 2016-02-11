#include "StdAfx.h"
#include "PlyMeshArcBall.h"


CPlyMeshArcBall::CPlyMeshArcBall(void)
{
	m_pVB = NULL;
	m_pBoundVB = NULL;

	m_pD3DVB = NULL;
	m_iVertex = 0;
}


CPlyMeshArcBall::~CPlyMeshArcBall(void)
{
	SAFE_DELETE(m_pVB);
	SAFE_DELETE(m_pBoundVB);
	//SAFE_DELETE(m_pIB);
	SAFE_RELEASE(m_pD3DVB);
	//SAFE_RELEASE(m_pD3DIB);
}
HRESULT CPlyMeshArcBall::Create( LPCWSTR wszFileName, IDirect3DDevice9* pd3dDevice )
{
	FILE	 *fp;
	size_t len = wcslen(wszFileName) + 1;
	size_t converted = 0;
	char *szFileName;

	wcscpy_s( wszFile_, MAX_PATH, wszFileName);

	szFileName=(char*)malloc(len*sizeof(char));
	wcstombs_s(&converted, szFileName, len,wszFileName, _TRUNCATE);
	if ((fp = fopen(szFileName, "rb")) == NULL) 
	{ 
		printf("open file error!\n");
		return -1;
	}
	free(szFileName);

	long vn = ReadVertexCount(fp);//read #vertex
	if( m_pVB != NULL )
	{
		free( m_pVB );
		m_pVB = NULL;
	}
	SkipHeader(fp);//skip remain header
	fseek(fp,1,SEEK_CUR);
	

	m_pVB = ( CUSTOM_VERT_POS*)malloc(vn*sizeof(CUSTOM_VERT_POS));//read vertex data 
	CUSTOM_VERT_POS*pVertex=m_pVB;
	
	unsigned char RF6[6*sizeof(float)];
	float maxx,maxy,maxz,minx,miny,minz; 
	maxx=maxy=maxz=FLT_MIN;
	minx=miny=minz=FLT_MAX;
	for(long i=0; (i<vn)&&!feof(fp); i++)
	{
		fread((void*)RF6,sizeof(float),6,fp);//读取6个浮点数
		unsigned char *p = RF6;
		pVertex->x =GetFloat(p);
		p+=sizeof(float);
		pVertex->y = GetFloat(p);
		p+=sizeof(float);
		pVertex->z = GetFloat(p);
	
		if(pVertex->x>maxx)maxx=pVertex->x;
		else if(pVertex->x<minx)minx=pVertex->x;
		
		if(pVertex->y>maxy)maxy=pVertex->y;
		else if(pVertex->y<miny)miny=pVertex->y;
		
		if(pVertex->z>maxz)maxz=pVertex->z;
		else if(pVertex->z<minz)minz=pVertex->z;
		
		pVertex++;

	}

	
	v3max_ = D3DXVECTOR3(maxx,maxy,maxz);
	v3min_ = D3DXVECTOR3(minx,miny,minz);
	//D3DXMatrixTranslation(mat,-v3max.x,-v3max.y,-v3max.z);
	model_orgin_ =(v3max_ + v3min_)/2;
	//model_orgin_.x +=150;
	D3DXVECTOR3 volume = v3max_ - v3min_;

	
	m_iVertex = vn;
	LoadD3D_VB(pd3dDevice);
	BuildBound();
	fclose(fp);
	return 0;
}

void CPlyMeshArcBall::BuildBound()
{
	m_pBoundVB = ( CUSTOM_VERT_POS*)malloc(24*sizeof(CUSTOM_VERT_POS));//read vertex data 
	CUSTOM_VERT_POS t[8];
	t[0].z = v3min_.z , t[0].x = v3max_.x , t[0].y = v3max_.y;
	t[1].z = v3min_.z , t[1].x = v3min_.x , t[1].y = v3max_.y;
	t[2].z = v3min_.z , t[2].x = v3min_.x , t[2].y = v3min_.y;
	t[3].z = v3min_.z , t[3].x = v3max_.x , t[3].y = v3min_.y;

	t[4].z = v3max_.z , t[4].x = v3max_.x , t[4].y = v3max_.y;
	t[5].z = v3max_.z , t[5].x = v3min_.x , t[5].y = v3max_.y;
	t[6].z = v3max_.z , t[6].x = v3min_.x , t[6].y = v3min_.y;
	t[7].z = v3max_.z , t[7].x = v3max_.x , t[7].y = v3min_.y;
	
	int i=0;
	m_pBoundVB[i++] = t[0],m_pBoundVB[i++] = t[1],m_pBoundVB[i++] = t[1],m_pBoundVB[i++] = t[2];
	m_pBoundVB[i++] = t[2],m_pBoundVB[i++] = t[3],m_pBoundVB[i++] = t[3],m_pBoundVB[i++] = t[0];

	m_pBoundVB[i++] = t[4],m_pBoundVB[i++] = t[5],m_pBoundVB[i++] = t[5],m_pBoundVB[i++] = t[6];
	m_pBoundVB[i++] = t[6],m_pBoundVB[i++] = t[7],m_pBoundVB[i++] = t[7],m_pBoundVB[i++] = t[4];

	m_pBoundVB[i++] = t[0],m_pBoundVB[i++] = t[4],m_pBoundVB[i++] = t[1],m_pBoundVB[i++] = t[5];
	m_pBoundVB[i++] = t[2],m_pBoundVB[i++] = t[6],m_pBoundVB[i++] = t[3],m_pBoundVB[i++] = t[7];



}
const CPlyMeshArcBall& CPlyMeshArcBall::operator=(const CPlyMeshArcBall& rhs)
{
	if( this == &rhs )
		return *this;
	wcscpy_s( wszFile_, MAX_PATH, rhs.wszFile_ );

	frame_need_update_ = rhs.frame_need_update_;
	model_scal_factor_ = rhs.model_scal_factor_;		
	model_orgin_ = rhs.model_orgin_;
	model_volume_= rhs.model_volume_;
	world_matrix_ = rhs.world_matrix_;
	world_arcball_ = rhs.world_arcball_;
	v3pos_ = rhs.v3pos_;
		
    SAFE_RELEASE(p_model_mesh_);
	if( (p_model_mesh_ = rhs.p_model_mesh_ ) != 0 ) p_model_mesh_->AddRef();
	SAFE_RELEASE(m_pD3DVB);
	if( (m_pD3DVB = rhs.m_pD3DVB) != 0 ) m_pD3DVB->AddRef();
	
	m_iVertex = rhs.m_iVertex;    //# vertex 
	if(rhs.m_pVB!=NULL)
	{
		m_pVB = ( CUSTOM_VERT_POS*)malloc(m_iVertex*sizeof(CUSTOM_VERT_POS));//read vertex data 
		memcpy( m_pVB, rhs.m_pVB,  m_iVertex*sizeof(CUSTOM_VERT_POS) );
	}
	if(rhs.m_pBoundVB!=NULL)
	{
		m_pBoundVB = ( CUSTOM_VERT_POS*)malloc(24*sizeof(CUSTOM_VERT_POS));//read vertex data 
		memcpy( m_pBoundVB, rhs.m_pBoundVB,  24*sizeof(CUSTOM_VERT_POS) );
	}

	
    return *this;

}
void CPlyMeshArcBall::Render(LPDIRECT3DDEVICE9 pd3dDevice)
{
	

	pd3dDevice->SetTransform(D3DTS_WORLD, &world_matrix_);
	pd3dDevice->SetStreamSource(0, m_pD3DVB, 0, sizeof(CUSTOM_VERT_POS));
	pd3dDevice->SetIndices(NULL);
	pd3dDevice->SetFVF(D3D_FVF_CUSTOMVERTEX_POS);
	pd3dDevice->DrawPrimitive(D3DPT_POINTLIST,0, m_iVertex);
	pd3dDevice->DrawPrimitiveUP(D3DPT_LINELIST,12,m_pBoundVB,sizeof(CUSTOM_VERT_POS));
	//m_pDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_NONE);
	//pD3DDevice->SetIndices(g_pIB);
	//pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_iNumRows*g_iNumCols, 0, (g_iNumRows-1)*(g_iNumCols-1)*2)))
	
	//m_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST,m_iVertex,m_pVB,sizeof(CUSTOM_VERT_POS));
	//m_pDevice->DrawPrimitive(D3DPT_LINESTRIP,0,m_iVertex-1);
}
void CPlyMeshArcBall::LoadD3D_VB(IDirect3DDevice9* pd3dDevice )
{
	int iResult = -1;

	SAFE_RELEASE(m_pD3DVB);
	iResult = pd3dDevice->CreateVertexBuffer( m_iVertex*sizeof(CUSTOM_VERT_POS), 
											 D3DUSAGE_WRITEONLY, 
											 D3D_FVF_CUSTOMVERTEX_POS, 
											 D3DPOOL_MANAGED,//DEFAULT, 
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
int CPlyMeshArcBall::ReadLine(FILE*fp,char*buf)
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

long  CPlyMeshArcBall::ReadVertexCount(FILE *fp)
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

void CPlyMeshArcBall::SkipHeader(FILE *fp)
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
float CPlyMeshArcBall::GetFloat(unsigned char *buf)
{
	
	/*unsigned char temp[sizeof(float)];
	for(int k=0; k < sizeof(float); k++)
		temp[sizeof(float)-k-1]=*buf++;

	float *p = (float *) temp;*/
	float *p = (float*)buf;
	return *p;
}
