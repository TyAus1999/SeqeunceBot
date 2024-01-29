#version 430
layout(location=0) in vec3 decalOffset;
layout(location=1) in vec2 textureCoordTopLeft;
layout(location=2) in vec2 textureCoordSize;
layout(location=3) in mat4 model;
layout(location=7) in int isRedSuit;

flat out vec2 geoTopLeftTexture;
flat out vec2 geoTextureSize;
flat out mat4 geoProjection;
flat out int fragIsRedSuit;

uniform mat4 projection;
uniform mat4 view;

void main(){
    geoTopLeftTexture=textureCoordTopLeft;
    geoTextureSize=textureCoordSize;
    geoProjection=projection*view*model;
    gl_Position=vec4(decalOffset,1);
}