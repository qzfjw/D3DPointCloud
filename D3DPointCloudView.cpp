
// D3DPointCloudView.cpp : CD3DPointCloudView 类的实现
//

#include "stdafx.h"
#include "DXUT.h"
#include "SDKmisc.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "D3DPointCloud.h"
#endif

#include "D3DPointCloudDoc.h"
#include "D3DPointCloudView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CD3DPointCloudView

IMPLEMENT_DYNCREATE(CD3DPointCloudView, CView)

BEGIN_MESSAGE_MAP(CD3DPointCloudView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CD3DPointCloudView 构造/析构

CD3DPointCloudView::CD3DPointCloudView()
	:_device(0), _teapot(0)
{
	// TODO: 在此处添加构造代码
	::ZeroMemory(&_d3dpp, sizeof(_d3dpp));
	g_pEffect = NULL;      

	g_hAmbient = NULL;
	g_hDiffuse = NULL;
	g_hSpecular = NULL;
	g_hOpacity = NULL;
	g_hSpecularPower = NULL;
	g_hLightColor = NULL;
	g_hLightPosition = NULL;
	g_hCameraPosition = NULL;
	g_hTexture = NULL;
	g_hTime = NULL;
	g_hWorld = NULL;
	g_hWorldViewProjection = NULL;

}
HRESULT CD3DPointCloudView::initD3D(HWND hwnd,int width,int height,bool windowed,D3DDEVTYPE deviceType)
{
	HRESULT hr = 0;
	// Step 1: Create the IDirect3D9 object.
	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if( !d3d9 )
	{
		::MessageBox(0, L"Direct3DCreate9() - FAILED", 0, 0);
		return E_FAIL;
	}
	// Step 2: Check for hardware vp.
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);
	int vp = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
	_d3dpp.BackBufferWidth = width;
	_d3dpp.BackBufferHeight = height;
	_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	_d3dpp.BackBufferCount = 1;
	_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	_d3dpp.MultiSampleQuality = 0;
	_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3dpp.hDeviceWindow = hwnd;
	_d3dpp.Windowed = windowed;
	_d3dpp.EnableAutoDepthStencil = true;
	_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	_d3dpp.Flags = 0;
	_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	_d3dpp.PresentationInterval =D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 4: Create the device.
	hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, // primary adapter
		deviceType, // device type
		hwnd, // window associated with device
		vp, // vertex processing
		&_d3dpp, // present parameters
		&_device); // return created device
	if( FAILED(hr) )
	{
		// try again using a safer configuration.
		_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT,deviceType,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&_d3dpp,&_device);
		if( FAILED(hr) )
		{
			d3d9->Release(); // done with d3d9 object
			::MessageBox(0, L"CreateDevice() - FAILED", 0, 0);
			return hr;
		}
	}
		d3d9->Release(); // done with d3d9 object
		return S_OK;
}
HRESULT CD3DPointCloudView::setup(int width, int height)
{
	HRESULT hr=0;
	WCHAR str[MAX_PATH];
	
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

	#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DXSHADER_DEBUG;
    #endif

	#ifdef DEBUG_VS
        dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
    #endif
	#ifdef DEBUG_PS
        dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
    #endif
	if( _device )
	{
		// Create the mesh and load it with data already gathered from a file
		V_RETURN( g_MeshLoader.Create( _device, L"media\\cup.obj" ) );
		 // Read the D3DX effect file
		V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"MeshFromOBJ.fx" ) );

		// If this fails, there should be debug output as to 
		// they the .fx file failed to compile
		V_RETURN( D3DXCreateEffectFromFile( _device, str, NULL, NULL, dwShaderFlags,
									     NULL, &g_pEffect, NULL ) );
		// Cache the effect handles
		g_hAmbient = g_pEffect->GetParameterBySemantic( 0, "Ambient" );
		g_hDiffuse = g_pEffect->GetParameterBySemantic( 0, "Diffuse" );
		g_hSpecular = g_pEffect->GetParameterBySemantic( 0, "Specular" );
		g_hOpacity = g_pEffect->GetParameterBySemantic( 0, "Opacity" );
		g_hSpecularPower = g_pEffect->GetParameterBySemantic( 0, "SpecularPower" );
		g_hLightColor = g_pEffect->GetParameterBySemantic( 0, "LightColor" );
		g_hLightPosition = g_pEffect->GetParameterBySemantic( 0, "LightPosition" );
		g_hCameraPosition = g_pEffect->GetParameterBySemantic( 0, "CameraPosition" );
		g_hTexture = g_pEffect->GetParameterBySemantic( 0, "Texture" );
		g_hTime = g_pEffect->GetParameterBySemantic( 0, "Time" );
		g_hWorld = g_pEffect->GetParameterBySemantic( 0, "World" );
		g_hWorldViewProjection = g_pEffect->GetParameterBySemantic( 0, "WorldViewProjection" );

		 // Store the correct technique handles for each material
		for( UINT i = 0; i < g_MeshLoader.GetNumMaterials(); i++ )
		{
			Material* pMaterial = g_MeshLoader.GetMaterial( i );

			const char* strTechnique = NULL;

			if( pMaterial->pTexture && pMaterial->bSpecular )
				strTechnique = "TexturedSpecular";
			else if( pMaterial->pTexture && !pMaterial->bSpecular )
				strTechnique = "TexturedNoSpecular";
			else if( !pMaterial->pTexture && pMaterial->bSpecular )
				strTechnique = "Specular";
			else if( !pMaterial->pTexture && !pMaterial->bSpecular )
				strTechnique = "NoSpecular";

			pMaterial->hTechnique = g_pEffect->GetTechniqueByName( strTechnique );
		}


		// Set view matrix.
		D3DXMATRIX V;
		D3DXVECTOR3 pos (0.0f, 0.0f, -6.0f);
		D3DXVECTOR3 target (0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up (0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&V, &pos, &target, &up);
		_device->SetTransform(D3DTS_VIEW, &V);
		// Create the teapot.
		if( !_teapot)
			D3DXCreateTeapot(_device, &_teapot, 0);
		// Use wireframe mode and turn off lighting.
		//_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		_device->SetRenderState(D3DRS_LIGHTING, false);
		// Size the viewport based on window dimensions.
		D3DVIEWPORT9 vp = {0, 0, width, height, 0.0f, 1.0f};
		_device->SetViewport( &vp );
		// Set the projection matrix based on the
		// window dimensions.
		D3DXMATRIX P;
		D3DXMatrixPerspectiveFovLH(&P,D3DX_PI * 0.25f,//45-degree field of view
			(float)width / (float)height,1.0f,1000.0f);
		_device->SetTransform(D3DTS_PROJECTION, &P);

		 // Setup the camera's view parameters
		D3DXVECTOR3 vecEye( 2.0f, 1.0f, 0.0f );
		D3DXVECTOR3 vecAt ( 0.0f, 0.0f, -0.0f );
		g_Camera.SetViewParams( &vecEye, &vecAt );

		// Setup the camera's projection parameters
		float fAspectRatio = (float)width / (float)height;
		g_Camera.SetProjParams( D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f );
		g_Camera.SetWindow(width,height );

		_device->SetTransform(D3DTS_WORLD, g_Camera.GetWorldMatrix());
		_device->SetTransform(D3DTS_VIEW, g_Camera.GetViewMatrix());
		_device->SetTransform(D3DTS_PROJECTION, g_Camera.GetProjMatrix());
	}

	

	return S_OK;
}
HRESULT CD3DPointCloudView::cleanup()
{
	// Nothing to Destroy.
	return S_OK;
}

HRESULT CD3DPointCloudView::update(float fElapsedTime )
{
	if( _device )
	{
		//
		// Spin the teapot around the y-axis.
		//
		static float angle = 0.0f;
		D3DXMATRIX yRotationMatrix;
		D3DXMatrixRotationY(&yRotationMatrix, angle);
		//_device->SetTransform(D3DTS_WORLD, &yRotationMatrix);
		angle += fElapsedTime ;
		if(angle >= D3DX_PI * 2.0f)
			angle = 0.0f;
	}
	 g_Camera.FrameMove( fElapsedTime  );
	
	return S_OK;
}
HRESULT CD3DPointCloudView::render(double fTime, float fElapsedTime)
{
	////HRESULT hr;
 //   D3DXMATRIXA16 mWorld;
 //   D3DXMATRIXA16 mView;
 //   D3DXMATRIXA16 mProj;
 //   //D3DXMATRIXA16 mWorldViewProjection;


	//mWorld = *g_Camera.GetWorldMatrix();
 //   mView =  *g_Camera.GetViewMatrix();
 //   mProj =  *g_Camera.GetProjMatrix();
	////mWorldViewProjection = mWorld * mView * mProj;

	//_device->SetTransform(D3DTS_WORLD, &mWorld);
	//_device->SetTransform(D3DTS_VIEW, &mView);
	//_device->SetTransform(D3DTS_PROJECTION, &mProj);
	//

	//if( _device )
	//{
	//	//
	//	// Draw the scene.
	//	//
	//	_device->Clear(0, 0,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0x00000000, 1.0f, 0);
	//	_device->BeginScene();
	//	// Draw the teapot.
	//	_teapot->DrawSubset(0);
	//	_device->EndScene();
	//	_device->Present(0, 0, 0, 0);
	//}

	HRESULT hr;
    D3DXMATRIXA16 mWorld;
    D3DXMATRIXA16 mView;
    D3DXMATRIXA16 mProj;
    D3DXMATRIXA16 mWorldViewProjection;


    // Clear the render target and the zbuffer 
    V( _device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 141, 153, 191 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( _device->BeginScene() ) )
    {
        // Get the projection & view matrix from the camera class
        mWorld = *g_Camera.GetWorldMatrix();
        mView  = *g_Camera.GetViewMatrix();
        mProj  = *g_Camera.GetProjMatrix();

        mWorldViewProjection = mWorld * mView * mProj;

        // Update the effect's variables. 
        V( g_pEffect->SetMatrix( g_hWorldViewProjection, &mWorldViewProjection ) );
        V( g_pEffect->SetMatrix( g_hWorld, &mWorld ) );
        V( g_pEffect->SetFloat( g_hTime, ( float )fTime ) );
        V( g_pEffect->SetValue( g_hCameraPosition, g_Camera.GetEyePt(), sizeof( D3DXVECTOR3 ) ) );

        //UINT iCurSubset = ( UINT )( INT_PTR )g_SampleUI.GetComboBox( IDC_SUBSET )->GetSelectedData();
		UINT iCurSubset = -1;
        // A subset of -1 was arbitrarily chosen to represent all subsets
        if( iCurSubset == -1 )
        {
            // Iterate through subsets, changing material properties for each
            for( UINT iSubset = 0; iSubset < g_MeshLoader.GetNumMaterials(); iSubset++ )
            {
                RenderSubset( iSubset );
            }
        }
        else
        {
            RenderSubset( iCurSubset );
        }

       

        V( _device->EndScene() );
		_device->Present(0, 0, 0, 0);
    }

	return S_OK;
}
//--------------------------------------------------------------------------------------
void CD3DPointCloudView::RenderSubset( UINT iSubset )
{
    HRESULT hr;
    UINT iPass, cPasses;

    // Retrieve the ID3DXMesh pointer and current material from the MeshLoader helper
    ID3DXMesh* pMesh = g_MeshLoader.GetMesh();
    Material* pMaterial = g_MeshLoader.GetMaterial( iSubset );

    // Set the lighting variables and texture for the current material
    V( g_pEffect->SetValue( g_hAmbient, pMaterial->vAmbient, sizeof( D3DXVECTOR3 ) ) );
    V( g_pEffect->SetValue( g_hDiffuse, pMaterial->vDiffuse, sizeof( D3DXVECTOR3 ) ) );
    V( g_pEffect->SetValue( g_hSpecular, pMaterial->vSpecular, sizeof( D3DXVECTOR3 ) ) );
    V( g_pEffect->SetTexture( g_hTexture, pMaterial->pTexture ) );
    V( g_pEffect->SetFloat( g_hOpacity, pMaterial->fAlpha ) );
    V( g_pEffect->SetInt( g_hSpecularPower, pMaterial->nShininess ) );

    V( g_pEffect->SetTechnique( pMaterial->hTechnique ) );
    V( g_pEffect->Begin( &cPasses, 0 ) );

    for( iPass = 0; iPass < cPasses; iPass++ )
    {
        V( g_pEffect->BeginPass( iPass ) );

        // The effect interface queues up the changes and performs them 
        // with the CommitChanges call. You do not need to call CommitChanges if 
        // you are not setting any parameters between the BeginPass and EndPass.
        // V( g_pEffect->CommitChanges() );

        // Render the mesh with the applied technique
        V( pMesh->DrawSubset( iSubset ) );

        V( g_pEffect->EndPass() );
    }
    V( g_pEffect->End() );
}


CD3DPointCloudView::~CD3DPointCloudView()
{
	if( _teapot )
		_teapot->Release();
	if( _device )
		_device->Release();
	g_MeshLoader.Destroy();
}

BOOL CD3DPointCloudView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CD3DPointCloudView 绘制

void CD3DPointCloudView::OnDraw(CDC* /*pDC*/)
{
	CD3DPointCloudDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CD3DPointCloudView 打印

BOOL CD3DPointCloudView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CD3DPointCloudView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CD3DPointCloudView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CD3DPointCloudView 诊断

#ifdef _DEBUG
void CD3DPointCloudView::AssertValid() const
{
	CView::AssertValid();
}

void CD3DPointCloudView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CD3DPointCloudDoc* CD3DPointCloudView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CD3DPointCloudDoc)));
	return (CD3DPointCloudDoc*)m_pDocument;
}
#endif //_DEBUG


// CD3DPointCloudView 消息处理程序


void CD3DPointCloudView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(&rect);
	// Initialize Direct3D (e.g. acquire a IDirect3DDevice9 poniter).
	HRESULT hr = initD3D(GetSafeHwnd(),rect.right,rect.bottom,true,D3DDEVTYPE_HAL);
	if(FAILED(hr))
	{
		::MessageBox(0,L"initD3D() - Failed", 0,0);
		::PostQuitMessage(0);
	}
	// Setup the application.
	hr = setup(rect.right, rect.bottom);
	if(FAILED(hr))
	{
		::MessageBox(0,L"setup() - Failed", 0,0);
		::PostQuitMessage(0);
	}
}



void CD3DPointCloudView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(_device )
	{
		HRESULT hr = 0;
		// On a resize we must change the dimensions of the
		// back buffers to match the new window size.
		_d3dpp.BackBufferWidth = cx;
		_d3dpp.BackBufferHeight = cy;
		// We are about to call Reset, free any resources
		// that need to be freed prior to a Reset.
		hr = cleanup();
		if(FAILED(hr))
		{
			::MessageBox(0,L"destroy() - Failed", 0,0);
			::PostQuitMessage(0);
		}
		// Reset the flipping chain with the new window dimensions.
		// Note that all device states are reset to the default
		// after this call.
		hr = _device->Reset(&_d3dpp);
		if(FAILED(hr))
		{
			::MessageBox(0,L"Reset() - Failed", 0,0);
			::PostQuitMessage(0);
		}
		// Reinitialize resource and device states since we
		// Reset everything.
		hr = setup(cx, cy);
		if(FAILED(hr))
		{
			::MessageBox(0,L"setup() - Failed", 0,0);
			::PostQuitMessage(0);
		}
	}
}


BOOL CD3DPointCloudView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return FALSE;
	return CView::OnEraseBkgnd(pDC);
}


LRESULT CD3DPointCloudView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	// Pass all remaining windows messages to camera so it can respond to user input
	
	CWnd* pWnd = (CWnd*)(AfxGetApp()->m_pMainWnd);
	HWND hWnd = pWnd->GetSafeHwnd();
	g_Camera.HandleMessages( hWnd, message, wParam, lParam );

	
	return CView::WindowProc(message, wParam, lParam);
}
