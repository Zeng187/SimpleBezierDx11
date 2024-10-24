#pragma once


// Copyright (c) Microsoft
// All rights reserved
//
// Pixar U.S. Patent Nos. 6,037,949, 6,222,553, 6,300,960, 6,489,960, and U.S. RE 41,677E
//
// Licensed under the Ms-PL (the "License"); you may not use this file except in compliance with the License.  You may obtain a copy of the License at http://opensource.org/licenses/ms-pl
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//
// See the Ms-PL License for specific language governing permissions and limitations under the License.

#pragma once

#include <vector>
#include <set>

#include "DXUT.h"
#include "DXUTcamera.h"
#include "SDKmisc.h"

//! Base class that takes care for all settings of partial cases (note that in the paper those patches are called transition patches)
//! Each type of partial case is then derived from this base classed and must implement the required methods
class PartialCase
{
public:
	PartialCase(void);
	~PartialCase(void);

	//! Virtual method that crease all shaders; child classes take care for specific patchh setups
	virtual HRESULT CreateShaders(ID3D11Device* pd3dDevice) = 0;

	void Destroy();

	//! Creates the index buffers that are required for the draw calls

	//! Renders all regular patches of this type of partial case
	void DrawIndexedRegular(ID3D11DeviceContext* pd3dImmediateContext, UINT primitive_count);

protected:
	//! Shaders are created for all five child classes; but only once per child class even if there are more instances of each child class 
	HRESULT CreateShadersGeneral(ID3D11Device* pd3dDevice, std::vector<D3D_SHADER_MACRO*>& macros);
	virtual void DestroyShaders() = 0;



	UINT					m_NumShaders;
	UINT					m_NumSubPatch;

	//! Shaders for partial cases
	ID3D11HullShader** m_pHSPartialsRegularBSpline;
	ID3D11DomainShader** m_pDSPartialsRegularBSpline;



};


//DIFFERENT IMPLEMENTATION OF TRANSITION PATCHH CASES BELOW

class PartialCase0 :
	public PartialCase
{
public:
	PartialCase0(void);
	~PartialCase0(void);

	virtual HRESULT CreateShaders(ID3D11Device* pd3dDevice);
	virtual void DestroyShaders();
private:
	static bool s_bShadersAreCreated;

	static ID3D11HullShader** stg_pHSPartialsRegularBSpline;
	static ID3D11DomainShader** stg_pDSPartialsRegularBSpline;
};


class PartialCase1 :
	public PartialCase
{
public:
	PartialCase1(void);
	~PartialCase1(void);

	virtual HRESULT CreateShaders(ID3D11Device* pd3dDevice);
	virtual void DestroyShaders();
private:
	static bool s_bShadersAreCreated;

	static ID3D11HullShader** stg_pHSPartialsRegularBSpline;
	static ID3D11DomainShader** stg_pDSPartialsRegularBSpline;
};

class PartialCase2 :
	public PartialCase
{
public:
	PartialCase2(void);
	~PartialCase2(void);

	virtual HRESULT CreateShaders(ID3D11Device* pd3dDevice);
	virtual void DestroyShaders();
private:
	static bool s_bShadersAreCreated;

	static ID3D11HullShader** stg_pHSPartialsRegularBSpline;
	static ID3D11DomainShader** stg_pDSPartialsRegularBSpline;
};

class PartialCase3 :
	public PartialCase
{
public:
	PartialCase3(void);
	~PartialCase3(void);

	virtual HRESULT CreateShaders(ID3D11Device* pd3dDevice);
	virtual void DestroyShaders();
private:
	static bool s_bShadersAreCreated;

	static ID3D11HullShader** stg_pHSPartialsRegularBSpline;
	static ID3D11DomainShader** stg_pDSPartialsRegularBSpline;
};


class PartialCase4 :
	public PartialCase
{
public:
	PartialCase4(void);
	~PartialCase4(void);

	virtual HRESULT CreateShaders(ID3D11Device* pd3dDevice);
	virtual void DestroyShaders();
private:
	static bool s_bShadersAreCreated;

	static ID3D11HullShader** stg_pHSPartialsRegularBSpline;
	static ID3D11DomainShader** stg_pDSPartialsRegularBSpline;
};



