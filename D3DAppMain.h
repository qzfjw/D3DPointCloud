#pragma once
#include <d3dx9.h>
#include <DxErr.h>

#include "Camera.h"
#include "Math.h"
#include "MeshArcBall.h"


class CD3DAppMain
{
public:
	CD3DAppMain(void);
	virtual ~CD3DAppMain(void);
public:
	void InitD3D9(HWND hWnd);
	void FrameRender(float fTime,float fElapsedTime);
	//LPDIRECT3DTEXTURE9 CreateTexture(int texWidth, int texHeight, D3DCOLOR color);
	//LPDIRECT3DTEXTURE9 CreateInnerTexture(int texWidth, int texHeight, D3DCOLOR color);
	void ResizeD3DScene(int width, int height);
	HRESULT ResetDevice();
	void ToggleFullScreen();
	void SetupLight();
	void SetupMatrix();
	void FrameMove();
	Ray CalculatePickingRay(int x, int y);
	D3DXVECTOR3 ScreenToVector3(int x, int y);
	LRESULT HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
private:
	LPDIRECT3D9				d3d_;			// Direct3D object
	LPDIRECT3DDEVICE9		d3ddevice_;		// D3D9 Device
	D3DPRESENT_PARAMETERS	d3dpp_;			// D3D presentation parameters

	HWND hWnd_;				// Handle of game window
	WINDOWPLACEMENT wp_ ;		// Window position and size

	// Last window size
	int last_window_width_;
	int last_window_height_;
	// Current window size, used in resizing window 
	int current_window_width_;
	int current_window_height_;

	int screen_width_;	// The maximum resolution width
	int screen_height_;	// The maximum resolution height
	bool is_fullscreen_;	// Is Game in Full-Screen mode?

private:
	Camera*					camera;			// Model-view camera
	
private:
	ID3DXMesh* teapot_;
	CMeshArcBall* pMeshArcBall_;
	
};

