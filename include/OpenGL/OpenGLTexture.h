#pragma once
#include <cstdint>
#include <string_view>

class OpenGLTexture
{
public:
  void BindTexture(uint32_t textureUnit);
  uint32_t GetID() const;

  OpenGLTexture(std::string_view path, uint32_t type);
  ~OpenGLTexture();

  OpenGLTexture(const OpenGLTexture&) = delete;
  void operator=(const OpenGLTexture&) = delete;
  OpenGLTexture(OpenGLTexture&&) = delete;
  void operator=(OpenGLTexture&&) = delete;
private:
  uint32_t m_id;
  uint32_t m_type;
  int32_t m_textureWidth;
  int32_t m_textureHeight;
  int32_t m_textureBits;
};
