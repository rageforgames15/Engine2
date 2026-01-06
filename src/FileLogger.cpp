#include "fmt/base.h"
#include "FileLogger.h"
#include "EnginePrint.h"
#include "Asserts.h"
#include <cstdint>
#include <string>
#include <string_view>
#include <cstring>
#include <array>

#ifdef ERROR
#undef ERROR
#endif

static FileLogger* s_logger = nullptr;

const std::array<const std::string_view, 3> MSGTYPES = {
  "[TRACE] ", "[WARN] ", "[ERROR] "
};

enum class LogType : uint8_t
{
  TRACE, WARN, ERROR
};

inline void Log(
  const std::string_view str,
  const LogType msgType
)
{
  xengine_assert(s_logger != nullptr);
  const std::string_view& currentMsgType 
    = MSGTYPES[static_cast<uint8_t>(msgType)];

  // string allocate at least null terminate
  std::string msg(str.size() + currentMsgType.size(),'\0');
  memcpy(msg.data(), currentMsgType.data(), currentMsgType.size());
  memcpy(msg.data() + currentMsgType.size(), str.data(), str.size());
  s_logger->Write(msg);
}

void FileLogger::Write(std::string_view str)
{
  xengine_print("{}\n", str);
  if(m_isBlocked || m_file == nullptr) return;
  fwrite(str.data(), sizeof(uint8_t), str.size(), m_file);
  fwrite("\n",1,1, m_file);
}

void FileLogger::SetShouldBeBlocked(bool blocked)
{
  m_isBlocked = blocked;
}

void FileLogger::Flush()
{
  if(m_file)
    fclose(m_file);
  m_file = fopen("log.txt","a");
}

bool FileLogger::IsBlocked() const
{
  return m_isBlocked;
}

FileLogger& FileLogger::GetLogger()
{
  xengine_assert(s_logger != nullptr);
  return *s_logger; 
}

FileLogger::FileLogger(bool blockFileLogger)
  : m_file(fopen("log.txt","w")),
    m_isBlocked(blockFileLogger)
{
  s_logger = this;
}

FileLogger::FileLogger()
  : FileLogger(false)
{}

FileLogger::~FileLogger()
{
  s_logger = nullptr;
  if(m_file)
    fclose(m_file);
}

namespace XELogger
{
  void Trace([[maybe_unused]] const std::string_view str)
  {
#   ifndef PRODUCT_BUILD
      Log(str, LogType::TRACE);
#   endif
  }
  
  void Warn(const std::string_view str)
  {
    Log(str, LogType::WARN);
  }
  
  void Error(const std::string_view str)
  {
    Log(str, LogType::ERROR);
  }

  void ErrorAndCrash(const std::string_view str)
  {
    Log(str, LogType::ERROR);
    s_logger->Flush();
    std::abort();
  }
};
