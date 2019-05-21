#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 camera;
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec4 Ocolor;
}vs_out;

void main()
{
  gl_Position =  pr_matrix * camera * ml_matrix * position;
  vs_out.position = ml_matrix * position;
  vs_out.Ocolor = color;
}
