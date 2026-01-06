#pragma once
#include <cstdio>
#include <string_view>
#include <cstdint>
#include <expected>
#include "MacroUtils.h"
#include <string>

enum class FILEERROR : uint8_t
{
  NONE = 0,
  FILEDONTEXIST = 1,
};

enum class FILEOPENFLAGS : uint8_t
{
  READ = TOBIT(0),
  WRITE = TOBIT(1),
  APPEND = TOBIT(2),
  REMOVEDATA = TOBIT(3),
};

enum class FILESETCURSOR : uint8_t
{
  START = SEEK_SET,
  CURRENT = SEEK_CUR,
  END = SEEK_END
};

/*
4 bit size
FLAGS:
  0 bit: Read
  1 bit: Write
  2 bit: Append
  3 bit: RemoveData (by default false)
  */

class XEngineFile
{
public:
  bool IsReadable();
  bool IsWritable();

  void WriteBinaryData(
    const void* const start,
    uint64_t size,
    uint64_t count
  );

  uint64_t GetCurrentPoint();
  void SetPoint(int64_t offset, FILESETCURSOR where);

  [[nodiscard]]
  std::string ReadAllData();

  void Read(
    void* const buffer,
    uint32_t size,
    uint32_t count
  );

  void GetLine(
    char* const buffer,
    int32_t count
  );

  [[nodiscard]]
  FILEERROR Open(
    std::string_view filePath,
    uint8_t flags
  );

  void Close();

  XEngineFile(
    std::string_view filePath,
    uint8_t flags,
    FILEERROR& error
  );

  XEngineFile();
  ~XEngineFile();
private:
  FILE* m_file;
  uint8_t m_flags;
};
