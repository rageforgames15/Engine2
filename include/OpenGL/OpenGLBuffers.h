#pragma once
#include <glad/gl.h>
#include <cstddef>
#include <cstdint> // better now, when never

class OpenGLVBO
{
public:
  // dont forget it bind buffer
  void SetData(void* data, size_t size, uint32_t mode);
  void Bind();
  static void Unbind();

  void SetAttribute(
    uint32_t index,
    int32_t size,
    GLenum type,
    bool normalize,
    uint32_t stride,
    uint64_t offset
  );

  OpenGLVBO();
  ~OpenGLVBO();

  OpenGLVBO(const OpenGLVBO&) = delete;
  void operator=(const OpenGLVBO&) = delete;
  OpenGLVBO(OpenGLVBO&&) = delete;
  void operator=(OpenGLVBO&&) = delete;
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

  OpenGLVAO(const OpenGLVAO&) = delete;
  void operator=(const OpenGLVAO&) = delete;
  OpenGLVAO(OpenGLVAO&&) = delete;
  void operator=(OpenGLVAO&&) = delete;
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

  OpenGLEBO(const OpenGLEBO&) = delete;
  void operator=(const OpenGLEBO&) = delete;
  OpenGLEBO(OpenGLEBO&&) = delete;
  void operator=(OpenGLEBO&&) = delete;
private:
  uint32_t m_id;
};
