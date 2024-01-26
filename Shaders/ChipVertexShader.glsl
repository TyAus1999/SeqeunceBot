#version 430
layout(location=0)in vec3 vertexLocation;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 fragLoc;

void main(){
    gl_Position=projection*view*model*vec4(vertexLocation,1);
    fragLoc=vertexLocation;
}