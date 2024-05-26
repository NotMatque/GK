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

vec4 spotLight()
{
	vec3 lightVector = lightPos - crntPos;
	float outerCone = 0.9f;
	float innerCone = 0.95f;

	// Ambient
	float ambient = 0.1f;

	// Diffusion lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVector);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(normalize(vec3(-1.0f, -2.0f, -1.0f)), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(texPlanks, texCoord) * (diffuse * inten + ambient) + texture(texSpec, texCoord).r * specular * inten) * lightColor;
}

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset)
{
	float zVal = linearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));

}

float logisticDepthWrapper(float depth) {
	return logisticDepth(depth, 2.5f, 4.5f);
}

void main()
{
	// Outputs final color
	float depth = logisticDepthWrapper(gl_FragCoord.z);
	// FragColor = spotLight() * (1.0f - depth) + vec4(depth * vec3(0.13f, 0.27f, 0.41f), 1.0f);
	FragColor = spotLight() * (1.0f - depth) + vec4(depth * vec3(0.0f, 0.0f, 0.0f), 1.0f);
}