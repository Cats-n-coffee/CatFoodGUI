#version 330

in vec2 texCoord;

out vec4 color;

uniform sampler2D myTex;

void main()
{
	// color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	color = texture(myTex, texCoord);
}