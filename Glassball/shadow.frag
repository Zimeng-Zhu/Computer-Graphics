#version 450 core
out vec4 FragColor;
void main()
{
    gl_FragDepth = gl_FragCoord.z;//可注释
    FragColor = vec4(vec3(gl_FragCoord.z), 1.0f);
}

