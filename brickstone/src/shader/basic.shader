#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 v_SurfaceNormal;
out vec3 v_ToLightVector;
out vec3 v_FragmentPosition;
out vec3 v_Position;
out vec2 v_TexCoord;


uniform vec3 u_LightPosition;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {

	vec4 worldPosition = u_Model * position;

	gl_Position = u_Projection * (u_View * (worldPosition));

	v_SurfaceNormal = (u_Model * vec4(normal, 0.0)).xyz;
	v_ToLightVector = u_LightPosition - worldPosition.xyz;
	v_FragmentPosition = vec3(worldPosition);
	v_Position = position.xyz;
	v_TexCoord = texCoord;

}

#shader fragment
#version 330 core

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

layout(location = 0) out vec4 color;

in vec3 v_SurfaceNormal;
in vec3 v_ToLightVector;
in vec3 v_FragmentPosition;
in vec3 v_Position;
in vec2 v_TexCoord;

uniform vec3 u_LightColor;
uniform vec3 u_ViewPosition;
uniform material u_Material;

void main() {

	//ambient
	vec3 ambient = vec3(0.0);
	if (u_Material.useDiffuseMap == 1) {
		ambient = u_Material.ambient * vec3(texture(u_Material.diffuseMap, v_TexCoord)) * u_LightColor;
	}
	else {
		ambient = u_LightColor * u_Material.ambient;
	}

	//diffuse
	vec3 unitNormal = normalize(v_SurfaceNormal);
	vec3 unitLight = normalize(v_ToLightVector);
	float diff = max(dot(unitNormal, unitLight), 0.0);
	vec3 diffuse;
	if (u_Material.useDiffuseMap == 1) {
		diffuse = vec3(texture(u_Material.diffuseMap, v_TexCoord))* diff * u_LightColor;
	}
	else {
		diffuse = u_LightColor * diff * u_Material.diffuse;
	}

	//specular
	vec3 viewDir = normalize(u_ViewPosition - v_FragmentPosition);
	vec3 reflectionDir = reflect(-normalize(v_ToLightVector), v_SurfaceNormal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0), u_Material.shininess);
	vec3 specular;
	if (u_Material.useSpecularMap == 1) {
		specular = vec3(texture(u_Material.specularMap, v_TexCoord)) * spec * u_LightColor;
	}
	else {
		specular = u_Material.specular * spec * u_LightColor;
	}

	vec3 result = (ambient + diffuse + specular);

	color = vec4(result, 1.0);
	//color = texture(u_Sampler, v_TexCoord) * vec4(result, 1.0);


}