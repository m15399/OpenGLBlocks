
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <chrono>
#include <cstdlib>

// Only works on Mac...
#include <SDL2/SDL.h>
#include <OpenGL/gl.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lib/stb_image.h"

#include "Camera.h"
#include "Color.h"
#include "Game.h"
#include "Globals.h"
#include "Input.h"
#include "Shader.h"
#include "Texture.h"
#include "Time.h"
#include "Utils.h"
#include "Window.h"
#include "Mesh.h"
#include "Primitives.h"
#include "VertexData.h"

#include "GridGame/GridGame.h"
