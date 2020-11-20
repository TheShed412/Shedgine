#version 300 es
layout(location = 0) out mediump vec4 out_color;
uniform sampler2D objTexture;
in mediump float logz;

in mediump vec2 texcoord;
void main()
{
  mediump vec4 color1 = texture(objTexture, texcoord);
  out_color = color1;
  gl_FragDepth = logz;
}