#version 300 es
layout(location = 0) out mediump vec4 out_color;
uniform sampler2D texture_diffuse1;
 
in mediump vec2 texcoord;
void main()
{
  mediump vec4 color1 = texture(texture_diffuse1, texcoord);
  out_color = color1;
}