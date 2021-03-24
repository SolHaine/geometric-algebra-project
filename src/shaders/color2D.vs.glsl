#version 330 core

mat3 translate(float x, float y) {
  mat3 translate = mat3(vec3(1,0,0), vec3(0,1,0), vec3(x,y,1));
  return translate;
}

mat3 scale(float sx, float sy) {
  mat3 scale = mat3(vec3(sx,0,0), vec3(0,sy,0), vec3(0,0,1));
  return scale;
}

mat3 rotate(float a) {
  float b = radians(a);
  mat3 rotate = mat3( vec3(cos(b),sin(b),0), vec3(-sin(b),cos(b),0), vec3(0,0,1));
  return rotate;
}

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vFragPosition;

void main() {
  vFragColor = aVertexColor;
  //gl_Position = vec4( ( scale(0.5,0.5) * rotate(-45) * translate(0.5,0) * vec3(aVertexPosition,1)).xy , 0, 1);
  vFragPosition = aVertexPosition;
  gl_Position = vec4(vec3(aVertexPosition,1).xy , 0, 1);

}