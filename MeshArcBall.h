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
	HRESULT Create( LPCWSTR wszFileName,IDirect3DDevice9* pd3dDevice);
	void OnFrameMove() ;
	void Render();
	HRESULT HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	const D3DXMATRIX GetWorldMatrix() const ;
	
	void SetOrgin(D3DXVECTOR3 org)
	{
		model_orgin_ = org;
	}
	D3DXVECTOR3 GetOrgin()
	{
		return model_orgin_;
	}
	void SetPos(D3DXVECTOR3 p)
	{
		v3pos_ = p;
	}
	D3DXVECTOR3 GetPos()
	{
		return v3pos_;
	}
	void SetScale(float f)
	{
		model_scal_factor_ = f;

	}
	void SetRigidTransformation(D3DXMATRIX* mat)
	{
		rigidtransformation_matrix_ = *mat;
	}
	const CMeshArcBall& operator=( const CMeshArcBall& rhs );
   
	

protected:
	
	
	WCHAR   wszFile_[MAX_PATH];

	bool	frame_need_update_ ;
	float 	model_scal_factor_;		// Scale factor  of modle(+/-)
	D3DXVECTOR3  model_orgin_;
	D3DXVECTOR3  model_volume_;
	D3DXVECTOR3 v3min_;
	D3DXVECTOR3 v3max_;
	D3DXVECTOR3 v3pos_;

	
	D3DXMATRIX world_matrix_ ;			// World matrix of model
	ArcBall world_arcball_ ;			// Model arc ball
	ID3DXMesh* p_model_mesh_;

	D3DXMATRIX rigidtransformation_matrix_;

	IDirect3DDevice9* m_pd3dDevice; 
	 
};

