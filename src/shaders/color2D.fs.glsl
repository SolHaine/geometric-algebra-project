#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;
out vec2 fFragPosition;

void main() {
  float alpha = 10;
  float beta = 30;
  fFragPosition = vFragPosition;
  float a = alpha * exp( -beta * pow( distance( vFragPosition , vec2(0,0) ) , 2 )) ;
  fFragColor = a * vFragColor;

  vec3 pattern1 = fFragColor * length(fract(5.0 * fFragPosition));
  vec3 pattern2 = fFragColor * length(abs(fract(5.0 * fFragPosition) * 2.0 - 1.0));
  vec3 pattern3 = fFragColor * smoothstep(0.3, 0.32, length(fract(5.0 * fFragPosition) - 0.5));
  vec3 pattern4 = fFragColor * smoothstep(0.4, 0.5, max(abs(fract(8.0 * fFragPosition.x - 0.5 * mod(floor(8.0 * fFragPosition.y), 2.0)) - 0.5), abs(fract(8.0 * fFragPosition.y) - 0.5)));
  vec3 mypattern = fFragColor * smoothstep(0.1, 3.0,6.0);
  fFragColor = mypattern;
};