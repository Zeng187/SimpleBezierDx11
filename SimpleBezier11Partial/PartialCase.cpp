#include"DXUT.h"
#include "PartialCase.h"

extern HRESULT CompileShaderFromFile(WCHAR* szFileName, D3D_SHADER_MACRO* pDefines, LPCSTR szEntryPoint,
    LPCSTR szShaderModel, ID3DBlob** ppBlobOut);


PartialCase::PartialCase(void)
{


	m_pHSPartialsRegularBSpline = NULL;
	m_pDSPartialsRegularBSpline = NULL;

	m_NumShaders = 1;
	m_NumSubPatch = 1;

}

PartialCase::~PartialCase(void)
{
}

void PartialCase::Destroy()
{

	DestroyShaders();
}


void PartialCase::DrawIndexedRegular(ID3D11DeviceContext* pd3dImmediateContext, UINT primitive_count)
{
	for (UINT i = 0; i < m_NumShaders; i++) {

		pd3dImmediateContext->HSSetShader(m_pHSPartialsRegularBSpline[i], 0, 0);

		pd3dImmediateContext->DSSetShader(m_pDSPartialsRegularBSpline[i], 0, 0);

		//pd3dImmediateContext->DrawIndexed(primitive_count, 0, 0);
		pd3dImmediateContext->Draw(primitive_count, 0);


	}
}


HRESULT PartialCase::CreateShadersGeneral(ID3D11Device* pd3dDevice, std::vector<D3D_SHADER_MACRO*>& macros)
{
	HRESULT hr = S_OK;

	m_pHSPartialsRegularBSpline = new ID3D11HullShader * [m_NumShaders];
	m_pDSPartialsRegularBSpline = new ID3D11DomainShader * [m_NumShaders];

	ID3DBlob* pBlobHS = NULL;
	ID3DBlob* pBlobDS = NULL;

	for (UINT i = 0; i < m_NumShaders; i++) {

		// Compile shaders
		ID3DBlob* pBlobHSInt = NULL;
		ID3DBlob* pBlobDS = NULL;


		V_RETURN(CompileShaderFromFile(L"SimpleBezierPartial.hlsl", macros[i], "BezierHS", "hs_5_0", &pBlobHSInt));
		V_RETURN(CompileShaderFromFile(L"SimpleBezierPartial.hlsl", macros[i], "BezierDS", "ds_5_0", &pBlobDS));

		V_RETURN(pd3dDevice->CreateHullShader(pBlobHSInt->GetBufferPointer(), pBlobHSInt->GetBufferSize(), NULL, &m_pHSPartialsRegularBSpline[i]));
		V_RETURN(pd3dDevice->CreateDomainShader(pBlobDS->GetBufferPointer(), pBlobDS->GetBufferSize(), NULL, &m_pDSPartialsRegularBSpline[i]));


	}

	return hr;
}


//static definitions
bool PartialCase0::s_bShadersAreCreated = false;
ID3D11HullShader** PartialCase0::stg_pHSPartialsRegularBSpline = NULL;
ID3D11DomainShader** PartialCase0::stg_pDSPartialsRegularBSpline = NULL;


PartialCase0::PartialCase0(void)
{
}

PartialCase0::~PartialCase0(void)
{
}

HRESULT PartialCase0::CreateShaders(ID3D11Device* pd3dDevice)
{
	HRESULT hr = S_OK;

	m_NumShaders = 1;
	m_NumSubPatch = 3;

	if (!s_bShadersAreCreated) {

		std::vector<D3D_SHADER_MACRO*> macros;
		D3D_SHADER_MACRO partial0_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "TRI_DOMAIN", "1"} ,{ "CASE00", "1" } ,{0} };
		macros.push_back(partial0_macros);

		V_RETURN(CreateShadersGeneral(pd3dDevice, macros));
		s_bShadersAreCreated = true;

		stg_pHSPartialsRegularBSpline = m_pHSPartialsRegularBSpline;
		stg_pDSPartialsRegularBSpline = m_pDSPartialsRegularBSpline;
	}
	else {
		m_pDSPartialsRegularBSpline = stg_pDSPartialsRegularBSpline;
		m_pHSPartialsRegularBSpline = stg_pHSPartialsRegularBSpline;
	}

	return hr;

}


PartialCase1::PartialCase1(void)
{
}

PartialCase1::~PartialCase1(void)
{
}

//static definitions
bool PartialCase1::s_bShadersAreCreated = false;
ID3D11HullShader** PartialCase1::stg_pHSPartialsRegularBSpline = NULL;
ID3D11DomainShader** PartialCase1::stg_pDSPartialsRegularBSpline = NULL;

HRESULT PartialCase1::CreateShaders(ID3D11Device* pd3dDevice)
{
	HRESULT hr = S_OK;

	m_NumShaders = 1;
	m_NumSubPatch = 4;

	if (!s_bShadersAreCreated) {

		std::vector<D3D_SHADER_MACRO*> macros;
		D3D_SHADER_MACRO partial0_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "TRI_DOMAIN", "1"} ,{ "CASE10", "1" } ,{0} };
		macros.push_back(partial0_macros);

		V_RETURN(CreateShadersGeneral(pd3dDevice, macros));
		s_bShadersAreCreated = true;

		stg_pHSPartialsRegularBSpline = m_pHSPartialsRegularBSpline;
		stg_pDSPartialsRegularBSpline = m_pDSPartialsRegularBSpline;
	}
	else {
		m_pDSPartialsRegularBSpline = stg_pDSPartialsRegularBSpline;
		m_pHSPartialsRegularBSpline = stg_pHSPartialsRegularBSpline;
	}

	return hr;

}



void PartialCase0::DestroyShaders()
{
	if (!s_bShadersAreCreated)	return;

	for (UINT i = 0; i < m_NumShaders; i++) {
		if (stg_pHSPartialsRegularBSpline)				SAFE_RELEASE(stg_pHSPartialsRegularBSpline[i]);
		if (stg_pDSPartialsRegularBSpline)				SAFE_RELEASE(stg_pDSPartialsRegularBSpline[i]);
	}

	SAFE_DELETE_ARRAY(stg_pHSPartialsRegularBSpline);
	SAFE_DELETE_ARRAY(stg_pDSPartialsRegularBSpline);

	s_bShadersAreCreated = false;
}


void PartialCase1::DestroyShaders()
{
	if (!s_bShadersAreCreated)	return;

	for (UINT i = 0; i < m_NumShaders; i++) {
		if (stg_pHSPartialsRegularBSpline)				SAFE_RELEASE(stg_pHSPartialsRegularBSpline[i]);
		if (stg_pDSPartialsRegularBSpline)				SAFE_RELEASE(stg_pDSPartialsRegularBSpline[i]);
	}

	SAFE_DELETE_ARRAY(stg_pHSPartialsRegularBSpline);
	SAFE_DELETE_ARRAY(stg_pDSPartialsRegularBSpline);

	s_bShadersAreCreated = false;
}



//static definitions
bool PartialCase2::s_bShadersAreCreated = false;
ID3D11HullShader** PartialCase2::stg_pHSPartialsRegularBSpline = NULL;
ID3D11DomainShader** PartialCase2::stg_pDSPartialsRegularBSpline = NULL;


PartialCase2::PartialCase2(void)
{
}

PartialCase2::~PartialCase2(void)
{
}

HRESULT PartialCase2::CreateShaders(ID3D11Device* pd3dDevice)
{
	HRESULT hr = S_OK;

	m_NumShaders = 4;
	m_NumSubPatch = 1;

	if (!s_bShadersAreCreated) {

		std::vector<D3D_SHADER_MACRO*> macros;
		D3D_SHADER_MACRO partial0_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "QUAD_DOMAIN", "1"} ,{ "CASE20", "1" } ,{0} }; macros.push_back(partial0_macros);
		D3D_SHADER_MACRO partial1_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "TRI_DOMAIN", "1"} ,{ "CASE21", "1" } ,{0} }; macros.push_back(partial1_macros);
		D3D_SHADER_MACRO partial2_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "TRI_DOMAIN", "1"} ,{ "CASE22", "1" } ,{0} }; macros.push_back(partial2_macros);
		D3D_SHADER_MACRO partial3_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "TRI_DOMAIN", "1"} ,{ "CASE23", "1" } ,{0} };macros.push_back(partial3_macros);

		V_RETURN(CreateShadersGeneral(pd3dDevice, macros));
		s_bShadersAreCreated = true;

		stg_pHSPartialsRegularBSpline = m_pHSPartialsRegularBSpline;
		stg_pDSPartialsRegularBSpline = m_pDSPartialsRegularBSpline;
	}
	else {
		m_pDSPartialsRegularBSpline = stg_pDSPartialsRegularBSpline;
		m_pHSPartialsRegularBSpline = stg_pHSPartialsRegularBSpline;
	}

	return hr;

}

void PartialCase2::DestroyShaders()
{
	if (!s_bShadersAreCreated)	return;

	for (UINT i = 0; i < m_NumShaders; i++) {
		if (stg_pHSPartialsRegularBSpline)				SAFE_RELEASE(stg_pHSPartialsRegularBSpline[i]);
		if (stg_pDSPartialsRegularBSpline)				SAFE_RELEASE(stg_pDSPartialsRegularBSpline[i]);
	}

	SAFE_DELETE_ARRAY(stg_pHSPartialsRegularBSpline);
	SAFE_DELETE_ARRAY(stg_pDSPartialsRegularBSpline);

	s_bShadersAreCreated = false;
}


//static definitions
bool PartialCase3::s_bShadersAreCreated = false;
ID3D11HullShader** PartialCase3::stg_pHSPartialsRegularBSpline = NULL;
ID3D11DomainShader** PartialCase3::stg_pDSPartialsRegularBSpline = NULL;


PartialCase3::PartialCase3(void)
{
}

PartialCase3::~PartialCase3(void)
{
}

HRESULT PartialCase3::CreateShaders(ID3D11Device* pd3dDevice)
{
	HRESULT hr = S_OK;

	m_NumShaders = 1;
	m_NumSubPatch = 4;

	if (!s_bShadersAreCreated) {

		std::vector<D3D_SHADER_MACRO*> macros;
		D3D_SHADER_MACRO partial0_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "QUAD_DOMAIN", "1"} ,{ "CASE30", "1" } ,{0} }; macros.push_back(partial0_macros);

		V_RETURN(CreateShadersGeneral(pd3dDevice, macros));
		s_bShadersAreCreated = true;

		stg_pHSPartialsRegularBSpline = m_pHSPartialsRegularBSpline;
		stg_pDSPartialsRegularBSpline = m_pDSPartialsRegularBSpline;
	}
	else {
		m_pDSPartialsRegularBSpline = stg_pDSPartialsRegularBSpline;
		m_pHSPartialsRegularBSpline = stg_pHSPartialsRegularBSpline;
	}

	return hr;

}

void PartialCase3::DestroyShaders()
{
	if (!s_bShadersAreCreated)	return;

	for (UINT i = 0; i < m_NumShaders; i++) {
		if (stg_pHSPartialsRegularBSpline)				SAFE_RELEASE(stg_pHSPartialsRegularBSpline[i]);
		if (stg_pDSPartialsRegularBSpline)				SAFE_RELEASE(stg_pDSPartialsRegularBSpline[i]);
	}

	SAFE_DELETE_ARRAY(stg_pHSPartialsRegularBSpline);
	SAFE_DELETE_ARRAY(stg_pDSPartialsRegularBSpline);

	s_bShadersAreCreated = false;
}


//static definitions
bool PartialCase4::s_bShadersAreCreated = false;
ID3D11HullShader** PartialCase4::stg_pHSPartialsRegularBSpline = NULL;
ID3D11DomainShader** PartialCase4::stg_pDSPartialsRegularBSpline = NULL;


PartialCase4::PartialCase4(void)
{
}

PartialCase4::~PartialCase4(void)
{
}

HRESULT PartialCase4::CreateShaders(ID3D11Device* pd3dDevice)
{
	HRESULT hr = S_OK;

	m_NumShaders = 1;
	m_NumSubPatch = 2;

	if (!s_bShadersAreCreated) {

		std::vector<D3D_SHADER_MACRO*> macros;
		D3D_SHADER_MACRO partial0_macros[] = { { "BEZIER_HS_PARTITION", "\"integer\"" },{ "QUAD_DOMAIN", "1"} ,{ "CASE40", "1" } ,{0} }; macros.push_back(partial0_macros);


		V_RETURN(CreateShadersGeneral(pd3dDevice, macros));
		s_bShadersAreCreated = true;

		stg_pHSPartialsRegularBSpline = m_pHSPartialsRegularBSpline;
		stg_pDSPartialsRegularBSpline = m_pDSPartialsRegularBSpline;
	}
	else {
		m_pDSPartialsRegularBSpline = stg_pDSPartialsRegularBSpline;
		m_pHSPartialsRegularBSpline = stg_pHSPartialsRegularBSpline;
	}

	return hr;

}

void PartialCase4::DestroyShaders()
{
	if (!s_bShadersAreCreated)	return;

	for (UINT i = 0; i < m_NumShaders; i++) {
		if (stg_pHSPartialsRegularBSpline)				SAFE_RELEASE(stg_pHSPartialsRegularBSpline[i]);
		if (stg_pDSPartialsRegularBSpline)				SAFE_RELEASE(stg_pDSPartialsRegularBSpline[i]);
	}

	SAFE_DELETE_ARRAY(stg_pHSPartialsRegularBSpline);
	SAFE_DELETE_ARRAY(stg_pDSPartialsRegularBSpline);

	s_bShadersAreCreated = false;
}
