#version 330 core
layout(location = 0) out vec4 out_color;
uniform sampler2D objTexture;
in float logz;

in vec2 texcoord;
void main()
{
  vec4 color1 = texture(objTexture, texcoord);
  out_color = color1;
  gl_FragDepth = logz;
}