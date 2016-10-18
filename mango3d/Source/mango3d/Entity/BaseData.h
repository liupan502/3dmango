#ifndef MANGO_3D_BASE_DATA_H_
#define MANGO_3D_BASE_DATA_H_
#include "Json.h"
#include <string>
#include <map>
#include <vector>
#include <set>

//UCLASS()
class MANGO3D_API BaseData
{
public:
	BaseData();
	~BaseData();

  void set_name(FString name);
  FString name() const;

  virtual void InitWithJsonObject(FJsonObject& jsonObject);
  //virtual FJsonObject ToJson();

protected:
  FString name_;
  
};

#endif
