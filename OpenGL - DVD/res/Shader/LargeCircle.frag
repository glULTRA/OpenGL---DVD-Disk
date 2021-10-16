#version 330 core 

out vec4 FragColor;

uniform vec3 Color;
in vec3 myColor;

void main() {
    FragColor = vec4(myColor * Color ,1.0f);    
}