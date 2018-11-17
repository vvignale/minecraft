
//output the gl position to the fragment shader
varying vec4 position;

void main(void)
{
    position = ftransform();
    gl_Position = position;

}

