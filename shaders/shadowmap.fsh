varying float distance;

void main() {
  float normDistance = 5.0/distance;
  gl_FragColor = vec4(normDistance, normDistance, normDistance, 1.0);
}
