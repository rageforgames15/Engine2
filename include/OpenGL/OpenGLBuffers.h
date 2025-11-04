#pragma once
#include <glad/gl.h>
#include <cstddef>
#include <cstdint> // better now, when never

class OpenGLVBO
{
public:
  // dont forget it bind buffer
  void SetData(void* data, size_t size, int mode);
  void Bind();
  static void Unbind();

  void SetAttribute(
    uint32_t index,
    int32_t size,
    GLenum type,
    bool normalize,
    uint32_t stride,
    const void* offset
  );

  OpenGLVBO();
  ~OpenGLVBO();
private:
  uint32_t m_id;
};

class OpenGLVAO
{
public:
  void Bind();
  static void Unbind();

  OpenGLVAO();
  ~OpenGLVAO();
private:
  uint32_t m_id;
};

class OpenGLEBO
{
public:
  void SetData(const uint32_t* indexis, size_t size, uint32_t usage);
  void Bind();
  static void Unbind();

  OpenGLEBO();
  ~OpenGLEBO();

private:
  uint32_t m_id;
};

