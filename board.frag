#version 330 core

in vec2 texCoord;
in vec3 crntPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texPlanks;
uniform sampler2D texSpec;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
	vec3 lightVector = lightPos - crntPos;
	// Ambient
	float ambient = 0.05f;

	// Diffusion lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(texPlanks, texCoord) * (diffuse + ambient) + texture(texSpec, texCoord).r * specular) * lightColor;
	//return (texture(texPlanks, texCoord)) * lightColor;
}

void main()
{
	// Outputs final color
	//FragColor = vec4(0.6f, 0.2f, 0.9f, 1.0f);
	FragColor = pointLight();
}