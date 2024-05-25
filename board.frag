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
	float dist_ObjLig = length(lightVector);
	float a = 0.1f;
	float b = 0.02f;
	float intensity = 1 / (a * dist_ObjLig * dist_ObjLig + b * dist_ObjLig + 1.0f);

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

	return (texture(texPlanks, texCoord) * (diffuse * intensity + ambient) + texture(texSpec, texCoord).r * specular * intensity) * lightColor;
	//return (texture(texPlanks, texCoord)) * lightColor;
}

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness = 2.5f, float offset = 4.5f)
{
	float zVal = linearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
	// Outputs final color
	float depth = logisticDepth(gl_FragCoord.z);
	FragColor = pointLight() * (1.0f - depth) + vec4(depth * vec3(0.13f, 0.27f, 0.41f), 1.0f);
}