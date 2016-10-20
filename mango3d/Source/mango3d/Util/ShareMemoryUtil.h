#ifndef MANGO_3D_SHARE_MEMORY_UTIL_H_
#define MANGO_3D_SHARE_MEMORY_UTIL_H_

#include "Core.h"

typedef struct DesignUpdateInfo {
  int id;
  int updater;
  int index;
  DesignUpdateInfo(int Id = 0, int Updater = -1, int Index = 0) {
    id = Id;
    updater = Updater;
    index = Index;
  }
} DesignUpdateInfo;

bool GetNewDesignData(FString& newData, int& currentIndex);
#endif
