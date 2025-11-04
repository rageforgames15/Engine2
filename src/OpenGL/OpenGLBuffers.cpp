#include "glad/gl.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <cstddef>
#include <cstdint>
#include <fmt/base.h>
#include <iostream>
#include "OpenGL/OpenGLBuffers.h"

static uint32_t s_bindedVBOBuffer{};
static uint32_t s_bindedVAOBuffer{};
static uint32_t s_bindedEBOBuffer{};

// OPENGLVBO
void OpenGLVBO::SetData(void* data, size_t size, int usage)
{
  if(s_bindedVBOBuffer != m_id)
    Bind();

  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
};

void OpenGLVBO::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  s_bindedVBOBuffer = m_id;
}

void OpenGLVBO::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  s_bindedVBOBuffer = 0;
}

void OpenGLVBO::SetAttribute(
  uint32_t index,
  int32_t size,
  uint32_t type,
  bool normalize,
  uint32_t stride,
  const void* offset
)
{
  if(s_bindedVBOBuffer != m_id)
    Bind();

  glVertexAttribPointer(
    index,
    size,
    type,
    normalize,
    stride,
    offset
  );
  glEnableVertexAttribArray(index);
}

OpenGLVBO::OpenGLVBO()
{
  glGenBuffers(1, &m_id);
}

OpenGLVBO::~OpenGLVBO()
{
  if(s_bindedVBOBuffer == m_id)
    Unbind();
  glDeleteBuffers(1, &m_id);
}

// OpenGlVAO
void OpenGLVAO::Bind()
{
  glBindVertexArray(m_id);
}

void OpenGLVAO::Unbind()
{
  glBindVertexArray(0);
  s_bindedVAOBuffer = 0;
}

OpenGLVAO::OpenGLVAO()
{
  glGenVertexArrays(1, &m_id);
}

OpenGLVAO::~OpenGLVAO()
{
  if(s_bindedVAOBuffer == m_id)
    Unbind();
  glDeleteVertexArrays(1, &m_id);
}

//OpenGLEBO

void OpenGLEBO::Bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void OpenGLEBO::Unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLEBO::SetData(const uint32_t* indexis, size_t size, uint32_t usage)
{
  if(s_bindedEBOBuffer != m_id)
    Bind();
  std::cout << glGetError() << '\n';
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexis, usage);
  std::cout << glGetError() << '\n';
}

OpenGLEBO::OpenGLEBO()
{
  glGenBuffers(1, &m_id);
}

OpenGLEBO::~OpenGLEBO()
{
  if(s_bindedEBOBuffer == m_id)
    Unbind();
  glDeleteBuffers(1,&m_id);
}

