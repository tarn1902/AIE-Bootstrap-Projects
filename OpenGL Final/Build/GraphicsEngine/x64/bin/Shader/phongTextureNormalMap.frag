// classic Phong fragment shader
#version 410
in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

struct DirLight {
    vec3 LightDirection;
    vec3 Ia;
    vec3 Id;
    vec3 Is;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 Ia;
    vec3 Id;
    vec3 Is;
};  

#define NR_DIR_LIGHTS 1
uniform DirLight dirLights[NR_DIR_LIGHTS];

#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform bool useDiffuse = false;
uniform bool useSpecular = false;
uniform bool useNormal = false;

uniform vec3 Ka; // ambient material colour
uniform vec3 Kd; // diffuse material colour
uniform vec3 Ks; // specular material colour
uniform float specularPower; // material specular power

uniform vec3 cameraPosition;

vec3 CalcDirLight(DirLight dirLight, vec3 N, vec3 V);
vec3 CalcPointLight(PointLight pointlight, vec3 N, vec3 V);
vec3 Ambient(vec3 Ia);
vec3 Diffuse(vec3 Id, vec3 N, vec3 L);
vec3 Specular(vec3 Is, vec3 L, vec3 N, vec3 V);
out vec4 FragColour;

void main() 
{
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 N = normalize(vNormal);
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	mat3 TBN = mat3(T,B,N);
	if(useNormal)
	{
		vec3 texNormal = texture(normalTexture, vTexCoord).rgb;
		N = TBN * (texNormal * 2 - 1);
	}
	// output final colour
	for(int i = 0; i < NR_DIR_LIGHTS; i++)
	{
		FragColour += vec4(CalcDirLight(dirLights[i], N, V), 1);
	}
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		FragColour += vec4(CalcPointLight(pointLights[i], N, V), 1);
	}
	
}

vec3 CalcDirLight(DirLight dirLight, vec3 N, vec3 V)
{
	//light directions are normalised
	vec3 L = normalize(dirLight.LightDirection);
	return Diffuse(dirLight.Id, N, L) + Ambient(dirLight.Ia) + Specular(dirLight.Is, L, N, V);
}

vec3 CalcPointLight(PointLight pointLight, vec3 N, vec3 V)
{
    vec3 L = normalize(pointLight.position - vPosition.xyz);
    // attenuation
    float distance = length(pointLight.position - vPosition.xyz);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
   
    // combine results
    vec3 ambient  = Ambient(pointLight.Ia);
    vec3 diffuse  = Diffuse(pointLight.Id, N, L);
    vec3 specular = Specular(pointLight.Is, L, N, V);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 Diffuse(vec3 Id, vec3 N, vec3 L)
{
	// calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );
	// calculate each colour property
	if(useDiffuse)
	{
		vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
		return Id * Kd * lambertTerm * texDiffuse;
	}

	return Id * Kd * lambertTerm;
}

vec3 Specular(vec3 Is, vec3 L, vec3 N, vec3 V)
{
	// calculate view vector and reflection vectorW
	vec3 R = reflect( L, N );
	// calculate specular term
	float specularTerm = pow(max(dot( R, V ), 0), specularPower );
	if(useSpecular)
	{
		vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
		return Is * Ks * specularTerm * texSpecular;
	}
	return Is * Ks * specularTerm;
}

vec3 Ambient(vec3 Ia)
{
	return Ia * Ka;
}

