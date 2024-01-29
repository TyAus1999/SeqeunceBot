#version 430
layout(location=0) in vec3 decalOffset;
layout(location=1) in vec2 textureCoordTopLeft;
layout(location=2) in vec2 textureCoordSize;
layout(location=3) in mat4 model;

flat out vec2 geoTopLeftTexture;
flat out vec2 geoTextureSize;
flat out mat4 geoProjection;

uniform mat4 projection;
uniform mat4 view;

void main(){
    geoTopLeftTexture=textureCoordTopLeft;
    geoTextureSize=textureCoordSize;
    geoProjection=projection*view*model;
    gl_Position=vec4(decalOffset,1);
}