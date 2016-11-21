#include "mango3d.h"
#include "PolygonUtil.h"

TArray<FVector2D> clean_vertex_list(TArray<int>& vertex_index_list, const TArray<FVector2D>& vertex_array);

void append_vertex(TArray<FVector2D>& vertices, bool flag, FVector2D v1, FVector2D v2, FVector2D v3);

bool IsClockwisePolygon(TArray<FVector2D> polygon) {
  if (polygon.Num() < 3) {
    return false;
  }
  
  float top_y_value = polygon[0].Y;
  TArray<int> top_vertex_indices;
  top_vertex_indices.Add(0);
  for (int i = 1; i < polygon.Num(); i++) {
    FVector2D vertex = polygon[i];
    if (vertex.Y > top_y_value) {
      top_y_value = vertex.Y;
      top_vertex_indices.Empty();
      top_vertex_indices.Add(i);
    }
    else if (vertex.Y > top_y_value) {
      top_vertex_indices.Add(i);
    }
  }

  bool is_clockwise = true;
  int vertex_num = polygon.Num();
  for (int i = 0; i < top_vertex_indices.Num(); i++) {
    int index = top_vertex_indices[i];
    int next_index = (index + 1) % vertex_num;
    int pre_index = (index + vertex_num - 1) % vertex_num;

    FVector2D pre_vertex = polygon[pre_index];
    FVector2D vertex = polygon[index];
    FVector2D next_vertex = polygon[next_index];

    if (pre_vertex.Y == vertex.Y && next_vertex.Y == vertex.Y) {
      continue;
    }

    if (pre_vertex.X > vertex.X || vertex.X > next_vertex.X) {
      is_clockwise = false;
    }
  }

  return is_clockwise;
}

bool IsConvexVertex(FVector2D preVertex, FVector2D vertex, FVector2D nextVertex) {
  FVector2D vec1 = vertex - preVertex;
  FVector2D vec2 = nextVertex - preVertex;
  float flag = vec1.X*vec2.Y - vec1.Y*vec2.X;
  return flag > 0;
}

TArray<FVector2D> Triangulation(TArray<FVector2D> polygon) {

  if (IsClockwisePolygon(polygon)) {
    TArray<FVector2D> tmp;
    for (int i = 1; i <= polygon.Num(); i++) {
      tmp.Add(polygon[polygon.Num() - i]);
    }
    polygon.Empty();
    polygon = tmp;
  }

  TArray<FVector2D> result;

  TArray<int> vertex_indices;
  for (int i = 0; i < polygon.Num(); i++) {
    vertex_indices.Add(i);
  }

  for (int i = 0; i < vertex_indices.Num(); i++) {
    for (int j = i + 1; j < vertex_indices.Num(); j++) {
      FVector2D vertex1 = polygon[vertex_indices[i]];
      FVector2D vertex2 = polygon[vertex_indices[j]];
      if (vertex1.Y < vertex2.Y) {
        int tmp = vertex_indices[i];
        vertex_indices[i] = vertex_indices[j];
        vertex_indices[j] = tmp;
      }
    }
  }

  int vertex_num = polygon.Num();
  int top_vertex_index = vertex_indices[0];
  int bottom_vertex_index = vertex_indices[vertex_num - 1];

  TArray<int> left_vertex_list; 
  for (int i = top_vertex_index;; i++) {
    int index = i%vertex_num;
    left_vertex_list.Add(index);
    if(index == bottom_vertex_index){
      break;
    }    
  }
  TArray<FVector2D> vertices1 = clean_vertex_list(left_vertex_list, polygon);
  result.Append(vertices1);
  
  TArray<int>right_vertex_list;
  for (int i = bottom_vertex_index;; i++) {
    int index = i%vertex_num;
    right_vertex_list.Add(index);
    if (index == top_vertex_index) {
      break;
    }
  }
  TArray<FVector2D> vertices2 = clean_vertex_list(right_vertex_list, polygon);
  result.Append(vertices2);
  for (int i = 0; i < right_vertex_list.Num() / 2; i++) {
    int tmp = right_vertex_list[i];
    right_vertex_list[i] = right_vertex_list[right_vertex_list.Num() - (i + 1)];
    right_vertex_list[right_vertex_list.Num() - (i + 1)] = tmp;
  }
  vertex_indices.Empty();
  vertex_indices.Add(top_vertex_index);
  int left_index = 1, right_index = 1;
  int list_flag = 0;
  while (true) {
    FVector2D left_vertex = polygon[left_vertex_list[left_index]];
    FVector2D right_vertex = polygon[right_vertex_list[right_index]];
    if (left_vertex.Y >= right_vertex.Y) {
      vertex_indices.Add(left_vertex_list[left_index]);
      list_flag = 1;
    }
    else if (left_vertex.Y < right_vertex.Y) {
      vertex_indices.Add(right_vertex_list[right_index]);
      list_flag = -1;
    }
    else {
      /*if (list_flag >= 0) {
        vertex_indices.Add(left_vertex_list[left_index]);
      }
      else {
        vertex_indices.Add(right_vertex_list[right_index]);
      }*/
    }
    if (list_flag >= 1) {
      left_index++;
    }
    else {
      right_index++;
    }
    
    if (left_index >= left_vertex_list.Num()-1) {
      for (int i = right_index; i < right_vertex_list.Num() - 1; i++) {
        vertex_indices.Add(right_vertex_list[i]);
      }
      break;
    }
    else if(right_index >= right_vertex_list.Num() - 1){
      for (int i = left_index; i < left_vertex_list.Num() - 1; i++) {
        vertex_indices.Add(left_vertex_list[i]);
      }
      break;
    }

  }
  vertex_indices.Add(bottom_vertex_index);

  if (vertex_indices.Num() < 3) {
    return result;
  }
  top_vertex_index = vertex_indices[0];
  int second_top_vertex_index = vertex_indices[1];
  int second_top_vertex_index_index;
  bool flag = left_vertex_list.Find(second_top_vertex_index,second_top_vertex_index_index);
  if (!flag) {
    right_vertex_list.Find(second_top_vertex_index, second_top_vertex_index_index);
  }
  //int third_top_vertex_index = flag ? left_vertex_list[second_top_vertex_index_index + 1] :
  //  right_vertex_list[second_top_vertex_index_index + 1];



  FVector2D top_vertex = polygon[top_vertex_index];
  FVector2D second_top_vertex = polygon[second_top_vertex_index];
  //FVector2D third_top_vertex = polygon[third_top_vertex_index];
  
  TArray<int> current_buffer_list;
  current_buffer_list.Add(top_vertex_index);
  current_buffer_list.Add(second_top_vertex_index);
  
  for (int i = 2; i < vertex_indices.Num(); i++) {
    int vertex_index = vertex_indices[i];
    FVector2D vertex = polygon[vertex_index];
    int vertex_index_index;
    bool tmp_flag = left_vertex_list.Find(vertex_index, vertex_index_index);
    if (tmp_flag != flag) {
      while (current_buffer_list.Num() > 1) {
        int first_index = current_buffer_list[0];
        int second_index = current_buffer_list[1];
        FVector2D vertex1 = polygon[first_index];
        FVector2D vertex2 = polygon[second_index];
        
        
        if (tmp_flag) {
          result.Add(vertex);
          result.Add(vertex2);
          result.Add(vertex1);
        }
        else {
          result.Add(vertex);
          result.Add(vertex1);
          result.Add(vertex2);
        }
        current_buffer_list.RemoveAt(0);
        
      }
      current_buffer_list.Add(vertex_index);
      flag = tmp_flag;
    }
    else {

      while (true) {
        int pre_index = current_buffer_list[current_buffer_list.Num() - 1];
        int pre_pre_index = current_buffer_list[current_buffer_list.Num() - 2];
        FVector2D pre_vertex = polygon[pre_index];
        FVector2D pre_pre_vertex = polygon[pre_pre_index];
        bool is_convex;
        if (flag) {
          is_convex = IsConvexVertex(pre_pre_vertex, pre_vertex, vertex);
        }
        else {
          is_convex = IsConvexVertex(vertex, pre_vertex, pre_pre_vertex);
        }
        if (is_convex) {
          if (tmp_flag) {
            result.Add(vertex);
            result.Add(pre_pre_vertex);
            result.Add(pre_vertex);
          }
          else {
            result.Add(vertex);
            result.Add(pre_vertex);
            result.Add(pre_pre_vertex);
          }
          current_buffer_list.RemoveAt(current_buffer_list.Num() - 1);
          if (current_buffer_list.Num() < 2) {
            current_buffer_list.Add(vertex_index);
            break;
          }
        }
        else {
          current_buffer_list.Add(vertex_index);
          break;
        }
      }
      
    }

  }

  return result;
}

TArray<FVector2D> clean_vertex_list(TArray<int>& vertex_index_list, const TArray<FVector2D>& vertex_array) {
  
  TArray<FVector2D> result;
  int vertex_index_num = vertex_index_list.Num();
  if (vertex_index_num == 0) {
    return result;
  }
  for (int i = 1; i < vertex_index_list.Num() - 1; i++) {
    FVector2D pre_vertex = vertex_array[vertex_index_list[i - 1]];
    FVector2D vertex = vertex_array[vertex_index_list[i]];
    FVector2D next_vertex = vertex_array[vertex_index_list[i + 1]];
    if (vertex.Y >= pre_vertex.Y && vertex.Y >= next_vertex.Y && IsConvexVertex(pre_vertex,vertex, next_vertex)) {
      result.Add(pre_vertex);
      result.Add(vertex);
      result.Add(next_vertex);
      vertex_index_list.RemoveAt(i);
      i--;
    }
  }
  return result;
}

void append_vertex(TArray<FVector2D>& vertices, bool flag, FVector2D v1, FVector2D v2, FVector2D v3) {
  if (flag) {
    vertices.Add(v3);
    vertices.Add(v2);
    vertices.Add(v1);
  }
  else {
    vertices.Add(v3);
    vertices.Add(v1);
    vertices.Add(v2);
  }
}