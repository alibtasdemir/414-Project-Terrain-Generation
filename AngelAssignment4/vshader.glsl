#version 440 core

//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 tex;

//out vec4 ourColor;
//out vec2 TexCoord;

//uniform mat4 model;
//uniform mat4 projection;
//uniform mat4 view;

//void main() {
//	gl_Position = (projection) * (view) * (model) * vec4(aPos, 1.0);
//	ourColor = vec4(clamp(aPos, 0.0f, 1.0f), 1.0f);
//	TexCoord = tex;
//}

varying vec3 N;
varying vec3 v;

void main(void)
{

   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
  