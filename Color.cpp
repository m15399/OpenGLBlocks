
Color::Color(){

}

Color::Color(GLubyte r2, GLubyte g2, GLubyte b2, GLubyte a2){
	r = r2;
	g = g2;
	b = b2;
	a = a2;
}

GLubyte& Color::operator[](int i){
	GLubyte* ptr = &r + i;
	return *ptr;
}

Color Color::operator*(float v){
	return Color{
		(GLubyte) (r * v),
		(GLubyte) (g * v),
		(GLubyte) (b * v),
		(GLubyte) (a * v),
	};
}

void Color::Set(GLubyte r2, GLubyte g2, GLubyte b2, GLubyte a2){
	r = r2;
	g = g2;
	b = b2;
	a = a2;
}

Color Color::Lerp(const Color& other, float t){
	return Color(
		::Lerp(r, other.r, t),
		::Lerp(g, other.g, t),
		::Lerp(b, other.b, t),
		::Lerp(a, other.a, t));
}

// TODO have a current light/sky color for better effect
void Color::Brighten(float amt){
	for(int i = 0; i < 3; i++)
		(*this)[i] = (GLubyte)(int)(std::round(Clamp(amt * (*this)[i], 0.f, 254.99f)));
}

glm::vec4 Color::ToVec4(){
	return glm::vec4((GLfloat) r / 255.0f, (GLfloat) g / 255.0f, (GLfloat) b / 255.0f, (GLfloat) a / 255.0f);
}
