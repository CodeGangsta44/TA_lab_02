#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int merge_inv(int* arr, int st, int mid, int fn, int count){
  int len_of_left = mid - st + 1;
  int len_of_right = fn - mid;
  int left[len_of_left + 1];
  int right[len_of_right + 1];
  int i = 0;
  int j = 0;
  for (i = 0; i < len_of_left; i++){
    left[i] = arr[i + st];
  }
  left[len_of_left] = 2147483647; // limit of int;
  for (i = 0; i < len_of_right; i++){
    right[i] = arr[mid + i + 1];
  }
  right[len_of_right] = 2147483647; // limit of int;
  i = 0;
  j = 0;
  for (int k = st; k <= fn; k++){
    if (left[i] < right[j]) {
      arr[k] = left[i];
      i++;
    }
    else if (left[i] > right[j] && i < len_of_left && j < len_of_right) {
      arr[k] = right[j];
      count += len_of_left - i;
      j++;
    }
    else if (i == len_of_left && j != len_of_right){
      arr[k] = right[j];
      j++;
    }
  }
  return count;
}

int get_inv(int* arr, int start_ind, int finish_ind, int count){
  if (start_ind < finish_ind) {
    int middle = (finish_ind + start_ind) / 2;
    count = get_inv(arr, start_ind, middle, count);
    count = count +  get_inv(arr, middle + 1, finish_ind, count);
    count = merge_inv(arr, start_ind, middle, finish_ind, count);
    return count;
  }
  else return 0;
}

void get_top(int len, int* first_arr, int* second_arr, int *result){
  for (int i = 0; i < len; i++){
    result[first_arr[i] - 1] = second_arr[i];
  }
}

void merge(int arr[][2], int st, int mid, int fn){
  int len_of_left = mid - st + 1;
  int len_of_right = fn - mid;
  int left[len_of_left + 1][2];
  int right[len_of_right + 1][2];
  for (int i = 0; i < len_of_left; i++){
    left[i][0] = arr[st + i][0];
    left[i][1] = arr[st + i][1];
  }
  for (int i = 0; i < len_of_right; i++){
    right[i][0] = arr[mid + i + 1][0];
    right[i][1] = arr[mid + i + 1][1];
  }
  left[len_of_left][0] = 2147483647;
  left[len_of_left][1] = 2147483647;
  right[len_of_right][0] = 2147483647;
  right[len_of_right][1] = 2147483647;
  int i = 0;
  int j = 0;
  for (int count = st; count <= fn; count++){
    if (left[i][1] <= right[j][1]){
      arr[count][1] = left[i][1];
      arr[count][0] = left[i][0];
      i++;
    } else {
      arr[count][1] = right[j][1];
      arr[count][0] = right[j][0];
      j++;
    }
  }
}

void sort(int arr[][2], int st, int fn){
  if (st < fn){
    int middle = (st + fn) / 2;
    sort(arr, st, middle);
    sort(arr, middle + 1, fn);
    merge(arr, st, middle, fn);
  }
}

int main(int argc, char* argv[]){
  int X = atoi(argv[2]);
  ifstream fin(argv[1]);
  ofstream fout("ip71_dovhopoliuk_02_output.txt");
  int U, M, number_of_user;
  int *result = new int(M);
  fin >> U >> M;
  int out[U - 1][2];
  int matrix[U][M];
  for (int i = 0; i < U; i++){
    fin >> number_of_user;
    for (int j = 0; j < M; j++){
      fin >> matrix[number_of_user - 1][j];
    }
  }
  int j = 0;
  for (int i = 0; i < U; i++){
    if (i != (X - 1)){
      get_top(M, matrix[X - 1], matrix[i], result);
      out[j][1] = get_inv(result, 0, M - 1, 0);
      out[j][0] = i + 1;
      j++;
    }
  }
  sort(out, 0, 8);
  fout << X << endl;
  for (int i = 0; i < U - 1; i++){
    fout << out[i][0] << " " << out[i][1] << endl;
  }
}
