
Color WaterColor{0, 100, 205, 255};
Color GrassColor{100, 184, 105, 255};
Color CoolShadow{0, 10, 50, 255};

void Block::Init(int x2, int y2){
	x = x2;
	y = y2;

	seed = Random(0.f, 1.f);

	topColor = GrassColor;

	bottomColor = topColor.Lerp(CoolShadow, .25f);


}

void Block::UpdateHeights(){
	float t = (g_time.time % 1000000) / 1000.f * 0.f + x/10.f + y/4.f;
	// t = (x) * 1.1f;
	z = 0;
	z = (GLfloat)(std::sin(t) * .5f);
	// z = 0;
	z += seed * .2 * .25;
}

void Block::UpdateLighting(){

	topColor = GrassColor;
	// topColor = topColor.Lerp(WaterColor, amtOfWater);

	float fac = 5.0;
	float spread = 2.0;
	float exp = .5;

	Block* rightBlock = g_grid.GetBlock(x + 1, y);
	Block* topBlock = g_grid.GetBlock(x, y + 1);

	// TODO reduce the effect of the seed (have a basez)
	// TODO use the topRight block too
	// TODO modifiable lighting direction? using a texture for a heights and do this in the shader?

	float dh = 0;

	if(rightBlock){
		dh = z - rightBlock->z;
	}
	if(topBlock){
		float dh2 = z - topBlock->z;
		dh = (dh + dh2) / 2;
	}
	
	float adj01 = Clamp(dh, -spread, spread) / spread;
	float adj = adj01 * fac + 1;

	adj = std::pow(adj, exp);

	topColor.Brighten(adj);
}
