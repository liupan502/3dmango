#include "mango3d.h"
#include "ShareMemoryUtil.h"
#include <windows.h>


bool GetNewDesignData(FString& newData, int& currentId) {
  DesignUpdateInfo* info = NULL;
  LPVOID h_index_map = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, TEXT("INDEX_NAME"));
  if (!h_index_map) {
    return false;
  }

  LPVOID index_buffer = ::MapViewOfFile(h_index_map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  info = (DesignUpdateInfo*)index_buffer;
  if (!info) {
    return false;
  }

  if (info->id <= currentId) {
    return false;
  }

  FString index_str = "SHARE_BUFFER_1";
  if (info->index == 2) {
    index_str = "SHARE_BUFFER_2";
  }

  LPVOID h_data_map = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, *index_str);
  if (!h_data_map) {
    return false;
  }

  LPVOID data_buffer = ::MapViewOfFile(h_data_map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  if (!data_buffer) {
    return false;
  }

  newData = FString((TCHAR*)data_buffer);
  currentId = info->id;
  return true;
}
