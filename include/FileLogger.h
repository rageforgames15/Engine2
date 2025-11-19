#pragma once
#include <cstdio>
#include <string_view>

class FileLogger
{
public:

  void Write(std::string_view str);
  void SetShouldBeBlocked(bool blocked);
  
  // just reopen file, nothing more
  void Flush();
  
  const bool IsBlocked() const;
  static FileLogger& GetLogger();

  FileLogger(bool blockFileLogger);
  FileLogger();
  ~FileLogger();

  FileLogger(const FileLogger&) = delete;
  void operator=(const FileLogger&) = delete;
private:
  FILE* m_file;
  bool m_isBlocked;
};

namespace XELogger
{
  void Trace(const std::string_view str);
  void Warn(const std::string_view str);
  void Error(const std::string_view str);
  void ErrorAndCrash(const std::string_view str);
};