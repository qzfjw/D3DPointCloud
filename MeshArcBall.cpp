#include "StdAfx.h"
#include "MeshArcBall.h"

CMeshArcBall::CMeshArcBall()
	:frame_need_update_(false),
	 model_scal_factor_(1.0f),
	 model_orgin_(0.0f,0.0f,0.0f),
	 model_volume_(0.0f,0.0f,0.0f),
	 p_model_mesh_(NULL)
{
	//d3ddevice_ = pd3dDevice;
	//Reset();
	//p_model_mesh_ = NULL;
}
CMeshArcBall::CMeshArcBall( const CMeshArcBall& old )
{
	p_model_mesh_ = NULL; 
	*this = old;
}
const CMeshArcBall& CMeshArcBall::operator=(const CMeshArcBall& rhs)
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
		
    SAFE_RELEASE(p_model_mesh_);
    if( (p_model_mesh_ = rhs.p_model_mesh_ ) != 0 ) p_model_mesh_->AddRef();
    return *this;

}

	
//--------------------------------------------------------------------------------------
HRESULT CMeshArcBall::Create( LPCWSTR wszFileName, IDirect3DDevice9* pd3dDevice )
{
	Reset();
	wcscpy_s( wszFile_, MAX_PATH, wszFileName);
	D3DXCreateTeapot(pd3dDevice, &p_model_mesh_, 0);
	return S_OK;

}

void CMeshArcBall::Reset() 
{
	/*frame_need_update_ = false ;
	Destroy();
	D3DXMatrixIdentity(&world_matrix_) ;
	world_arcball_.Reset();*/
}
void CMeshArcBall::Destroy()
{
	SAFE_RELEASE(p_model_mesh_);
}
CMeshArcBall::~CMeshArcBall(void)
{
	SAFE_RELEASE(p_model_mesh_);
	//d3ddevice_ = NULL;
	//SAFE_RELEASE(d3ddevice_);

}
void CMeshArcBall::OnFrameMove()
{
	//if(!frame_need_update_)
	//	return ;
	frame_need_update_ = false ;
	// Get the inverse of the view Arcball's rotation matrix
	D3DXMATRIX rotate_matrix = *world_arcball_.GetRotationMatrix();
	D3DXMATRIX scalmat,mt;
	D3DXMatrixTranslation(&mt,model_orgin_.x,model_orgin_.y,model_orgin_.z);
	D3DXMatrixScaling(&scalmat,model_scal_factor_,model_scal_factor_,model_scal_factor_);

	
	D3DXMatrixMultiply(&world_matrix_,&scalmat,&mt);
	D3DXMatrixMultiply(&world_matrix_,&rotate_matrix,&world_matrix_);


	
}
void CMeshArcBall::Render(LPDIRECT3DDEVICE9 pd3dDevice )
{
	 
	if(p_model_mesh_)
	{
		pd3dDevice->SetTransform(D3DTS_WORLD, &world_matrix_);
		p_model_mesh_->DrawSubset(0);
	}

}
const D3DXMATRIX CMeshArcBall::GetWorldMatrix() const
{
	return world_matrix_ ;
}
LRESULT CMeshArcBall::HandleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)    
	{
	case WM_LBUTTONDOWN:
		{
		SetCapture(hWnd) ;

		frame_need_update_ = true ;
		int mouse_x = (short)LOWORD(lParam) ;
		int mouse_y = (short)HIWORD(lParam) ;
		world_arcball_.OnBegin(mouse_x, mouse_y) ;
		}
		break;
	case WM_MOUSEMOVE:
		{
			frame_need_update_ = true ;
			int mouse_x = (short)LOWORD(lParam);
			int mouse_y = (short)HIWORD(lParam);
			world_arcball_.OnMove(mouse_x, mouse_y) ;
		}
		break;
	case WM_LBUTTONUP:
		{
			frame_need_update_ = true ;
			world_arcball_.OnEnd();
			ReleaseCapture();
		}
		break;
	case WM_KEYDOWN:
	{
		switch( wParam&0x7F )
		{
		case '[':
			{
				frame_need_update_ = true ;
				model_scal_factor_*=0.9f;
			}
			break;
		case ']':
			{
				frame_need_update_ = true ;
				model_scal_factor_*=1.1f;
			}
			break;
		default:
			break ;
		}
	}
	break ;


	}
	//// update model arc ball
	//if(uMsg == WM_LBUTTONDOWN)
	//{
	//	SetCapture(hWnd) ;

	//	frame_need_update_ = true ;
	//	int mouse_x = (short)LOWORD(lParam) ;
	//	int mouse_y = (short)HIWORD(lParam) ;
	//	world_arcball_.OnBegin(mouse_x, mouse_y) ;
	//}

	//// mouse move
	//if(uMsg == WM_MOUSEMOVE)
	//{
	//	frame_need_update_ = true ;
	//	int mouse_x = (short)LOWORD(lParam);
	//	int mouse_y = (short)HIWORD(lParam);
	//	world_arcball_.OnMove(mouse_x, mouse_y) ;
	//}

	//// right button up, terminate view arc ball rotation
	//if(uMsg == WM_LBUTTONUP)
	//{
	//	frame_need_update_ = true ;
	//	world_arcball_.OnEnd();
	//	ReleaseCapture() ;
	//}

	//// Mouse wheel, zoom in/out
	///*if(uMsg == WM_MOUSEWHEEL) 
	//{
	//	frame_need_update_ = true ;
	//	mouse_wheel_delta_ += (short)HIWORD(wParam);
	//}*/

	return TRUE ;
}
