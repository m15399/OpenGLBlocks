
Game* g_game = nullptr;


// Temporary location...

// TODO
// We need to sort different draw calls into different buckets
// One VertexData per type, sort by:
// - DrawType (GL_LINES, GL_TRIANGLES)
//   - Shader
//     - Texture
//
// Alternatively draw everything in order
// Switch to a new VertexData when any gl state switches

// TODO
// overlapping textures
// interface like drawSquare, ...
// squares can be drawn with texture shader, just need a white square
// tex coords can be ushorts

void PushSquare(VertexData& v, float x, float y, float size){
	float s2 = size/2;
	float x1 = x - s2;
	float y1 = y - s2;
	float x2 = x + s2;
	float y2 = y + s2;

	// GLubyte r = (GLubyte) Random(0, 255);
	// GLubyte g = (GLubyte) Random(0, 255);
	// GLubyte b = (GLubyte) Random(0, 255);
	GLubyte r = 255;
	GLubyte g = 255;
	GLubyte b = 255;

	v.PushVertex(x1, y1, 0, 0, 1);
	v.PushVertex(x2, y1, 0, 1, 1);
	v.PushVertex(x1, y2, 0, 0, 0);
	v.PushVertex(x1, y2, 0, 0, 0);
	v.PushVertex(x2, y1, 0, 1, 1);
	v.PushVertex(x2, y2, 0, 1, 0);

	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
}

Texture tex;
VertexData v;

void Game::Init(){
	tex.Init("pup.png");
	g_camera.mode = Camera::Mode::TopDown;
}

void Game::Update(){
	g_camera.CenterOn(glm::vec3{});
}


void Game::Draw(){
	glDisable(GL_DEPTH_TEST);

	Mesh m;
	m.Init();
	float s = .5f;
	float spacing = s * std::sin(time());
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			PushSquare(v, i * spacing, j * spacing, s);
		}
	}
	v.SendToMesh(m);
	v.Clear();

	m.Draw(g_shaders.basic_color_tex, glm::mat4(1.0f), Color(255, 255, 255, 255).ToVec4(), &tex);

	glEnable(GL_DEPTH_TEST);

}
