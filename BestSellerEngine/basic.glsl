#shader vertex
#version 400 core

uniform mat4 MVP;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
    v_TexCoord = texCoord;
}





#shader fragment
#version 400 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    gl_FragColor = texColor;
}