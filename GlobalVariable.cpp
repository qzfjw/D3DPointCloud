#include "StdAfx.h"
#include "GlobalVariable.h"
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>

CGlobalVariable::CGlobalVariable(void)
{
	m_edtModelStep = 15;
	m_edtModel_X = 13.67;
	m_edtModel_Y = 0;
    m_edtModel_Z = 0;
	m_chkX = TRUE;
	m_chkY = TRUE;
	m_chkZ = FALSE;
	pd3dDevice = NULL;

	for( int i = 0; i < meshes_.GetSize(); ++i )
       meshes_[i].Destroy();
    meshes_.RemoveAll();
	nActiveMesh_ = -1; 
	MaximumIterations_ = 10;
}


CGlobalVariable::~CGlobalVariable(void)
{
	for( int i = 0; i < meshes_.GetSize(); ++i )
       meshes_[i].Destroy();
    meshes_.RemoveAll();
	nActiveMesh_ = -1;
}
bool CGlobalVariable::ComputeRigidTranformation(int from, int to, D3DXMATRIX* trans)
{
	 pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in (new pcl::PointCloud<pcl::PointXYZ>);
	 pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);
	 

	 // Fill in the CloudIn data
	 cloud_in->width    = meshes_[from].GetSize();
	 cloud_in->height   = 1;
	 cloud_in->is_dense = false;
	 cloud_in->points.resize (cloud_in->width * cloud_in->height);

	 CUSTOM_VERT_POS *pVB = meshes_[from].GetBuffer();
	 for (size_t i = 0; i < cloud_in->points.size (); ++i)
	 {
		 cloud_in->points[i].x = pVB->x;
		 cloud_in->points[i].y = pVB->y;
		 cloud_in->points[i].z = pVB->z;
		 pVB++;
	 }
  
	 // Fill in the CloudOut data
	 cloud_out->width    = meshes_[to].GetSize();
	 cloud_out->height   = 1;
	 cloud_out->is_dense = false;
	 cloud_out->points.resize (cloud_out->width * cloud_out->height);
	 pVB = meshes_[to].GetBuffer();
	 for (size_t i = 0; i < cloud_out->points.size (); ++i)
	 {
		 cloud_out->points[i].x = pVB->x;
		 cloud_out->points[i].y = pVB->y;
		 cloud_out->points[i].z = pVB->z;
		 pVB++;
	 }

	 pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
	 icp.setInputCloud(cloud_in);
	 icp.setInputTarget(cloud_out);
	 pcl::PointCloud<pcl::PointXYZ> Final;

	 
	 // Set the max correspondence distance to 5cm (e.g., correspondences with higher distances will be ignored)
	 icp.setMaxCorrespondenceDistance (0.05);//0.05
	 // Set the maximum number of iterations (criterion 1)
	icp.setMaximumIterations (MaximumIterations_);
	// Set the transformation epsilon (criterion 2)
	icp.setTransformationEpsilon (1e-6);
	// Set the euclidean distance difference epsilon (criterion 3)
	icp.setEuclideanFitnessEpsilon (1);//1
	// Perform the alignment
	icp.align(Final);
	
	 bool converged = icp.hasConverged();
	 //std::cout << "has converged:" << icp.hasConverged() << " score: " <<
     float score = icp.getFitnessScore();
     Eigen::Matrix4f  m4f = icp.getFinalTransformation();
	 for(int i=0;i < 4; i++)
		 for(int j=0; j < 4; j++)
			 (*trans)(i,j) = m4f(i,j);
  
	 cloud_in->clear();
	 cloud_out->clear();
	 Final.clear();
	return converged;

}