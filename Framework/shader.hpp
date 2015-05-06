
matrix g_matWorld;
matrix g_matView;
matrix g_matProj;
matrix g_matWV;
matrix g_matWVP;

texture g_BaseTex;

sampler S0 = sampler_state
{
	Texture = g_BaseTex;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct _tagMtrl 
{
	float4	vDif;
	float4	vAmb;
	float4	vSpc;
	float4	vEmv;
	float	fPower;
};

_tagMtrl	g_mtrlMesh;

struct VS_INPUT
{
	float3 vPos : POSITION;
	float2 vTex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 vPos : POSITION;
	float2 vTex : TEXCOORD0;
};



struct VS_INPUT_NOTEX
{
	float3 vPos : POSITION;
};

struct VS_OUTPUT_NOTEX
{
	float4 vPos : POSITION;
};



struct VS_INPUT_COLOR
{
	float3 vPos : POSITION;
	float4 vColor : COLOR0;
};

struct VS_OUTPUT_COLOR
{
	float4 vPos : POSITION;
	float4 vColor : COLOR0;
};


struct PS_OUTPUT
{
	float4 vColor : COLOR;
};

VS_OUTPUT DefaultVS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.vPos = mul(float4(input.vPos, 1.f) , g_matWVP);
	output.vTex = input.vTex;

	return output;
}

PS_OUTPUT DefaultPS(VS_OUTPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	
	output.vColor = tex2D(S0, input.vTex);

	return output;
}

PS_OUTPUT NotexPS()
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	output.vColor = g_mtrlMesh.vDif;

	return output;
}

//


VS_OUTPUT_COLOR ColorVS(VS_INPUT_COLOR input)
{
	VS_OUTPUT_COLOR output = (VS_OUTPUT_COLOR)0;

	output.vPos = mul(float4(input.vPos, 1.f) , g_matWVP);
	output.vColor = input.vColor;

	return output;
}

PS_OUTPUT ColorPS(VS_OUTPUT_COLOR input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	output.vColor = input.vColor;

	return output;
}
//
//�⺻ ��ũ��
technique DefaultTech
{
	//�⺻ �н�. 
	//vs : wvp ����, �ؽ�ó ��ǥ ��������
	//ps : �ؽ�ó ��ǥ�� �÷� ��� (�ؽ�ó ������?)
	pass DefulatPass
	{
		vertexshader = compile vs_3_0 DefaultVS();
		pixelshader = compile ps_3_0 DefaultPS();

	}

	//�ؽ�ó ���� �н�.
	//vs : wvp ����
	//ps : ���׸��� ���.
	pass NoTexturePass
	{
		vertexshader = compile vs_3_0 DefaultVS();
		pixelshader = compile ps_3_0 NotexPS();
	}

	//�ؽ�ó, ���׸��� ���� �н�. 
	//vs : wvp ����, �÷� �� ��������
	//ps : ���ؽ��� �÷� �� ���
	//�ٵ� ���ؽ� �÷� ���� ������ �־��µ� ��� vec4�� ������... �ű�
	pass TestLinePass
	{
		vertexshader = compile vs_3_0 ColorVS();
		pixelshader = compile ps_3_0 ColorPS();
	}
}