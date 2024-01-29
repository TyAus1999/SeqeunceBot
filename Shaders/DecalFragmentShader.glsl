#version 430
out vec4 FragColour;

uniform sampler2D tex;

in vec2 fragTextureCoord;

void main(){
    //vec4 texColour=texture(tex, fragTextureCoord);
    //if(texColour.a<0.05)
        //discard;
    //FragColour=texColour;
    FragColour=vec4(1,0,0,1);
}