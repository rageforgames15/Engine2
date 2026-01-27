#define STB_IMAGE_IMPLEMENTATION
#include "Asserts.h"
#include "glad/gl.h"
#include "OpenGL/OpenGLTexture.h"
#include "stb_image.h"
#include <cstdint>
#include "FileLogger.h"
#include "fmt/format.h"

void OpenGLTexture::BindTexture(
  uint32_t textureUnit
)
{
  xengine_assertmsg(textureUnit < 32, "Texture units must be smaller than 32");
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(m_type, m_id);
}

uint32_t OpenGLTexture::GetID() const
{
  return m_id;
}

OpenGLTexture& OpenGLTexture::operator=(OpenGLTexture&& other) noexcept
{
	if (this != &other)
	{
		m_id = m_id;
		m_textureBits = m_textureBits;
		m_textureHeight = m_textureHeight;
		m_textureWidth = m_textureWidth;
		m_type = m_type;
		other.m_id = 0;
		other.m_textureBits = 0;
		other.m_textureHeight = 0;
		other.m_textureWidth = 0;
		other.m_type = 0;
	}
	return *this;
}

OpenGLTexture::OpenGLTexture(OpenGLTexture&& other) noexcept
	: m_id{other.m_id},
	m_type{other.m_type},
	m_textureWidth{other.m_textureWidth},
	m_textureHeight{other.m_textureHeight},
	m_textureBits{other.m_textureBits}
{}

OpenGLTexture::OpenGLTexture(std::string_view path, uint32_t type)
	: m_id{},
	m_type{type},
	m_textureWidth{},
	m_textureHeight{},
	m_textureBits{}
{
  stbi_set_flip_vertically_on_load(true);

  uint8_t* data = stbi_load(
    path.data(),
    &m_textureWidth,
    &m_textureHeight,
    &m_textureBits,
    STBI_rgb_alpha
  );

	if (!data) // RunTime thing
	{
		XELogger::Error(fmt::format("{} not a image. Texture could be safe loaded", path));
		return;
	}

  glGenTextures(1,&m_id);
  glBindTexture(type, m_id);

  glTexImage2D(
    type,
    0,
    GL_RGBA,
    m_textureWidth, m_textureHeight,
    GL_FALSE,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    data
  );

  glGenerateMipmap(type);

  glTexParameteri(type, GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGLTexture::~OpenGLTexture()
{
  glDeleteTextures(1,&m_id);
}

