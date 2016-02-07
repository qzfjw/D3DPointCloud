#pragma once
#include "ArcBall.h"


class CMeshArcBall
{
public:
	CMeshArcBall();
	CMeshArcBall( const CMeshArcBall& old );
	virtual ~CMeshArcBall(void);
	void Destroy();
	public:
	void Reset() ;
	HRESULT Create( LPCWSTR wszFileName, IDirect3DDevice9* pd3dDevice );
	void OnFrameMove() ;
	void Render(LPDIRECT3DDEVICE9 pd3dDevice );
	HRESULT HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	//void SetViewParams(const D3DXVECTOR3& eye_point, const D3DXVECTOR3& lookat_point, const D3DXVECTOR3& up_vector);
	//void SetProjParams(float field_of_view, float aspect_ratio, float near_plane, float far_plane) ;
	//void SetWindow(int window_width, int window_height, float arcball_radius = 1.0f) ;
	const D3DXMATRIX GetWorldMatrix() const ;
	void SetOrgin(D3DXVECTOR3 org)
	{
		model_orgin_ = org;
	}
	const CMeshArcBall& operator=( const CMeshArcBall& rhs );
   
	

private:
	
	//LPDIRECT3DDEVICE9		d3ddevice_;		// D3D9 Device
	WCHAR   wszFile_[MAX_PATH];

	bool	frame_need_update_ ;
	float 	model_scal_factor_;		// Scale factor  of modle(+/-)
	D3DXVECTOR3  model_orgin_;
	D3DXVECTOR3  model_volume_;
	
	D3DXMATRIX world_matrix_ ;			// World matrix of model
	ArcBall world_arcball_ ;			// Model arc ball
	ID3DXMesh* p_model_mesh_;
};

