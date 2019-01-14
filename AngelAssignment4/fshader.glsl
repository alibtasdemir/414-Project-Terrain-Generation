#version 440 core

//in vec4 ourColor;
//in vec2 TexCoord;

//out vec4 color;

//uniform sampler2D theTexture;

//void main() {
//	color = texture(theTexture, TexCoord);
//}

varying vec3 N;
varying vec3 v;

void main(void)
{
   vec3 L = normalize(gl_LightSource[0].position.xyz - v);   
   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);  
   Idiff = clamp(Idiff, 0.0, 1.0); 

   gl_FragColor = Idiff;
}
