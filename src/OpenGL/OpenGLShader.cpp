#include "glad/gl.h"
#include "OpenGL/OpenGLShader.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string_view>
#include <expected>
#include <string>
#include "fmt/base.h"
#include "fmt/core.h"
#include <filesystem>
#include "FileLogger.h"

std::expected<uint32_t, std::string> CompileShader(
  std::string_view shaderSource,
  uint32_t type
)
{
  uint32_t shader = glCreateShader(type);
  const char* sourcePtr = shaderSource.data();
  glShaderSource(shader, 1, &sourcePtr, NULL);
  glCompileShader(shader);
  int32_t res;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
  if(!res)
  {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &res);
    std::string errorMsg(res, '\0');
    glGetShaderInfoLog(shader, res, nullptr, errorMsg.data());
    return std::unexpected(std::move(errorMsg));
  }
  
  return shader;
}

std::expected<uint32_t, std::string> CreateProgram(
  std::string_view vertexShaderCode,
  std::string_view fragmentShaderCode
)
{
  auto vertexShaderRes
    = CompileShader(vertexShaderCode, GL_VERTEX_SHADER)
    .or_else([](const std::string& error) {
        // Current time we print it. Later save it to log file 
        XELogger::ErrorAndCrash(error);
        return std::expected<uint32_t, std::string>{0};
      }
    );

  auto fragmentShaderRes
    = CompileShader(fragmentShaderCode, GL_FRAGMENT_SHADER)
    .or_else([](const std::string& error) {
        XELogger::ErrorAndCrash(error);
        return std::expected<uint32_t, std::string>{0};
      }
    );

  uint32_t vertexShaderID = vertexShaderRes.value();
  uint32_t fragmentShaderID = fragmentShaderRes.value();

  uint32_t programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  int32_t res;
  glGetProgramiv(programID, GL_LINK_STATUS, &res);
  
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  if(!res)
  {
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &res);
    std::string msg(res, '\0');
    glGetProgramInfoLog(programID, res, nullptr, msg.data());
    return std::unexpected(std::move(msg));
  }  

  return programID;
}

void OpenGLShader::Use()
{
  glUseProgram(m_programID);
}

uint32_t OpenGLShader::GetID()
{
  return m_programID;
}

std::string GetBinaryDataFromFile(std::string_view filePath)
{
  FILE* file = fopen(filePath.data(), "rb");
  if(!file)
  {
    perror("Failed to open file");
    return "";
  }
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  std::string data(size, '\0');
  fread(data.data(), sizeof(char), size, file);

  fclose(file);

  return data;
}

void OpenGLShader::UnbindShader()
{
  glUseProgram(0);
}

OpenGLShader::OpenGLShader(
  std::string_view vertexShaderFilePath,
  std::string_view fragmentShaderFilePath
)
{
  std::string vertexShaderSrcCode
    = GetBinaryDataFromFile(vertexShaderFilePath);
  std::string fragmentShaderSrcCode
    = GetBinaryDataFromFile(fragmentShaderFilePath);

  auto programRes = CreateProgram(
    vertexShaderSrcCode,
    fragmentShaderSrcCode
  );

  if(!programRes)
  {
    XELogger::Error(fmt::format("Failed to create shader program, {}", programRes.error()));
    return;
  }
  m_programID = programRes.value();
}

OpenGLShader::~OpenGLShader()
{
  glDeleteProgram(m_programID);
}
