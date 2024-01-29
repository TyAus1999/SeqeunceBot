#version 430
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

flat in vec2 geoTopLeftTexture[];
flat in vec2 geoTextureSize[];
flat in mat4 geoProjection[];

flat out vec2 fragTextureCoord;

void main(){
    vec4 origin=gl_in[0].gl_Position;
    float size=1;
    //Top Left
    gl_Position=geoProjection[0]*(origin+vec4(-size,size,0,0));
    fragTextureCoord=geoTopLeftTexture[0];
    EmitVertex();
    //Bottom Left
    gl_Position=geoProjection[0]*(origin+vec4(-size,-size,0,0));
    fragTextureCoord=geoTopLeftTexture[0]+vec2(0,geoTextureSize[0].y);
    EmitVertex();
    //Top Right
    gl_Position=geoProjection[0]*(origin+vec4(size,size,0,0));
    fragTextureCoord=geoTopLeftTexture[0]+vec2(geoTextureSize[0].x,0);
    EmitVertex();
    //Bottom Right
    gl_Position=geoProjection[0]*(origin+vec4(size,-size,0,0));
    fragTextureCoord=geoTopLeftTexture[0]+geoTextureSize[0];
    EmitVertex();
    EndPrimitive();
}