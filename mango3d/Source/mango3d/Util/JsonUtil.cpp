
#include "mango3d.h"
#include "JsonUtil.h"

FVector StringToVector2(FString& str) {
  FString split_token = ",";
  FString tmp_str = str;
  FString left_str;
  FString right_str;
  
  
  tmp_str.Split(split_token, &left_str, &right_str);
  float x = FCString::Atof(*left_str);
  float y = FCString::Atof(*right_str);
  float z = 0.0;
  FVector vector(x, y, z);
  return vector;
}

FVector StringToVector3(FString& str) {
  FString split_token = ",";
  FString tmp_str = str;
  FString left_str;
  FString right_str;

  tmp_str.Split(split_token, &left_str, &right_str);
  float x = FCString::Atof(*left_str);
  tmp_str = right_str;

  tmp_str.Split(split_token, &left_str, &right_str);
  float y = FCString::Atof(*left_str);
  float z = FCString::Atof(*right_str);

  FVector vector(x, y, z);
  return vector;
}