#define STB_IMAGE_IMPLEMENTATION
#include "Asserts.h"
#include "glad/gl.h"
#include "OpenGL/OpenGLTexture.h"
#include "stb_image.h"
#include <cstdint>

static OpenGLTexture* s_bindedTextures[32];
static uint8_t s_currentUnit{};

void OpenGLTexture::BindTexture(
  uint8_t textureUnit
)
{
  xengine_assertmsg(textureUnit < 32, "Texture units must be smaller than 32");
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(m_type, m_id);
  s_currentUnit = textureUnit;
  s_bindedTextures[textureUnit] = this;
}

uint32_t OpenGLTexture::GetID() const
{
  return m_id;
}

OpenGLTexture::OpenGLTexture(std::string_view path, uint32_t type)
  : m_type(type)
{
  stbi_set_flip_vertically_on_load(true);

  uint8_t* data = stbi_load(
    path.data(),
    &m_textureWidth,
    &m_textureHeight,
    &m_textureBits,
    STBI_rgb_alpha
  );

  xengine_assert(data != nullptr); // Debuger thing

  if(!data) // RunTime thing
    return;

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

  glTexParameteri(type, GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
  glTexParameteri(type, GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glGenerateMipmap(type);
  if(s_bindedTextures[s_currentUnit])
    glBindTexture(
      s_bindedTextures[s_currentUnit]->m_type,
      s_bindedTextures[s_currentUnit]->m_id
    );

  stbi_image_free(data);
}

OpenGLTexture::~OpenGLTexture()
{
  glDeleteTextures(1,&m_id);
  for(size_t i{}; i < 32; ++i)
  {
    if(s_bindedTextures[i] == this)
    {
      s_bindedTextures[i] = nullptr;
      break;
    }
  }
}

