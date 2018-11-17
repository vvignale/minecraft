varying vec4 position;
uniform float camX;
uniform float camY;
uniform float camZ;

void main(void)
{

//    vec2 tCoord = gl_FragCoord.xy/viewport;
//    vec4 image = texture(litImage, tCoord);
//    vec4 position = texture(positions, tCoord);

    vec3 camPos = vec3(camX,camY,camZ);
    float distance = length(position.xyz - camPos);

    vec4 fogColor = vec4(.27,.27,.32,1);

    // exponential interpolation
    float b = .05;
    float interpVal = 1.0/(exp(b*distance)) + .2;
    clamp(interpVal, 0.0, 1.0);

//    gl_FragColor = vec4((image*(interpVal) + fogColor*(1.0-interpVal)).xyz,1);




        gl_FragColor = position;
}

