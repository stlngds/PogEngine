#shader vertex
#version 400
uniform mat4 MVP;
in vec3 vertex_position;
in vec3 vertex_color;
in vec2 texCoord;
out vec3 color;
out vec2 v_TexCoord;
void main()
{
    gl_Position = MVP * vec4(vertex_position, 1.0);
    color = vertex_color;
    v_TexCoord = texCoord;
};


#shader fragment
#version 400
in vec3 color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture; // Does not exist!
void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    
    gl_FragColor = vec4(texColor, 1.0);
};

