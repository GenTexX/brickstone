#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 v_SurfaceNormal;

out vec3 v_FragmentPosition;
out vec3 v_Position;
out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {

	//worldPosition
	vec4 worldPosition = u_Model * position;

	//VertexPositrion
	gl_Position = u_Projection * (u_View * (worldPosition));

	//normal
	v_SurfaceNormal = vec3(u_Model * vec4(normal, 0.0));


	v_FragmentPosition = vec3(worldPosition);
	v_Position = vec3(position);
	v_TexCoord = texCoord;

}

#shader fragment
#version 330 core

struct dirLight {

	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

struct pointLight {

	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float lin;
	float quadratic;

};

struct spotLight {

	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float lin;
	float quadratic;

	float innerCutOff;
	float outerCutOff;

};

struct material {

	vec3 ambient;
	vec3 diffuse;
	sampler2D diffuseMap;
	int useDiffuseMap;
	sampler2D specularMap;
	int useSpecularMap;
	vec3 specular;
	float shininess;

};

vec3 calcDirLight(dirLight light, vec3 viewDir);
vec3 calcPointLight(pointLight light, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(spotLight light, vec3 fragPos, vec3 viewDir);

layout(location = 0) out vec4 color;

in vec3 v_SurfaceNormal;
in vec3 v_FragmentPosition;
in vec3 v_Position;
in vec2 v_TexCoord;



uniform vec3 u_ViewPosition;
uniform material u_Material;

#define MAX_LIGHTS 4
uniform dirLight u_DirLights[MAX_LIGHTS];
uniform pointLight u_PointLights[MAX_LIGHTS];
uniform spotLight u_SpotLights[MAX_LIGHTS];

void main() {

	vec3 viewDir = normalize(u_ViewPosition - v_FragmentPosition);
	vec3 result = vec3(0.0);

	vec3 ambient = vec3(1.0);
	vec3 diffuse = vec3(1.0);
	vec3 specular = vec3(1.0);

	for (int i = 0; i < 4; i++) {
	
		//if (u_DirLights[i].diffuse.x == 0)
		//	result += vec3(0.4, 0.0, 0.0);
		result += calcDirLight(u_DirLights[i], viewDir);
	
	}

	for (int i = 0; i < 4; i++) {

		vec3 pointL = calcPointLight(u_PointLights[i], v_FragmentPosition, viewDir);
		if (pointL.x >= 0.0)
			result += pointL;

	}

	for (int i = 0; i < 4; i++) {

		vec3 pointL = calcSpotLight(u_SpotLights[i], v_FragmentPosition, viewDir);
		if (pointL.x >= 0.0)
			result += pointL;

	}

	//if (u_SpotLights[0].ambient.x == 1.0)
	//	result = vec3(0.2, 0.4, 0.2);

	//result = ambient + (diffuse + specular) * lightValue;

	color = vec4(result, 1.0);

}

vec3 calcDirLight(dirLight light, vec3 viewDir) {

	vec3 lightDir = normalize(-light.direction);

	//ambient
	vec3 ambient = vec3(0.0);

	if (u_Material.useDiffuseMap == 1) {
		ambient = u_Material.ambient * vec3(texture(u_Material.diffuseMap, v_TexCoord));
	}
	else {
		ambient = u_Material.ambient;
	}
	ambient *= light.ambient;
	

	//diffuse
	vec3 diffuse = vec3(1.0);

	vec3 unitNormal = normalize(v_SurfaceNormal);
	float diff = max(dot(unitNormal, lightDir), 0.0);
	if (u_Material.useDiffuseMap == 1) {
		diffuse = diff * vec3(texture(u_Material.diffuseMap, v_TexCoord));
	}
	else {
		diffuse = diff * u_Material.diffuse;
	}
	diffuse *= light.diffuse*2;
	//specular
	vec3 specular;

	vec3 reflectionDir = reflect(-lightDir, v_SurfaceNormal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), u_Material.shininess);
	if (u_Material.useSpecularMap == 1) {
		specular = vec3(texture(u_Material.specularMap, v_TexCoord)) * spec;
	}
	else {
		specular = spec * u_Material.specular;
	}
	specular *= light.specular;

	// combine results
	return (ambient + diffuse + specular);

}

vec3 calcPointLight(pointLight light, vec3 fragPos, vec3 viewDir) {

	vec3 lightDir = normalize(light.position - v_FragmentPosition);

	//ambient
	vec3 ambient = vec3(0.4);

	if (u_Material.useDiffuseMap == 1) {
		ambient = u_Material.ambient * vec3(texture(u_Material.diffuseMap, v_TexCoord));
	}
	else {
		ambient = u_Material.ambient;
	}
	ambient *= light.ambient;

	//diffuse
	vec3 diffuse;

	vec3 unitNormal = normalize(v_SurfaceNormal);
	float diff = max(dot(unitNormal, lightDir), 0.0);
	if (u_Material.useDiffuseMap == 1) {
		diffuse = diff * vec3(texture(u_Material.diffuseMap, v_TexCoord));
	}
	else {
		diffuse = diff * u_Material.diffuse;
	}
	diffuse *= light.diffuse;



	//specular
	vec3 specular;

	vec3 reflectionDir = reflect(-lightDir, v_SurfaceNormal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), u_Material.shininess);
	if (u_Material.useSpecularMap == 1) {
		specular = vec3(texture(u_Material.specularMap, v_TexCoord)) * spec;
	}
	else {
		specular = spec * u_Material.specular;
	}
	specular *= light.specular;


	float distance = length(light.position - v_FragmentPosition);
	float attenuation = 1.0 / (light.constant + light.lin * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;


	return (ambient + diffuse + specular);

}

vec3 calcSpotLight(spotLight light, vec3 fragPos, vec3 viewDir) {


	vec3 lightDir = normalize(-light.direction);

	//ambient
	vec3 ambient = vec3(0.0);

	if (u_Material.useDiffuseMap == 1) {
		ambient = u_Material.ambient * vec3(texture(u_Material.diffuseMap, v_TexCoord));
	}
	else {
		ambient = u_Material.ambient;
	}
	ambient *= light.ambient;


	//diffuse
	vec3 diffuse;

	vec3 unitNormal = normalize(v_SurfaceNormal);
	float diff = max(dot(unitNormal, lightDir), 0.0);
	if (u_Material.useDiffuseMap == 1) {
		diffuse = diff * vec3(texture(u_Material.diffuseMap, v_TexCoord));
	}
	else {
		diffuse = diff * u_Material.diffuse;
	}
	diffuse *= light.diffuse;


	//specular
	vec3 specular;

	vec3 reflectionDir = reflect(-lightDir, v_SurfaceNormal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), u_Material.shininess);
	if (u_Material.useSpecularMap == 1) {
		specular = vec3(texture(u_Material.specularMap, v_TexCoord)) * spec;
	}
	else {
		specular = spec * u_Material.specular;
	}
	specular *= light.specular;


	float distance = length(light.position - v_FragmentPosition);
	float attenuation = 1.0 / (light.constant + light.lin * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	ambient *= intensity;
	diffuse *= intensity;
	specular *= intensity;


	return (ambient + diffuse + specular);


}