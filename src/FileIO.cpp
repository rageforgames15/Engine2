#include "FileIO.h"
#include <filesystem>
#include <utility>
#include <fmt/base.h>

bool XEngineFile::IsReadable()
{
  return m_flags & std::to_underlying(FILEOPENFLAGS::READ);
}

bool XEngineFile::IsWritable()
{
  return m_flags & std::to_underlying(FILEOPENFLAGS::WRITE);
}

void XEngineFile::WriteBinaryData(
  const void* const start,
  uint64_t size,
  uint64_t count
)
{
  if(m_file)
    fwrite(start, size, count,  m_file);
}

uint64_t XEngineFile::GetCurrentPoint()
{
  return ftell(m_file);
}

void XEngineFile::SetPoint(int64_t offset, FILESETCURSOR where)
{
  fseek(m_file, offset, std::to_underlying(where));
}

[[nodiscard]]
std::string XEngineFile::ReadAllData()
{
  if(!m_file) return "";
  SetPoint(0, FILESETCURSOR::END);
  uint64_t size = GetCurrentPoint();
  SetPoint(0, FILESETCURSOR::START);
  std::string data(size, '\0');
  Read(data.data(), sizeof(uint8_t), size);
  SetPoint(0, FILESETCURSOR::START);
  return data;
}

void XEngineFile::Read(
  void* const buffer,
  uint32_t typeSize,
  uint32_t count
)
{
  if(m_file)
    fread(buffer, typeSize, count, m_file);
}

void XEngineFile::GetLine(
  char* const buffer,
  int32_t count
)
{
  if(m_file)
    fgets(buffer, count, m_file);
}

[[nodiscard]]
FILEERROR XEngineFile::Open(
  std::string_view filePath,
  uint8_t flags
)
{
  Close();
  m_flags = flags;
  bool fileExist = std::filesystem::exists(filePath.data());
  bool readable
    = flags & std::to_underlying(FILEOPENFLAGS::READ);
  bool writable
    = flags & std::to_underlying(FILEOPENFLAGS::WRITE);
  bool shouldAppend
    = flags & std::to_underlying(FILEOPENFLAGS::APPEND);
  bool removeData
    = flags & std::to_underlying(FILEOPENFLAGS::REMOVEDATA);
    
  if(removeData || (!fileExist && writable))
    fclose(fopen(filePath.data(),"wb"));

  if(readable && writable)
    m_file = fopen(filePath.data(), "r+b");
  else if(readable)
  {
    if(fileExist)
      m_file = fopen(filePath.data(), "rb");
    else
      return FILEERROR::FILEDONTEXIST;
  }
  else
  {
    m_file = fopen(filePath.data(), "ab");
    SetPoint(0,FILESETCURSOR::START);
  }

  if(shouldAppend)
    SetPoint(0,FILESETCURSOR::END);

  return FILEERROR::NONE;
}

void XEngineFile::Close()
{
  if(m_file)
  {
    fclose(m_file);
    m_file = nullptr;
    m_flags = 0;
  }
}

XEngineFile::XEngineFile()
  : m_file(nullptr), m_flags(0)
{}

XEngineFile::XEngineFile(
  std::string_view filePath,
  uint8_t flags,
  FILEERROR& error
) : XEngineFile()
{
  error = Open(filePath, flags);
}

XEngineFile::~XEngineFile()
{
  Close();
}