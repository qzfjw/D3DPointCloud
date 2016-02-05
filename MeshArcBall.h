#pragma once
#include "ArcBall.h"
class CMeshArcBall
{
public:
	CMeshArcBall(LPDIRECT3DDEVICE9 pd3dDevice);
	virtual ~CMeshArcBall(void);
	public:
	void Reset() ;
	void OnFrameMove() ;
	void Render();
	LRESULT HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	//void SetViewParams(const D3DXVECTOR3& eye_point, const D3DXVECTOR3& lookat_point, const D3DXVECTOR3& up_vector);
	//void SetProjParams(float field_of_view, float aspect_ratio, float near_plane, float far_plane) ;
	//void SetWindow(int window_width, int window_height, float arcball_radius = 1.0f) ;
	const D3DXMATRIX GetWorldMatrix() const ;

	

private:
	
	LPDIRECT3DDEVICE9		d3ddevice_;		// D3D9 Device
	char   szFile[MAX_PATH];

	bool	frame_need_update_ ;
	float 	model_scal_factor_;		// Scale factor  of modle(+/-)
	D3DXVECTOR3  model_orgin_;
	D3DXVECTOR3  model_volume_;
	
	D3DXMATRIX world_matrix_ ;			// World matrix of model
	ArcBall world_arcball_ ;			// Model arc ball
	ID3DXMesh* p_model_mesh_;
};

