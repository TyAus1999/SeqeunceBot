#version 430

out vec4 FragColour;

in vec3 fragLoc;

void main(){
    float dist=distance(vec3(0), fragLoc);
    if(dist<3)
        FragColour=vec4(0,0,1,1);
    else
        discard;
}