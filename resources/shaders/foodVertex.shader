#version 330

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 modelViewProjection;

out vec2 texCoord;

void main() 
{
	gl_Position = modelViewProjection * vec4(aPosition, 1.0f);
	texCoord = aTexCoord;
}