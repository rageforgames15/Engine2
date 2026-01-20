#pragma once
#include <cstdint>
#include <string_view>

// DONT USE THROW

class OpenGLShader
{
public:
  void Use();
  uint32_t GetID();

  OpenGLShader(
    std::string_view vertexShaderFilePath,
    std::string_view fragmentShaderFilePath
  );

  static void UnbindShader();
  ~OpenGLShader();

  OpenGLShader(const OpenGLShader&) = delete;
  void operator=(const OpenGLShader&) = delete;
  OpenGLShader(OpenGLShader&&) = delete;
  void operator=(OpenGLShader&&) = delete;
private:
  uint32_t m_programID;
};
