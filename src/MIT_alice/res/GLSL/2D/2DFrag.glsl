#version 440
in vec2 vTexCoord;

out vec4 oColor;

uniform sampler2D uTex;

void main()
{
    oColor = texture( uTex, vTexCoord.xy );
	if(oColor.a == 0.0)
		discard;
}
