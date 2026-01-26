#include "glad/gl.h"
#include "FileLogger.h"
#include "EnginePrint.h"
#include "OpenGL/OpenGLShader.h"
#include <expected>
#include <string>
#include <string_view>
#include <utility>
#include <cstdio>
#include "FileIO.h"
#include <cstdint>

enum class ShaderType : uint32_t
{
  VERTEX = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER
};

[[nodiscard]]
std::expected<uint32_t, std::string> CompileShader(
  const std::string_view shaderCode,
  ShaderType shaderType
)
{
  uint32_t shaderID = glCreateShader(std::to_underlying(shaderType));
  const char* data = shaderCode.data();
  
  glShaderSource(
    shaderID,
    1,
    &data,
    nullptr
  );

  glCompileShader(shaderID);

  int32_t result{};
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
  if(!result)
  {
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &result);
    std::string msg(static_cast<uint64_t>(result), '\0');
    glGetShaderInfoLog(shaderID, result, nullptr, msg.data());
    return std::unexpected(std::move(msg));
  }

  return shaderID;
}

[[nodiscard]]
std::expected<uint32_t, std::string> CreateProgram(
  std::string_view vertexShaderSource,
  std::string_view fragmentShaderSource
)
{
  auto vertexShader 
    = CompileShader(vertexShaderSource, ShaderType::VERTEX);
  auto fragmentShader 
    = CompileShader(fragmentShaderSource, ShaderType::FRAGMENT);

  if(!vertexShader.has_value()) 
    return vertexShader;

  if(!fragmentShader.has_value()) 
    return fragmentShader;

  uint32_t vertexShaderID = vertexShader.value();
  uint32_t fragmentShaderID = fragmentShader.value();

  uint32_t programID = glCreateProgram();
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);

  glLinkProgram(programID);

  int32_t result{};
  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  if(!result)
  {
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &result);
    std::string msg(static_cast<uint64_t>(result), '\0');
    glGetProgramInfoLog(programID, result, nullptr, msg.data());
    return std::unexpected(std::move(msg));
  }

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

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

OpenGLShader::OpenGLShader(
  std::string_view vertexShaderFilePath,
  std::string_view fragmenShaderFilePath
) : m_programID(0)
{
  FILEERROR fileError;
  XEngineFile vertexFile(
    vertexShaderFilePath,
    std::to_underlying(FILEOPENFLAGS::READ),
    fileError
  );
  if(fileError != FILEERROR::NONE)
  {
    std::string msg("Failed to open file: ");
    msg += vertexShaderFilePath;
    XELogger::Error(msg);
  }
  std::string vertexSourceCode = vertexFile.ReadAllData();
  XEngineFile fragmentFile(
    fragmenShaderFilePath,
    std::to_underlying(FILEOPENFLAGS::READ),
    fileError
  );
  if(fileError != FILEERROR::NONE)
  {
    std::string msg("Failed to open file: ");
    msg += fragmenShaderFilePath;
    XELogger::Error(msg);
  }
  std::string fragmentSourceCode = fragmentFile.ReadAllData();

  auto programRes = CreateProgram(vertexSourceCode, fragmentSourceCode);
  if(!programRes.has_value()) XELogger::Error(programRes.error());
  else m_programID = programRes.value();
}

OpenGLShader::~OpenGLShader()
{
  glDeleteProgram(m_programID);
}
