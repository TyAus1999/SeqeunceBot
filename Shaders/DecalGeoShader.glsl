#version 430
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

flat in vec2 geoTopLeftTexture[];
flat in vec2 geoTextureSize[];
flat in mat4 geoProjection[];

flat out vec2 fragTextureCoord;

void main(){
    vec4 origin=gl_in[0].gl_Position;
    float size=0.5;
    gl_Position=geoProjection[0]*(origin+vec4(-size,size,0,0));
    //fragTextureCoord=geoTopLeftTexture[0];
    EmitVertex();
    gl_Position=geoProjection[0]*(origin+vec4(-size,-size,0,0));
    //fragTextureCoord=geoTopLeftTexture[0]+vec2(0,geoTextureSize[0].y);
    EmitVertex();
    gl_Position=geoProjection[0]*(origin+vec4(size,-size,0,0));
    //fragTextureCoord=geoTopLeftTexture[0]+
    EmitVertex();
    gl_Position=geoProjection[0]*(origin+vec4(size,size,0,0));
    EndPrimitive();
}