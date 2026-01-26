#pragma once
#include <cstdio>
#include <string_view>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4820)
#endif

class FileLogger
{
public:

  void Write(std::string_view str);
  void SetShouldBeBlocked(bool blocked);
  
  // just reopen file, nothing more
  void Flush();
  
  bool IsBlocked() const;
  static FileLogger& GetLogger();

  FileLogger(bool blockFileLogger);
  FileLogger();
  ~FileLogger();

  FileLogger(const FileLogger&) = delete;
  void operator=(const FileLogger&) = delete;
  FileLogger(FileLogger&&) = delete;
  void operator=(FileLogger&&) = delete;
private:
  FILE* m_file = nullptr;
  bool m_isBlocked = false;
};

namespace XELogger
{
  void Trace(const std::string_view str);
  void Warn(const std::string_view str);
  void Error(const std::string_view str);
  void ErrorAndCrash(const std::string_view str);
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif