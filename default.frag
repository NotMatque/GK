#version 330 core

in vec2 texCoord;
in vec3 crntPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texCube;
uniform sampler2D texNormal;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
	vec3 lightVector = lightPos - crntPos;
	float dist_ObjLig = length(lightVector);
	float a = 0.1f;
	float b = 0.02f;
	float intensity = 1 / (a * dist_ObjLig * dist_ObjLig + b * dist_ObjLig + 1.0f);

	// Ambient lighting
	float ambient = 0.05f;


	// Diffues lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular lighting
	float specular = 0.0f;
	if(diffuse != 0.0f);
	{
		float specularLight = 0.5f;
		vec3 viewDirection = normalize(camPos - crntPos);
		vec3 reflectionDirection = reflect(-lightDirection, normal);

		vec3 halfwayVec = normalize(viewDirection + lightDirection);

		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	}

	return (texture(texCube, texCoord) * (diffuse * intensity + ambient + specular * intensity)) * lightColor;
}


void main()
{
	FragColor = pointLight();
}