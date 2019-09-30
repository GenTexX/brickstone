#shader vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 v_Position;
out vec2 v_TexCoord;


uniform vec3 u_LightPosition;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {

	vec4 worldPosition = u_Model * position;

	gl_Position = u_Projection * (u_View * (worldPosition));

	surfaceNormal = (u_Model * vec4(normal, 0.0)).xyz;
	toLightVector = u_LightPosition - worldPosition.xyz;
	v_Position = position.xyz;
	v_TexCoord = texCoord;

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 v_Position;
in vec2 v_TexCoord;

uniform vec3 u_LightColor;
uniform sampler2D u_Sampler;

void main() {

	//ambient
	vec3 ambient = u_LightColor * 0.5;

	//diffuse
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLight = normalize(toLightVector);
	vec3 diffuse = max(dot(unitNormal, unitLight), 0.0) * u_LightColor * 0.5;

	vec3 result = ambient + diffuse;
	//color = texture(u_Sampler, v_TexCoord) * vec4(result, 1.0);
	color = vec4(result, 1.0);

}