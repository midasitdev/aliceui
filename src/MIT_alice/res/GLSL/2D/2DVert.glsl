#version 440

in vec3 position;
in vec2 texcoord;

out vec2 vTexCoord;

uniform mat4 uMatModelViewProjection;

void main()
{
    vTexCoord = texcoord;
    gl_Position = uMatModelViewProjection * vec4( position, 1.0 );
}
