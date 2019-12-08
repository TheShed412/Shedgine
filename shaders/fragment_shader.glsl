#version 300 es
layout(location = 0) out mediump vec4 out_color;
in mediump vec4 color;
 
void main()
{
  out_color = color;
}