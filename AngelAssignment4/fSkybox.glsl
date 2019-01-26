#version 440

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform mat4 model;
out vec4 color;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear_;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};


uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;

vec4 CalcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

	vec4 specularColor = vec4(0, 0, 0, 0);

	if (diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));

		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColor + diffuseColor + specularColor);
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = FragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 color = CalcLightByDirection(pLight.base, direction);
	float attenuation = pLight.exponent * distance * distance +
		pLight.linear_ * distance +
		pLight.constant;

	return (color / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);

	if (slFactor > sLight.edge)
	{
		vec4 color = CalcPointLight(sLight.base);

		return color * (1.0f - (1.0f - slFactor)*(1.0f / (1.0f - sLight.edge)));

	}
	else {
		return vec4(0, 0, 0, 0);
	}
}

float remap( float minval, float maxval, float curval )
{
    return ( curval - minval ) / ( maxval - minval );
} 
//                       r      b    g
vec4 rgb(float r, float b, float g){
	return vec4(r/256, b/256, g/256, 1);
}

const vec4 sun = rgb(230, 251, 95); 
const vec4 blueLight = rgb(153, 219, 255);
const vec4 blueDark = rgb(13, 112, 165);
const vec4 night = rgb(3, 38, 57);

void main()
{
	vec4 finalColor = CalcLightByDirection(directionalLight.base, directionalLight.direction);
	//finalColor += CalcPointLights();
	finalColor += CalcSpotLight(spotLight);

	//color = texture(theTexture, TexCoord) * finalColor;	

	
	//color = vec4(vec3(FragPos) * 0.02,1);
	//return;
	
	vec4 up = model[1];
	vec4 camPos = model[3];
	vec4 current = normalize(vec4(vec3(FragPos - vec3(model[3])),1));
	
	float skyFloat =  dot(up,current);
	//skyFloat = skyFloat * skyFloat;

	if(skyFloat > 0.9){
		float ratio = remap(0.9, 1.0, skyFloat);
		color = ratio * sun + (1 - ratio) * blueLight;
	}
	else if(skyFloat > 0.2){
		float ratio = remap(0.2, 0.9, skyFloat);
		color = ratio * blueLight + (1 - ratio) * blueDark;
	}
	else if(skyFloat > -0.6){
		float ratio = remap(-0.6, 0.2, skyFloat);
		color = ratio * blueDark + (1 - ratio) * night;
	}
	else{
		color = night;
	}

}