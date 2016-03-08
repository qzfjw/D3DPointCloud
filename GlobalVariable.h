#pragma once
#include "PlyMeshArcBall.h"
class CGlobalVariable
{
public:
	CGlobalVariable(void);
	virtual ~CGlobalVariable(void);
public:
	bool ComputeRigidTranformation(int from, int to, D3DXMATRIX* trans);
	void CenterAlign(int from, int to);

	
public:
	int nActiveMesh_;
	CGrowableArray <CPlyMeshArcBall> meshes_;           // List of meshes being rendered
	// 增加或减少的量
	float m_edtModelStep;
	// X坐标值
	float m_edtModel_X;
	// Y坐标值
	float m_edtModel_Y;
	// Z坐标值
	float m_edtModel_Z;
	// 是否选中X轴
	BOOL m_chkX;
	// 是否选中Y轴
	BOOL m_chkY;
	// 是否选中Z轴
	BOOL m_chkZ;
	//ICP最大迭代次数
	int MaximumIterations_;

	IDirect3DDevice9*pd3dDevice;

	
};

