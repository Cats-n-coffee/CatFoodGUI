#version 330

layout (location = 0) in vec2 position;
uniform mat4 modelViewProjection;

void main() 
{
	gl_Position = modelViewProjection * vec4(position, 0.0f, 1.0f);
}