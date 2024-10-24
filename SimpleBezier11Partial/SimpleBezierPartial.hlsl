//--------------------------------------------------------------------------------------
// File: SimpleBezier11.hlsl
//
// This sample shows an simple implementation of the DirectX 11 Hardware Tessellator
// for rendering a Bezier Patch.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// This allows us to compile the shader with a #define to choose
// the different partition modes for the hull shader.
// See the hull shader: [partitioning(BEZIER_HS_PARTITION)]
// This sample demonstrates "integer", "fractional_even", and "fractional_odd"

#if D3DX_VERSION == 0xa2b
#pragma ruledisable 0x0802405f
#endif


#ifndef BEZIER_HS_PARTITION
#define BEZIER_HS_PARTITION "integer"
#endif // BEZIER_HS_PARTITION

// The input patch size.  In this sample, it is 16 control points.
// This value should match the call to IASetPrimitiveTopology()
#define INPUT_PATCH_SIZE 16

// The output patch size.  In this sample, it is also 16 control points.
#define OUTPUT_PATCH_SIZE 16

//--------------------------------------------------------------------------------------
// Constant Buffers
//--------------------------------------------------------------------------------------
cbuffer cbPerFrame : register( b0 )
{
    matrix g_mViewProjection;
    float3 g_vCameraPosWorld;
    float  g_fTessellationFactor;
};

//--------------------------------------------------------------------------------------
// Vertex shader section
//--------------------------------------------------------------------------------------
struct VS_CONTROL_POINT_INPUT
{
    float3 vPosition        : POSITION;
};

struct VS_CONTROL_POINT_OUTPUT
{
    float3 vPosition        : POSITION;
};

// This simple vertex shader passes the control points straight through to the
// hull shader.  In a more complex scene, you might transform the control points
// or perform skinning at this step.

// The input to the vertex shader comes from the vertex buffer.

// The output from the vertex shader will go into the hull shader.

VS_CONTROL_POINT_OUTPUT BezierVS( VS_CONTROL_POINT_INPUT Input )
{
    VS_CONTROL_POINT_OUTPUT Output;

    Output.vPosition = Input.vPosition;

    return Output;
}

//--------------------------------------------------------------------------------------
// Constant data function for the BezierHS.  This is executed once per patch.
//--------------------------------------------------------------------------------------

struct HS_CONSTANT_DATA_OUTPUT_QUAD
{
    float Edges[4]             : SV_TessFactor;
    float Inside[2]            : SV_InsideTessFactor;
};

struct HS_CONSTANT_DATA_OUTPUT_TRI
{
    float Edges[3]			: SV_TessFactor;
    float Inside			: SV_InsideTessFactor;
};

struct HS_OUTPUT
{
    float3 vPosition           : BEZIERPOS;
};

// This constant hull shader is executed once per patch.  For the simple Mobius strip
// model, it will be executed 4 times.  In this sample, we set the tessellation factor
// via SV_TessFactor and SV_InsideTessFactor for each patch.  In a more complex scene,
// you might calculate a variable tessellation factor based on the camera's distance.
#ifdef TRI_DOMAIN
HS_CONSTANT_DATA_OUTPUT_TRI BezierConstantHS( InputPatch<VS_CONTROL_POINT_OUTPUT, INPUT_PATCH_SIZE> ip,
                                          uint PatchID : SV_PrimitiveID )
{  
    HS_CONSTANT_DATA_OUTPUT_TRI Output;
#else
HS_CONSTANT_DATA_OUTPUT_QUAD BezierConstantHS( InputPatch<VS_CONTROL_POINT_OUTPUT, INPUT_PATCH_SIZE> ip,
                                          uint PatchID : SV_PrimitiveID )
{ 
        HS_CONSTANT_DATA_OUTPUT_QUAD Output;
#endif


    float TessAmount = g_fTessellationFactor;

#ifdef CASE00

	float side = sqrt(1.25) * TessAmount;
    if(PatchID % 3 ==1)
    {
        Output.Edges[0] = TessAmount;
        Output.Edges[1] = side;
        Output.Edges[2] = TessAmount/2.0;    
        Output.Inside = 0.33 * (Output.Edges[0] + Output.Edges[1] + Output.Edges[2]) ;
    }
    else if(PatchID % 3 ==2)
    {
        Output.Edges[0] = TessAmount;
        Output.Edges[1] = TessAmount/2.0;
        Output.Edges[2] = side;    
        Output.Inside = 0.33 * (Output.Edges[0] + Output.Edges[1] + Output.Edges[2]) ;
    }
    else
    {
        Output.Edges[0] = side;
        Output.Edges[1] = TessAmount;
        Output.Edges[2] = side;
        Output.Inside = 0.33 * (Output.Edges[0] + Output.Edges[1] + Output.Edges[2]) ;

    }


#endif  

#ifdef CASE10 

    if(PatchID % 4 ==1)
    {
        float side = sqrt(1.25) * TessAmount;
        Output.Edges[0] = TessAmount;
        Output.Edges[1] = TessAmount/2.0;
        Output.Edges[2] = side;    
        Output.Inside = 0.33 * (Output.Edges[0] + Output.Edges[1] + Output.Edges[2]) ;
    }
    else if(PatchID % 4 ==2)
    {
        float side = sqrt(0.5) * TessAmount;
        Output.Edges[0] = TessAmount/2.0;
        Output.Edges[1] = TessAmount/2.0;
        Output.Edges[2] = side;    
        Output.Inside = 0.33 * (Output.Edges[0] + Output.Edges[1] + Output.Edges[2]) ;
    }
    else if(PatchID % 4 ==3)
    {
        float side1 = sqrt(1.25) * TessAmount;
        float side2 = sqrt(0.5) * TessAmount;
        Output.Edges[0] = side1;
        Output.Edges[1] = side1;
        Output.Edges[2] = side2;    
        Output.Inside = 0.33 * (Output.Edges[0] + Output.Edges[1] + Output.Edges[2]) ;
    }
    else
    {
        float side = sqrt(1.25) * TessAmount;
        Output.Edges[0] = TessAmount;
        Output.Edges[1] = side;
        Output.Edges[2] = TessAmount/2.0;    
        Output.Inside = 0.33 * (Output.Edges[0] + Output.Edges[1] + Output.Edges[2]) ;
    }



#endif

#ifdef CASE20 
    Output.Edges[0] = TessAmount/2.0;
    Output.Edges[1] = TessAmount;
    Output.Edges[2] = TessAmount/2.0;
    Output.Edges[3] = TessAmount;
    Output.Inside[0] = TessAmount;
    Output.Inside[1] = TessAmount/2.0;
#endif
#ifdef CASE21 
	float side = sqrt(0.5) * TessAmount;
    Output.Edges[0] = TessAmount/2.0;
    Output.Edges[1] = side;
    Output.Edges[2] = TessAmount/2.0;    
    Output.Inside = TessAmount/2.0;
#endif
#ifdef CASE22 
	float side = sqrt(0.5) * TessAmount;
    Output.Edges[0] = TessAmount/2.0;
    Output.Edges[1] = TessAmount/2.0;
    Output.Edges[2] = side;    
    Output.Inside = TessAmount/2.0;
#endif
#ifdef CASE23 
	float side = sqrt(0.5) * TessAmount;
    Output.Edges[0] = side;
    Output.Edges[1] = side;
    Output.Edges[2] = TessAmount;    
    Output.Inside = TessAmount/2.0;
#endif


#ifdef CASE30 

    if(PatchID % 4 ==1)
    {
        Output.Edges[0] = Output.Edges[1] = Output.Edges[2] = Output.Edges[3] = TessAmount/2.0;
        Output.Inside[0] = Output.Inside[1] = TessAmount/2.0;
    }
    else if(PatchID % 4 ==2)
    {
        Output.Edges[0] = Output.Edges[1] = Output.Edges[2] = Output.Edges[3] = TessAmount/2.0;
        Output.Inside[0] = Output.Inside[1] = TessAmount/2.0;
    }
    else if(PatchID % 4 ==3)
    {
        Output.Edges[0] = Output.Edges[1] = Output.Edges[2] = Output.Edges[3] = TessAmount/2.0;
        Output.Inside[0] = Output.Inside[1] = TessAmount/2.0;
    }
    else
    {
        Output.Edges[0] = Output.Edges[1] = Output.Edges[2] = Output.Edges[3] = TessAmount/2.0;
        Output.Inside[0] = Output.Inside[1] = TessAmount/2.0;
    }

#endif


#ifdef CASE40

    if(PatchID % 2 ==1)
    {
        Output.Edges[0] = TessAmount;
        Output.Edges[1] = TessAmount/2.0;
        Output.Edges[2] = TessAmount;
        Output.Edges[3] = TessAmount/2.0;
        Output.Inside[0] = TessAmount/2.0;
        Output.Inside[1] = TessAmount;
    }
    else
    {
        Output.Edges[0] = TessAmount;
        Output.Edges[1] = TessAmount/2.0;
        Output.Edges[2] = TessAmount;
        Output.Edges[3] = TessAmount/2.0;
        Output.Inside[0] = TessAmount/2.0;
        Output.Inside[1] = TessAmount;
    }

#endif

    return Output;
}

// The hull shader is called once per output control point, which is specified with
// outputcontrolpoints.  For this sample, we take the control points from the vertex
// shader and pass them directly off to the domain shader.  In a more complex scene,
// you might perform a basis conversion from the input control points into a Bezier
// patch, such as the SubD11 Sample.

// The input to the hull shader comes from the vertex shader

// The output from the hull shader will go to the domain shader.
// The tessellation factor, topology, and partition mode will go to the fixed function
// tessellator stage to calculate the UVW and domain points.

#ifdef TRI_DOMAIN
[domain("tri")]
#else
[domain("quad")]
#endif
[partitioning(BEZIER_HS_PARTITION)]
[outputtopology("triangle_cw")]
[outputcontrolpoints(OUTPUT_PATCH_SIZE)]
[patchconstantfunc("BezierConstantHS")]
HS_OUTPUT BezierHS( InputPatch<VS_CONTROL_POINT_OUTPUT, INPUT_PATCH_SIZE> p, 
                    uint i : SV_OutputControlPointID,
                    uint PatchID : SV_PrimitiveID )
{
    HS_OUTPUT Output;
    Output.vPosition = p[i].vPosition;
    return Output;
}

//--------------------------------------------------------------------------------------
// Bezier evaluation domain shader section
//--------------------------------------------------------------------------------------
struct DS_OUTPUT
{
    float4 vPosition        : SV_POSITION;
    float3 vWorldPos        : WORLDPOS;
    float3 vNormal            : NORMAL;
};

//--------------------------------------------------------------------------------------
float4 BernsteinBasis(float t)
{
    float invT = 1.0f - t;

    return float4( invT * invT * invT,
                   3.0f * t * invT * invT,
                   3.0f * t * t * invT,
                   t * t * t );
}

//--------------------------------------------------------------------------------------
float4 dBernsteinBasis(float t)
{
    float invT = 1.0f - t;

    return float4( -3 * invT * invT,
                   3 * invT * invT - 6 * t * invT,
                   6 * t * invT - 3 * t * t,
                   3 * t * t );
}

//--------------------------------------------------------------------------------------
float3 EvaluateBezier( const OutputPatch<HS_OUTPUT, OUTPUT_PATCH_SIZE> bezpatch,
                       float4 BasisU,
                       float4 BasisV )
{
    float3 Value = float3(0,0,0);
    Value  = BasisV.x * ( bezpatch[0].vPosition * BasisU.x + bezpatch[1].vPosition * BasisU.y + bezpatch[2].vPosition * BasisU.z + bezpatch[3].vPosition * BasisU.w );
    Value += BasisV.y * ( bezpatch[4].vPosition * BasisU.x + bezpatch[5].vPosition * BasisU.y + bezpatch[6].vPosition * BasisU.z + bezpatch[7].vPosition * BasisU.w );
    Value += BasisV.z * ( bezpatch[8].vPosition * BasisU.x + bezpatch[9].vPosition * BasisU.y + bezpatch[10].vPosition * BasisU.z + bezpatch[11].vPosition * BasisU.w );
    Value += BasisV.w * ( bezpatch[12].vPosition * BasisU.x + bezpatch[13].vPosition * BasisU.y + bezpatch[14].vPosition * BasisU.z + bezpatch[15].vPosition * BasisU.w );

    return Value;
}

// The domain shader is run once per vertex and calculates the final vertex's position
// and attributes.  It receives the UVW from the fixed function tessellator and the
// control point outputs from the hull shader.  Since we are using the DirectX 11
// Tessellation pipeline, it is the domain shader's responsibility to calculate the
// final SV_POSITION for each vertex.  In this sample, we evaluate the vertex's
// position using a Bernstein polynomial and the normal is calculated as the cross
// product of the U and V derivatives.

// The input SV_DomainLocation to the domain shader comes from fixed function
// tessellator.  And the OutputPatch comes from the hull shader.  From these, you
// must calculate the final vertex position, color, texcoords, and other attributes.

// The output from the domain shader will be a vertex that will go to the video card's
// rasterization pipeline and get drawn to the screen.

#ifdef TRI_DOMAIN
[domain("tri")]
DS_OUTPUT BezierDS( HS_CONSTANT_DATA_OUTPUT_TRI input, 
                    float3 uvw : SV_DomainLocation,
                    const OutputPatch<HS_OUTPUT, OUTPUT_PATCH_SIZE> bezpatch,
                    uint PatchID : SV_PrimitiveID  )
{
#else
[domain("quad")]
DS_OUTPUT BezierDS( HS_CONSTANT_DATA_OUTPUT_QUAD input, 
                    float2 uv : SV_DomainLocation,
                    const OutputPatch<HS_OUTPUT, OUTPUT_PATCH_SIZE> bezpatch,
                    uint PatchID : SV_PrimitiveID  )
{
#endif

    float2 UV;
	UV = float2(0.0,0.0);

#ifdef CASE00

    if(PatchID % 3 ==1)
    {
        UV.x = 1.0-uvw.x/2.0;
        UV.y = uvw.z;
    }
    else if(PatchID % 3 ==2)
    {
        UV.x = uvw.x/2.0;
        UV.y = uvw.y;
    }
    else
    {
        UV.x = 1.0-uvw.x-uvw.y/2.0;
        UV.y = 1.0-uvw.y;
    }

#endif	

#ifdef CASE10

    if(PatchID % 4 ==1)
    {
        UV.x = uvw.y;
        UV.y = 1.0-uvw.x/2.0;
    }
    else if(PatchID % 4 ==2)
    {
        UV.x = uvw.x/2.0;
        UV.y = uvw.y/2.0;
    }
    else if(PatchID % 4 ==3)
    {
        UV.x = 1.0-uvw.x-uvw.y/2.0;
        UV.y = 1.0-uvw.y-uvw.x/2.0;
    }
    else
    {
        UV.x = 1.0-uvw.x/2.0;
        UV.y = uvw.z;
    }


#endif

#ifdef CASE20
	UV.x = uv.x;
	UV.y = uv.y/2.0;
#endif
#ifdef CASE21
	UV.x = uvw.x/2.0;
	UV.y = 1.0-uvw.z/2.0;
#endif
#ifdef CASE22
	UV.x = 1.0-uvw.x/2.0;
	UV.y = 1.0-uvw.y/2.0;
#endif
#ifdef CASE23
	UV.x = 1.0-uvw.x-uvw.z/2.0;
	UV.y = 0.5+uvw.z/2.0;
#endif

#ifdef CASE30


    if(PatchID % 4 ==1)
    {
        UV.x = 1.0 - uv.x/2.0;
        UV.y = 0.5 - uv.y/2.0;
    }
    else if(PatchID % 4 ==2)
    {
        UV.x = 0.5 - uv.x/2.0;
        UV.y = 1.0 - uv.y/2.0;
    }
    else if(PatchID % 4 ==3)
    {
        UV.x = 1.0 - uv.x/2.0;
        UV.y = 1.0 - uv.y/2.0;
    }
    else
    {
        UV.x = uv.x/2.0;
        UV.y = uv.y/2.0;
    }



#endif

#ifdef CASE40

    if(PatchID % 2 ==1)
    {
        UV.x = uv.x/2.0 + 0.5;
        UV.y = uv.y;
    }
    else
    {
        UV.x = uv.x/2.0;
        UV.y = uv.y;
    }

#endif
    float4 BasisU = BernsteinBasis( UV.x );
    float4 BasisV = BernsteinBasis( UV.y );
    float4 dBasisU = dBernsteinBasis( UV.x );
    float4 dBasisV = dBernsteinBasis( UV.y );

    float3 WorldPos = EvaluateBezier( bezpatch, BasisU, BasisV );
    float3 Tangent = EvaluateBezier( bezpatch, dBasisU, BasisV );
    float3 BiTangent = EvaluateBezier( bezpatch, BasisU, dBasisV );
    float3 Norm = normalize( cross( Tangent, BiTangent ) );

    DS_OUTPUT Output;
    Output.vPosition = mul( float4(WorldPos,1), g_mViewProjection );
    Output.vWorldPos = WorldPos;
    Output.vNormal = Norm;

    return Output;    

}
//--------------------------------------------------------------------------------------
// Smooth shading pixel shader section
//--------------------------------------------------------------------------------------

// The pixel shader works the same as it would in a normal graphics pipeline.
// In this sample, it performs very simple N dot L lighting.

float4 BezierPS( DS_OUTPUT Input ) : SV_TARGET
{
    float3 N = normalize(Input.vNormal);
    float3 L = normalize(Input.vWorldPos - g_vCameraPosWorld);
    return abs(dot(N, L)) * float4(1, 0, 0, 1);
}

//--------------------------------------------------------------------------------------
// Solid color shading pixel shader (used for wireframe overlay)
//--------------------------------------------------------------------------------------
float4 SolidColorPS( DS_OUTPUT Input ) : SV_TARGET
{
    // Return a solid green color
    return float4( 0, 1, 0, 1 );
}
