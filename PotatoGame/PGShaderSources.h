	#if !defined(PG_SHADER_SOURCE_H)	
#define PG_SHADER_SOURCE_H
//Note(Marc): This file is onyl there for quick editing and make it easy to test shader, you dont have to load the from elsewhere


struct PGMaterial {
	v3 ambient;
	v3 diffuse;
	v3 specular;
	r32 shininess;
};
const PGMaterial Material_Emerald = { v3(0.0215f, 0.1745f, 0.0215f), v3(0.07568f, 0.61424f, 0.07568f), v3(0.633f, 0.727811f, 0.633f), 0.6f*128.f }; //Emerald
const PGMaterial Material_Gold = { v3(0.24725f, 0.1995f, 0.0745f), v3(0.75164f, 0.60648f, 0.22648f), v3(0.628281f, 0.555802f, 0.366065f), 0.4f*128.f }; //Gold
const PGMaterial Material_Obsidian = { v3(0.05375f, 0.05f, 0.06625f), v3(0.18275f, 0.17f, 0.22525f), v3(0.332741f, 0.328634f, 0.346435f), 0.02f*128.f };
const PGMaterial Material_Turquoise = { v3(0.1f, 0.18725f, 0.1745f), v3(0.396f, 0.74151f, 0.69102f), v3(0.297254f, 0.30829f, 0.306678f), 8.8f };
const PGMaterial Material_Copper = { v3(0.19125f, 0.0735f, 0.0225f), v3(0.7038f, 0.27048f, 0.0828f), v3(0.256777f, 0.137622f, 0.086014f), 12.8f };

const PGMaterial Material_Green = { v3(0.01f, 0.01f, 0.0f), v3(0.54f, 0.89f, 0.39f), v3(0.0f, 0.0f, 0.0f), 20.f };
const PGMaterial Material_Brown_1 = { v3(0.0f, 0.01f, 0.01f), v3(0.71f, 0.52f, 0.36f), v3(1.0f, 0.41f, 0.1f), 20.f };
const PGMaterial Material_Brown_2 = { v3(0.0f, 0.01f, 0.01f), v3(0.8f, 0.5f, 0.35f), v3(1.0f, 0.41f, 0.1f), 20.f };
const PGMaterial Material_Blue = { v3(0.01f, 0.01f, 0.0f), v3(0.0f, 0.56f, 0.89f), v3(0.0f, 0.0f, 0.0f), 20.f };
const PGMaterial Material_Gray = { v3(0.01f, 0.0f, 0.01f), v3(0.26f, 0.26f, 0.26f), v3(0.0f, 0.0f, 0.0f), 20.f };

//const PGMaterial Material_Obsidian = ­{  };
//Note(Marc): Be aware, variables order match the same struct in the fragment shader, do not modify 1 without the other
struct PGLight {
	v4 position;
	v4 ambient;
	v4 diffuse;
	v4 specular;
};

static const GLfloat ui_panel_vertex_data[] = {//Center = top left align	
	0.0f, -1.0f, 0.0f, 1.0f,  // Bottom Left 1
	0.0f, 0.0f, 0.0f, 1.0f,  // Top Left 2
	1.0f, 0.0f, 0.0f, 1.0f,  // Top Right 3
	0.0f, -1.0f, 0.0f, 1.0f,   // Bottom Left 4
	1.0f, 0.0f, 0.0f, 1.0f, // Top Right 5
	1.0f, -1.0f, 0.0f, 1.0f // Bottom Right 6
};

static const GLfloat square_vertex_data[] = {
	// Tex 1					//Texture Coords
	-1.0f, -1.0f, 0.0f, 1.0f,  // Bottom Left 1
	-1.0f, 1.0f, 0.0f, 1.0f,  // Top Left 2
	1.0f, 1.0f, 0.0f, 1.0f,  // Top Right 3
	-1.0f, -1.0f, 0.0f, 1.0f,   // Bottom Left 4
	1.0f, 1.0f, 0.0f, 1.0f, // Top Right 5
	1.0f, -1.0f, 0.0f, 1.0f // Bottom Right 6
};


static const GLfloat tree_vertex_data_v3[] = {
	0.0f, -1.0f, 0.4f,			// - 0
	-1.0f, -0.4226497308f, 0.4f,// - 1
	-1.0f, 0.4226497308f, 0.4f,	// - 2
	0.0f, 1.0f, 0.4f,			// - 3
	1.0f, 0.4226497308f, 0.4f,	// - 4
	1.0f, -0.4226497308f, 0.4f,	// - 5

	0.0f, 0.0f, 1.0f,			// - 6

	0.5f, 0.5f, 0.4f,
	-0.5f, 0.5f, 0.4f,
	0.5f, -0.5f, 0.4f,
	-0.5f, -0.5f, 0.4f,

	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,		
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};
	static const GLuint tree_indice_data[] = {
		//Lower hexagone 
		1, 5, 0,
		2, 3, 1,
		4, 5, 3,
		3, 5, 1,
		//Upper tree

		//Wood trunck
	};


static const GLfloat hexagone_vertex_data_v3[] = {
	0.0f, -1.0f, 1.0f, 
	-1.0f, -0.4226497308f, 1.0f, 
	-1.0f, 0.4226497308f, 1.0f,
	0.0f, 1.0f, 1.0f, 
	1.0f, 0.4226497308f, 1.0f,
	1.0f, -0.4226497308f, 1.0f,
	
	0.0f, -1.0f, 0.0f,
	-1.0f, -0.4226497308f,0.0f,
	-1.0f, 0.4226497308f, 0.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 0.4226497308f, 0.0f,
	1.0f, -0.4226497308f, 0.0f
};

static const GLuint hexagone_indice_data[] = {
	//Top hexagone
	0, 5, 1,
	1, 3, 2,
	3, 5, 4,
	1, 5, 3,
	//Square side 1
	0, 1, 6, //Upper
	1, 7 ,6,
	//Square side 2
	1, 2, 7,
	2, 8, 7,
	//Square side 3
	2, 3, 8,
	3, 9 ,8,
	//Square side 4
	3, 4, 9,
	4, 10, 9,
	//Square side 5
	4, 5, 10,
	5, 11, 10,
	//Square side 6
	5, 0, 11,
	0, 6, 11,
	//Lower hexagone 
	7, 11, 6,
	8, 9, 7,
	10, 11, 9,
	9, 11, 7,
};
static const GLfloat center_align_texture_vertices[] = {
	// Positions			//Texture Coords
	-0.5f, 0.5f, 0.0f, 1.f,		1.0f, 0.0f,	// Bottom Right
	0.5f, -0.5f, 0.0f, 1.f,		0.0f, 0.0f,	// Bottom Left
	-0.5f, -0.5f, 0.0f, 1.f,	1.0f, 1.0f,	// Top Right
	0.5f, 0.5f, 0.0f, 1.f,		0.0f, 1.0f		// Top Left 
};
static const GLfloat top_left_align_texture_vertices[] = {
	// Positions			//Texture Coords
	1.f, 1.f, 0.0f, 1.f,	1.0f, 0.0f,	// Bottom Right
	0.f, 1.f, 0.0f, 1.f,	0.0f, 0.0f,	// Bottom Left
	1.0f, 0.0f, 0.0f, 1.f,  1.0f, 1.0f,	// Top Right
	0.0f, 0.0f, 0.0f, 1.f,  0.0f, 1.0f		// Top Left 
};

static const GLuint texture_indices[] = {  // Note that we start from 0!
	3, 1, 0,   // First Triangle
	0, 2, 3    // Second Triangle
};

static const GLfloat cube_vertex_normal[] = {
	-1.0f, -1.0f, -1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Left-1
	- 1.0f, -1.0f, 1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Left-1
	- 1.0f, 1.0f, 1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Left-1
	1.0f, 1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,//	Back-1
	- 1.0f, -1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,//	Back-1
	- 1.0f, 1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,//	Back-1
	1.0f, -1.0f, 1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Bottom-1
	-1.0f, -1.0f, -1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Bottom-1
	1.0f, -1.0f, -1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Bottom-1
	1.0f, 1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,//	Back-2
	1.0f, -1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,//	Back-2
	-1.0f, -1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,//	Back-2
	-1.0f, -1.0f, -1.0f, 1.0f,   0.0f, -1.0f, 0.0f,//	Left-2
	-1.0f, 1.0f, 1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Left-2
	-1.0f, 1.0f, -1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Left-2
	1.0f, -1.0f, 1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Bottom-2
	-1.0f, -1.0f, 1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Bottom-2
	-1.0f, -1.0f, -1.0f, 1.0f,	 0.0f, -1.0f, 0.0f,//	Bottom-2
	-1.0f, 1.0f, 1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,//	Front-1
	-1.0f, -1.0f, 1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,//	Front-1
	1.0f, -1.0f, 1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,//	Front-1
	1.0f, 1.0f, 1.0f, 1.0f,		 1.0f, 0.0f, 0.0f,//	Right-1
	1.0f, -1.0f, -1.0f, 1.0f,	 1.0f, 0.0f, 0.0f,//	Right-1
	1.0f, 1.0f, -1.0f, 1.0f,	 1.0f, 0.0f, 0.0f,//	Right-1
	1.0f, -1.0f, -1.0f, 1.0f,	 1.0f, 0.0f, 0.0f,//	Right-2
	1.0f, 1.0f, 1.0f, 1.0f,		 1.0f, 0.0f, 0.0f,//	Right-2
	1.0f, -1.0f, 1.0f, 1.0f,	 1.0f, 0.0f, 0.0f,//	Right-2
	1.0f, 1.0f, 1.0f, 1.0f,		 0.0f, 1.0f, 0.0f,//	Top-1
	1.0f, 1.0f, -1.0f, 1.0f,	 0.0f, 1.0f, 0.0f,//	Top-1
	-1.0f, 1.0f, -1.0f, 1.0f,	 0.0f, 1.0f, 0.0f,//	Top-1
	1.0f, 1.0f, 1.0f, 1.0f,		 0.0f, 1.0f, 0.0f,//	Top-2
	-1.0f, 1.0f, -1.0f, 1.0f,	 0.0f, 1.0f, 0.0f,//	Top-2
	-1.0f, 1.0f, 1.0f, 1.0f,	 0.0f, 1.0f, 0.0f,//	Top-2
	1.0f, 1.0f, 1.0f, 1.0f,		 0.0f, 0.0f, 1.0f,//	Front-2
	-1.0f, 1.0f, 1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,//	Front-2
	1.0f, -1.0f, 1.0f, 1.0f,	 0.0f, 0.0f, 1.0f//	Front-2
};

static const GLfloat cube_vertex_data2[] = {
	-1.0f, -1.0f, -1.0f, 1.0f, // triangle 1 : begin
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f, -1.0f, 1.0f, // triangle 2 : begin
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f, // triangle 2 : end
	1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f
};
static const GLfloat axes_vertex_data[] = {
	// Tex 1						//Line color
	10000.0f, 0.0f, 0.0f, 1.0f,		1.f, 0.f, 0.f, 1.f,// x axis
	-10000.0f, 0.0f, 0.0f, 1.0f,	1.f, 0.f, 0.f, 1.f,  // neg x axis
	0.0f, 10000.0f, 0.0f, 1.0f,		0.f, 1.f, 0.f, 1.f,// y axis
	0.0f, -10000.0f, 0.0f, 1.0f,	0.f, 1.f, 0.f, 1.f,// neg y axis
	0.0f, 0.0f, 10000.0f, 1.0f,		0.f, 0.f, 1.f, 1.f,// z axis
	0.0f, 0.0f, -10000.0f, 1.0f,	0.f, 0.f, 1.f, 1.f// neg z axis
};
static const GLfloat marker_vertex_data[] = {
	// Tex 1						//Line color
	1.f, 0.0f, 0.0f, 1.0f, 1.f, 0.f, 0.f, 1.f,// x axis
	0.f, 0.0f, 0.0f, 1.0f, 1.f, 0.f, 0.f, 1.f,  // neg x axis
	0.0f, 1.f, 0.0f, 1.0f, 0.f, 1.f, 0.f, 1.f,// y axis
	0.0f, 0.f, 0.0f, 1.0f, 0.f, 1.f, 0.f, 1.f,// neg y axis
	0.0f, 0.0f, 1.f, 1.0f, 0.f, 0.f, 1.f, 1.f,// z axis
	0.0f, 0.0f, 0.f, 1.0f, 0.f, 0.f, 1.f, 1.f// neg z axis
};
static const GLfloat panel_vertices[] = {
	// Positions			
	1.0f, 0.0f, 0.0f,	// Bottom Right
	0.0f, 0.0f, 0.0f,	// Bottom Left
	1.f, 1.f, 0.0f,		// Top Right
	0.f, 1.f, 0.0f,		// Top Left 
};
static const GLuint panel_indices[] = {  // Note that we start from 0!
	3, 0, 1,   // First Triangle
	0, 3, 2    // Second Triangle
};
static const GLfloat text_vertices_rev[] = {
	// Positions			//Texture Coords
	1.f, 1.f, 0.0f, 1.f, 1.0f, 1.0f,	// Bottom Right
	0.f, 1.f, 0.0f, 1.f, 0.0f, 1.0f,	// Bottom Left
	1.0f, 0.0f, 0.0f, 1.f, 1.0f, 0.0f, 	// Top Right
	0.0f, 0.0f, 0.0f, 1.f, 0.0f, 0.0f 		// Top Left 
};
static const GLuint text_quad_indices[] = {  // Note that we start from 0!
	3, 1, 0,   // First Triangle
	0, 2, 3    // Second Triangle
};

#define PG_SHADER(shader_text) static shader_text
#define GLSL330(src) "#version 330 core\n" #src 
PG_SHADER(const char* tile_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;
	layout(location = 1) in vec2 tex_coord;

	uniform mat4 Translate;
	uniform mat4 Scale;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	out vec2 Tex_Coord;
		
	void main() {
		Tex_Coord = tex_coord;
		gl_Position = WorldProjection * WorldView * (Translate* Scale) * vertex_position;
	}
));
PG_SHADER(const char* tile_fragment_shader = GLSL330(	
	uniform sampler2D Texture_Sample;

	in vec2 Tex_Coord;
	out vec4 color;

	void main() {
		color = texture(Texture_Sample, Tex_Coord).rgba;
	}
));
PG_SHADER(const char* ui_panel_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;

	uniform mat4 Translate;
	uniform mat4 Scale;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	void main() {
		gl_Position = GUIProjection * (Translate* Scale) * vertex_position;
	}
));
PG_SHADER(const char* texture_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;
	layout(location = 1) in vec2 tex_coord;
	
	uniform mat4 Translate;
	uniform mat4 Scale;
	uniform mat4 Rotate;

	out vec2 Tex_Coord;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	void main() {
		gl_Position = GUIProjection * (Translate*Rotate* Scale) * vertex_position;
		Tex_Coord = tex_coord;
	}
));
PG_SHADER(const char* texture_fragment_shader = GLSL330(
	in vec2 Tex_Coord;
	out vec4 color;

	uniform sampler2D Texture_Sample;
	uniform vec4 Color_Channel;
	void main() {
		color = Color_Channel*texture(Texture_Sample, Tex_Coord).rgba;
	}
));
PG_SHADER(const char* simple_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;

	uniform mat4 Translate;
	uniform mat4 Scale;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	void main() {
		gl_Position = WorldProjection  * WorldView * (Translate* Scale) * vertex_position;
	}
));

PG_SHADER(const char* hexagone_vertex_shader = GLSL330(
	layout(location = 0) in vec3 vertex_position;

	uniform mat4 Translate;
	uniform mat4 Scale;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	void main() {
		gl_Position = WorldProjection  * WorldView * (Translate* Scale) * vec4(vertex_position, 1.f);
	}
	
));
PG_SHADER(const char* text_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;
	layout(location = 1) in vec2 uv_position;

	uniform mat4 Translate;
	uniform mat4 Scale;

	out vec2 uv_tex_possition;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	void main() {
		gl_Position = GUIProjection * (Translate* Scale) * vertex_position;
		uv_tex_possition = uv_position;
	}
));
PG_SHADER(const char* text_fragment_shader = GLSL330(
	in vec2 uv_tex_possition;
	out vec4 color;

	uniform sampler2D text_texture;
	uniform vec4 TextColor;

	void main() {
		vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text_texture, uv_tex_possition).r);
		color = TextColor*sampled;
	}
));
PG_SHADER(const char* axis_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;
	layout(location = 1) in vec4 vertex_color;
	
	uniform mat4 Translate;

	out vec4 FragColor;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};

	void main() {
		FragColor = vertex_color;
		gl_Position = WorldProjection  * WorldView * Translate * vertex_position;
	}
));

PG_SHADER(const char* FragShaderColor4fIn = GLSL330(
	in vec4 FragColor;
	out vec4 color;
	
	void main() {
		color = FragColor;
	}
));

PG_SHADER(const char* FragShaderColor4fUnif = GLSL330(
	uniform vec4 FragColor;
	out vec4 color;
	
	void main() {
		color = FragColor;
	}
));
PG_SHADER(const char* light_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;
	layout(location = 1) in vec3 vertex_normal;

	uniform mat4 Translate;
	uniform mat4 Scale;

	out vec3 Normal;
	out vec3 FragPos;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};


	void main() {

		gl_Position = WorldProjection  * WorldView * (Translate* Scale) * vertex_position;
			FragPos = vec3(WorldView*(Translate * Scale) * vertex_position);
		Normal = mat3(transpose(inverse(WorldView *  Translate * Scale))) * vertex_normal;
	}
));
//Note(Marc): Main methode for model with materiel
PG_SHADER(const char* model_vertex_shader = GLSL330(
	layout(location = 0) in vec4 vertex_position;
	layout(location = 1) in vec3 vertex_normal;
	layout(location = 2) in vec3 ambient;
	layout(location = 3) in vec3 diffuse;
	layout(location = 4) in vec3 specular;
	layout(location = 5) in vec4 shininess;

	struct PGMaterial {
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	};

	uniform mat4 Translate;
	uniform mat4 Scale;

	out vec3 Normal;
	out vec3 FragPos;
	
	out PGMaterial Matl;

	

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};


	void main() {
		Matl.ambient = ambient;
		Matl.diffuse = diffuse;
		Matl.specular = specular;
		Matl.shininess = shininess.x;
		//Note(Marc): this next line should be uptimise so 1 less call is made
		gl_Position = WorldProjection  * WorldView * (Translate* Scale) * vertex_position;
		FragPos = vec3(WorldView*(Translate * Scale) * vertex_position);
		Normal = mat3(transpose(inverse(WorldView *  Translate * Scale))) * vertex_normal;
	}
));
PG_SHADER(const char* Model_FragShader = GLSL330(
	struct PGMaterial {
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	};
	struct PGLight {
		vec4 position;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	};
	

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};
	layout(std140) uniform SceneAdvanceLightData_UBO
	{
		PGLight Light;
	};
		
	in vec3 Normal;
	in vec3 FragPos;
	in PGMaterial Matl;

	out vec4 color;

	void main() {
		// Ambient
		vec3 ambient = vec3(Light.ambient) * Matl.ambient;

		// Diffuse 
		vec3 LightPos = vec3(WorldView * Light.position);
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(LightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0f);
		vec3 diffuse = vec3(Light.diffuse) * (diff * Matl.diffuse);

		vec3 viewDir = normalize(-FragPos); // The viewer is at(0, 0, 0) so viewDir is(0, 0, 0) - Position = > -Position
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), Matl.shininess);
		vec3 specular = vec3(Light.specular) * (spec * Matl.specular);

		//Combine each	colors
		color = vec4((ambient + diffuse + specular), 1.0f);
		
	}
));
PG_SHADER(const char* FragShaderMaterializeLight = GLSL330(
	struct PGMaterial {
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	};
	struct PGLight {
		vec4 position;
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
	};
	uniform PGMaterial Material;

	
	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};
	layout(std140) uniform SceneAdvanceLightData_UBO
	{
		PGLight Light;
	};

	in vec3 FragPos;
	in vec3 Normal;

	out vec4 color;	

	void main() {
		// Ambient
		vec3 ambient = vec3(Light.ambient) * Material.ambient;

		// Diffuse 
		vec3 LightPos = vec3(WorldView * Light.position);
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(LightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0f);
		vec3 diffuse = vec3(Light.diffuse) * (diff * Material.diffuse);

		vec3 viewDir = normalize(-FragPos); // The viewer is at(0, 0, 0) so viewDir is(0, 0, 0) - Position = > -Position
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.shininess);
		vec3 specular = vec3(Light.specular) * (spec * Material.specular);

		//Combine each	colors
		color = vec4((ambient + diffuse + specular), 1.0f);

	}
));	


//This shader is no longer use
PG_SHADER(const char* FragShaderBasicLight = GLSL330(
	in vec3 FragPos;
	in vec3 Normal;

	uniform vec4 ObjectColor;

	layout(std140) uniform Renderer_UBO
	{
		mat4 WorldProjection;
		mat4 WorldView;
		mat4 GUIProjection;
		vec4 CenterOfFog;
	};
	layout(std140) uniform SceneLightData_UBO
	{
		vec4 light_possition;
		vec4 light_color;
	};
	out vec4 color;

	void main() {

		vec3 _light_color = vec3(light_color.x, light_color.y, light_color.z);
		// Ambient
		float ambientStrength = 0.1f;
		vec3 ambient = ambientStrength * _light_color;

			
		// Diffuse 
		vec3 LightPos = vec3(WorldView * light_possition);
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(LightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * _light_color;

		// Specular
		float specularStrength = 0.5f;
		vec3 viewDir = normalize(-FragPos); // The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * _light_color;

		vec3 result = (ambient + diffuse + specular);
		color = vec4(result, 1.0f)* ObjectColor;

	}
));


#endif