#version 430
layout(location=0) in vec3 vertexLocation;
layout(location=1) in vec2 textureCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 fragTextureCoord;

void main(){
    gl_Position=projection*view*model*vec4(vertexLocation,1);
    fragTextureCoord=textureCoord;
}