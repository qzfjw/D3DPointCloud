#include "StdAfx.h"
#include "D3DAppMain.h"

CD3DAppMain::CD3DAppMain(void)
    : d3d_(NULL),
	  d3ddevice_(NULL),
	  is_fullscreen_(false),
	  current_window_width_(0),
	  current_window_height_(0),
	  last_window_width_(0),
	  last_window_height_(0),
	  screen_width_(0),
	  screen_height_(0),
	  nActiveMesh_(0)
{
	camera = new Camera();
	teapot_ = NULL;
	meshes_.RemoveAll();
	//pMeshArcBall_ = NULL;
	
	

}

CD3DAppMain::~CD3DAppMain(void)
{
	SAFE_DELETE(camera);
	//SAFE_DELETE(pMeshArcBall_);
	//SAFE_RELEASE(teapot_);
		
    for( int i = 0; i < meshes_.GetSize(); ++i )
       meshes_[i].Destroy();
    meshes_.RemoveAll();
	// Release Direct3D Device
	SAFE_RELEASE(d3ddevice_);
	
	// Release Direct3D object
	SAFE_RELEASE(d3d_);
	

	
}
void CD3DAppMain::InitD3D9(HWND hWnd)
{
	this->hWnd_ = hWnd;

	// Create the D3D object.
	if( NULL == ( d3d_ = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		MessageBox(hWnd, L"Create Direct3D9 failed!", L"error!", 0) ;

	// Step 2: Check for hardware vp.

	//D3DCAPS9 caps;
	//d3d_->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	//int vp = 0;
	//if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	//	vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	//else
	//	vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	ZeroMemory( &d3dpp_, sizeof(d3dpp_) );

	// Get max display resolution and set it as back buffer size
	D3DDISPLAYMODE displayMode ;
	d3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode) ;

	
	// Initialize the max resolution width and height
	screen_width_  = displayMode.Width;
	screen_height_ = displayMode.Height;

	if(is_fullscreen_)
	{
		d3dpp_.Windowed = FALSE;
		d3dpp_.BackBufferWidth  = displayMode.Width;
		d3dpp_.BackBufferHeight = displayMode.Height;
	}
	else
	{
		d3dpp_.Windowed = TRUE;

		// Get current window size and set it as back buffer size
		RECT rect;
		GetClientRect(hWnd, &rect);
		d3dpp_.BackBufferWidth  = rect.right - rect.left;
		d3dpp_.BackBufferHeight = rect.bottom - rect.top;

		current_window_width_  = last_window_width_ = d3dpp_.BackBufferWidth;
		current_window_height_ = last_window_height_ = d3dpp_.BackBufferHeight;
	}
	
	// We didn't specify the back-buffer width and height, D3D will initialize it to the window width and height
	d3dpp_.hDeviceWindow = hWnd;
	d3dpp_.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp_.BackBufferCount           = 1;
	d3dpp_.BackBufferFormat			= D3DFMT_X8R8G8B8;
	d3dpp_.EnableAutoDepthStencil	= TRUE ;
	d3dpp_.AutoDepthStencilFormat	= D3DFMT_D24S8;//D3DFMT_D16 ;
	
	d3dpp_.Flags                      = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER ;//0;
	d3dpp_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp_.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
	// Create the D3DDevice
	HRESULT hr = d3d_->CreateDevice(D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp_, &d3ddevice_ );
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"Create Direct3D9 device failed!", L"error!", 0) ;
	}

	// Setup view matrix
	D3DXVECTOR3 vecEye(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 vecAt (0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vecUp (0.0f, 1.0f, 0.0f) ;
	camera->SetViewParams(vecEye, vecAt, vecUp);
	
	// Setup projection matrix
	float aspectRatio = (float)d3dpp_.BackBufferWidth / (float)d3dpp_.BackBufferHeight ;
	camera->SetProjParams(D3DX_PI /4, aspectRatio, 1.0f,1000.0f) ;

	ResetDevice();

	
	/*CMeshArcBall* pNewMesh;
	for( int i = 0; i < 10; ++i )
	{
		pNewMesh = new CMeshArcBall();
		pNewMesh->Create(L"xx0",d3ddevice_);
		pNewMesh->SetOrgin(D3DXVECTOR3(2.0f*i-10,0.0f,0.0f));
		meshes_.Add(*pNewMesh);
		SAFE_DELETE(pNewMesh);
	}
	nActiveMesh_ = 6;*/
	CPlyMeshArcBall* pNewMesh;

	pNewMesh = new CPlyMeshArcBall();
	pNewMesh->Create(L"media\\LUNGU5.ply",d3ddevice_);
	pNewMesh->SetPos(D3DXVECTOR3(0.0f,0.0f,-422.0f));
	meshes_.Add(*pNewMesh);

	SAFE_DELETE(pNewMesh);

	pNewMesh = new CPlyMeshArcBall();
	pNewMesh->Create(L"media\\LUNGU6.ply",d3ddevice_);
	pNewMesh->SetPos(D3DXVECTOR3(-20.0f,0.0f,-422.0f));
	meshes_.Add(*pNewMesh);
	SAFE_DELETE(pNewMesh);
	
	nActiveMesh_ =0;
}

void CD3DAppMain::FrameRender(float fTime,float fElapsedTime)
{
	// Update frame
	FrameMove() ;

	SetupMatrix();

	SetupLight();

	// Clear the back buffer to a black color
	d3ddevice_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x4F94CD, 1.0f, 0);
	d3ddevice_->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	

	
	if( SUCCEEDED(d3ddevice_->BeginScene()))
	{
		
		
		//draw all unit cubes to build the Rubik cube
		// Restore world matrix since the Draw function in class Cube has set the world matrix for each cube
		D3DXMATRIX matWorld = camera->GetWorldMatrix() ;
		d3ddevice_->SetTransform(D3DTS_WORLD, &matWorld) ;
		//if(teapot_)
		//	teapot_->DrawSubset(0);
		//pMeshArcBall_->Render();

		for( int i = 0; i < meshes_.GetSize(); ++i )
		{
			
			 meshes_[i].Render(d3ddevice_);
			 //CMeshArcBall temp = meshes_[i];
			 //temp.Render(d3ddevice_);
		}

		d3ddevice_->EndScene();
	}

	// Present the back buffer contents to the display
	HRESULT hr = d3ddevice_->Present(NULL, NULL, NULL, NULL);

	// Render failed, try to reset device
	if(FAILED(hr))
	{
		ResetDevice() ;
	}
}
void CD3DAppMain::SetupMatrix()
{
	// View matrix
	D3DXMATRIX matView = camera->GetViewMatrix() ;
	d3ddevice_->SetTransform(D3DTS_VIEW, &matView) ;

	// Projection matrix
	D3DXMATRIX matProj = camera->GetProjMatrix() ;
	d3ddevice_->SetTransform(D3DTS_PROJECTION, &matProj) ;
}
void CD3DAppMain::SetupLight()
{
	// Create light
	D3DLIGHT9 pointLight ;

	// Light color
	D3DXCOLOR color = D3DCOLOR_XRGB(0, 0, 255) ;

	// The light position is always same as the camera eye point
	// so no matter how you rotate the camera, the cube will keep the same brightness
	 D3DXVECTOR3 position = camera->GetEyePoint() ;

	// Light type, we use point light here
	pointLight.Type			= D3DLIGHT_POINT ;

	// Light attributes
	pointLight.Ambient		= color * 0.6f;
	pointLight.Diffuse		= color;
	pointLight.Specular		= color * 0.6f;
	pointLight.Position		= position;
	pointLight.Range		= 10320.0f;
	pointLight.Falloff		= 1.0f;
	pointLight.Attenuation0	= 1.0f;
	pointLight.Attenuation1	= 0.0f;
	pointLight.Attenuation2	= 0.0f;

	// Set material
	D3DMATERIAL9 material ;
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0) ;
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0);
	material.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0);
	material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	material.Power = 2.0f ;
	d3ddevice_->SetMaterial(&material) ;

	// Enable light
	d3ddevice_->SetLight(0, &pointLight) ;		
	d3ddevice_->LightEnable(0, true) ;		
}

void CD3DAppMain::ResizeD3DScene(int width, int height)
{
	if (height == 0)				// Prevent A Divide By Zero By
		height = 1;					// Making Height Equal One

	// Compute aspect ratio
	float fAspectRatio = width / (FLOAT)height;

	// Setup Projection matrix
	camera->SetProjParams(D3DX_PI / 4, fAspectRatio, 1.0f, 1000.0f);

	camera->SetWindow(width, height);
}
HRESULT CD3DAppMain::ResetDevice()
{
	/*for( int i = 0; i < meshes_.GetSize(); ++i )
	{
		meshes_[i].Destroy();
	}
	meshes_.RemoveAll();*/
	// Check device state
	if(d3ddevice_ == NULL)
		return S_OK;
	HRESULT hr = d3ddevice_->TestCooperativeLevel() ;
	
	// Device can be reset now
	if (SUCCEEDED(hr) || hr == D3DERR_DEVICENOTRESET)
	{
		// Reset device
		HRESULT hr = d3ddevice_->Reset(&d3dpp_);
		if (SUCCEEDED(hr))
		{
			ResizeD3DScene(d3dpp_.BackBufferWidth, d3dpp_.BackBufferHeight) ;
		}
		else // Reset device failed, show error box
		{
			const WCHAR* errorString = DXGetErrorString(hr) ;
			DXTRACE_ERR_MSGBOX(errorString, hr) ;
		}
	}
	// Device is still in lost state, wait
	else if (hr == D3DERR_DEVICELOST)
	{
		Sleep(25) ;
	}
	else // Other error, Show error box
	{
		const WCHAR* errorString = DXGetErrorString(hr) ;
		DXTRACE_ERR_MSGBOX(errorString, hr) ;
	}

	//if(teapot_==NULL)
	//	D3DXCreateTeapot(d3ddevice_, &teapot_, 0);
	/*CMeshArcBall* pNewMesh;
	for( int i = 0; i < 10; ++i )
	{
		pNewMesh = new CMeshArcBall();
		pNewMesh->Create(L"xx0",d3ddevice_);
		pNewMesh->SetOrgin(D3DXVECTOR3(2.0f*i-10,0.0f,0.0f));
		meshes_.Add(*pNewMesh);
		SAFE_DELETE(pNewMesh);
	}
	nActiveMesh_ = 6;*/
	return hr ;
}
void CD3DAppMain::FrameMove()
{
	camera->OnFrameMove() ;
	//pMeshArcBall_->OnFrameMove();
	for( int i = 0; i < meshes_.GetSize(); ++i )
	{
		meshes_[i].OnFrameMove();
	}
}
// Calculate the picking ray and transform it to model space 
// x and y are the screen coordinates when left button down
Ray CD3DAppMain::CalculatePickingRay(int x, int y)
{
	float px = 0.0f;
	float py = 0.0f;

	// Get viewport
	D3DVIEWPORT9 vp;
	d3ddevice_->GetViewport(&vp);

	// Get Projection matrix
	D3DXMATRIX proj;
	d3ddevice_->GetTransform(D3DTS_PROJECTION, &proj);

	px = ((( 2.0f*x) / vp.Width)  - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	Ray ray;
	ray.origin    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ray.direction = D3DXVECTOR3(px, py, 1.0f); 

	// Get view matrix
	D3DXMATRIX view;
	d3ddevice_->GetTransform(D3DTS_VIEW, &view);

	// Get world matrix
	D3DXMATRIX world;
	d3ddevice_->GetTransform(D3DTS_WORLD, &world);

	// Concatinate them in to single matrix
	D3DXMATRIX WorldView = world * view;

	// inverse it
	D3DXMATRIX worldviewInverse;
	D3DXMatrixInverse(&worldviewInverse, 0, &WorldView);


	// Transform the ray to model space
	D3DXVec3TransformCoord(&ray.origin, &ray.origin, &worldviewInverse) ;
	D3DXVec3TransformNormal(&ray.direction, &ray.direction, &worldviewInverse) ;

	// Normalize the direction
	D3DXVec3Normalize(&ray.direction, &ray.direction) ;

	return ray;
}
// Transform the screen point to vector in model space
D3DXVECTOR3 CD3DAppMain::ScreenToVector3(int x, int y)
{
	D3DXVECTOR3 vector3 ;

	// Get viewport
	D3DVIEWPORT9 vp;
	d3ddevice_->GetViewport(&vp);

	// Get Projection matrix
	D3DXMATRIX proj;
	d3ddevice_->GetTransform(D3DTS_PROJECTION, &proj);

	vector3.x = ((( 2.0f*x) / vp.Width)  - 1.0f) / proj(0, 0);
	vector3.y = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);
	vector3.z = 1.0f ;

	// Get view matrix
	D3DXMATRIX view;
	d3ddevice_->GetTransform(D3DTS_VIEW, &view);

	// Get world matrix
	D3DXMATRIX world;
	d3ddevice_->GetTransform(D3DTS_WORLD, &world);

	// Concatinate them in to single matrix
	D3DXMATRIX WorldView = world * view;

	// inverse it
	D3DXMATRIX worldviewInverse;
	D3DXMatrixInverse(&worldviewInverse, 0, &WorldView);

	D3DXVec3TransformCoord(&vector3, &vector3, &worldviewInverse) ;

	D3DXVec3Normalize(&vector3, &vector3) ;

	return vector3 ;
}

LRESULT CD3DAppMain::HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)    
	{
		case WM_LBUTTONDOWN:
			{	
				// Set current window to capture mouse event, so even if the mouse was release outside the window
				// the message still can be correctly processed.
				SetCapture(hWnd) ;
				int iMouseX = ( short )LOWORD( lParam );
				int iMouseY = ( short )HIWORD( lParam );
				//OnLeftButtonDown(iMouseX, iMouseY);
			}
			break ;
		case WM_LBUTTONUP:
			{
				//OnLeftButtonUp();
				ReleaseCapture();
			}
			break ;

		case WM_MOUSEMOVE:
			{
				int iMouseX = ( short )LOWORD( lParam );
				int iMouseY = ( short )HIWORD( lParam );
				//OnMouseMove(iMouseX, iMouseY) ;
			}
			break ;
		case WM_KEYDOWN:
			{
				/*switch( wParam )
				{
					case 'F':
						ToggleFullScreen() ;
						break;
					case VK_ESCAPE:
						PostQuitMessage(0);
						break ;
					default:
						break ;
				}*/
			}
			break ;

		case WM_SIZE: // why not use WM_EXITSIZEMOVE?
		{
			current_window_width_ = ( short )LOWORD( lParam );
			current_window_height_ = ( short )HIWORD( lParam );
			d3dpp_.BackBufferWidth = current_window_width_;
			d3dpp_.BackBufferHeight = current_window_height_;
			ResetDevice();
			//if (wParam == SIZE_MAXIMIZED)
			//{
			//	// Get current window size
			//	current_window_width_ = ( short )LOWORD( lParam );
			//	current_window_height_ = ( short )HIWORD( lParam );

			//	if(current_window_width_ != last_window_width_ || current_window_height_ != last_window_height_)
			//	{
			//		d3dpp_.BackBufferWidth = current_window_width_;
			//		d3dpp_.BackBufferHeight = current_window_height_;
			//		ResetDevice();
			//		last_window_width_ = current_window_width_ ;
			//		last_window_height_ = current_window_height_ ;
			//	}
			//}
			//else if (wParam == SIZE_RESTORED)
			//{
			//	
			//	// Maximized -> Full Screen
			//	if (is_fullscreen_)
			//	{
			//		// Update back buffer to desktop resolution
			//		d3dpp_.BackBufferWidth  = screen_width_;  
			//		d3dpp_.BackBufferHeight = screen_height_;

			//		// Reset device
			//		ResetDevice();
			//	}
			//	else
			//	{
			//		// Get current window size
			//		current_window_width_ = ( short )LOWORD( lParam );
			//		current_window_height_ = ( short )HIWORD( lParam );

			//		// Reset device
			//		d3dpp_.BackBufferWidth = current_window_width_;
			//		d3dpp_.BackBufferHeight = current_window_height_;
			//		ResetDevice();
			//		last_window_width_ = current_window_width_ ;
			//		last_window_height_ = current_window_height_ ;
			//	}
			//}
		}
		break ;
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage (0) ;
			return 0 ;    
	}

	HRESULT hr = camera->HandleMessages(hWnd, uMsg, wParam, lParam);
	if( meshes_.GetSize() > 0 )
        hr = meshes_[nActiveMesh_].HandleMessages( hWnd, uMsg, wParam, lParam);
	 //hr = meshes_[1].HandleMessages( hWnd, uMsg, wParam, lParam);
	//return pMeshArcBall_->HandleMessages(hWnd, uMsg, wParam, lParam);
	 return hr;
}

// Switch from window mode and full-screen mode
void CD3DAppMain::ToggleFullScreen()
{
	wp_.length = sizeof(WINDOWPLACEMENT) ;

	// Window -> Full-Screen
	if(!is_fullscreen_)
	{
		is_fullscreen_ = true;

		// Get and save window placement
		GetWindowPlacement(hWnd_, &wp_) ;

		// Update back buffer to desktop resolution
		last_window_width_ = current_window_width_;
		last_window_height_ = current_window_height_;

		d3dpp_.Windowed = !is_fullscreen_;
		d3dpp_.BackBufferWidth  = screen_width_;  
		d3dpp_.BackBufferHeight = screen_height_;
		//d3dpp_.SwapEffect=D3DSWAPEFFECT_FLIP; 
		//d3dpp_.BackBufferCount=2;
	}
	else // Full-Screen -> Window
	{
		is_fullscreen_ = false;
		d3dpp_.Windowed = !is_fullscreen_;

		// Update back buffer size
		current_window_width_  = last_window_width_;  
		current_window_height_ = last_window_height_;
		
		// When swith from Full-Screen mode to window mode and the wp structe was not initialized
		// The window position and size was unavailable, this will happened when the app start as full-screen mode
		// give a defaul value of it.
		SetWindowPlacement(hWnd_, &wp_) ;
	}

	// Display mode changed, we need to reset device
	ResetDevice() ;
}
