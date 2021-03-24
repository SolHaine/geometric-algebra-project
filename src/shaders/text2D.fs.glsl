#version 330 core

in vec2 vFragTexture;
in vec2 vFragPosition;

out vec3 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture;

void main() {
  vec4 texture = texture(uTexture,vFragTexture);
  fFragColor = vec3(texture);
};
