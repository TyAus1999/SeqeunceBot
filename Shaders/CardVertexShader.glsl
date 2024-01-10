#version 430
layout(location=0)in vec3 startLocation;
//layout(location=1)in vec3 targetLocation;
//layout(location=2)in vec3 directionNormalized;
//layout(location=3)in float timeToReachTarget;
//layout(location=4)in float timeOfMovementOrder;
//layout(location=5)in float moveSpeed;

uniform mat4 projection;
uniform mat4 view;
uniform float currentTime;

mat4 getTranslationModel(vec3 loc){
    mat4 toRet=mat4(1.f);//Init to identity matrix
    toRet[3]=vec4(loc,1.0);//Set the translation params
    return toRet;
}

vec3 getCurrentPosition(vec3 start,vec3 end,vec3 direction, float speed, float timeReach,float timeMoveOrder){
    if(currentTime>=timeReach)
        return end;
    float timeDiff=currentTime-timeMoveOrder;
    float distTravel=timeDiff*speed;
    return start+(direction*distTravel);
}

void main(){
    //vec3 loc=getCurrentPosition(startLocation, targetLocation,directionNormalized, moveSpeed, timeToReachTarget, timeOfMovementOrder);
    //mat4 model=getTranslationModel(loc);
    gl_Position=vec4(startLocation, 1);
}