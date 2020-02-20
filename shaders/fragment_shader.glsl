#version 300 es
out mediump vec4 out_color;
in mediump vec4 color;
uniform sampler2D texture1;
 
in mediump vec2 texcoord;
void main()
{
  mediump vec4 color1 = texture(texture1, texcoord);
  out_color = color1;
}