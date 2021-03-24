#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

out vec2 vFragTexture;
out vec2 vFragPosition;

/*
mat3 rotate(float a) {
  float b = radians(a);
  mat3 rotate = mat3( vec3(cos(b),sin(b),0), vec3(-sin(b),cos(b),0), vec3(0,0,1));
  return rotate;
}

uniform float uTime;
*/

uniform mat3 uModelMatrix;

void main() {
  vFragTexture = aVertexTexture;
  gl_Position = vec4( (uModelMatrix * vec3(aVertexPosition,1)).xy , 0, 1);
  vFragPosition = aVertexPosition;
}