
Texture* Texture::currTexture = nullptr;

void Texture::Init(const char* filename){
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* pixels = stbi_load(filename, &width, &height, &numChannels, 4);
	assert(pixels != nullptr);
	printf("Load image: %s size: %dx%d channels: %d data: %p \n", filename, width, height, numChannels, pixels);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Use(){
	if(currTexture != this){
		if(currTexture)
			currTexture->Unuse();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		boundUnit = 0;
		
		currTexture = this;		
	}
}

void Texture::Unuse(){
	boundUnit = -1;
}

