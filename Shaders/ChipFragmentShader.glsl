#version 430

out vec4 FragColour;

uniform vec3 chipColour;

in vec3 fragLoc;

void main(){
    float dist=distance(vec3(0), fragLoc);
    if(dist<3)
        FragColour=vec4(chipColour,1);
    else
        discard;
}