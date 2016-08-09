/*
sorting.cpp: implementation for a few sort algorithms selected from https://en.wikipedia.org/wiki/Sorting_algorithm 
author: Ulrike Hager
date: August 2016

compile: g++ -Wall -std=c++11 -o sorting sorting.cpp 
*/

#include <vector>
#include <iostream>  // cout
#include <iterator>  // ostream_iterator

///// swap /////
void swap( std::vector<int>& vec, int index_a, int index_b ){
  int temp = vec.at(index_a);
  vec.at(index_a ) = vec.at(index_b);
  vec.at( index_b ) = temp;
}



///// bubble_sort /////
std::vector<int> bubble_sort(const std::vector<int>& to_sort)
{
  std::vector<int> sorted = to_sort;
  bool swapped = true;
  while ( swapped ) {
    swapped = false;
    for ( decltype(sorted.size()) i = 0 ; i < sorted.size() - 1 ; i++ ) {
      if ( sorted.at( i ) > sorted.at( i+1) ) {
	swap(sorted, i, i+1 );
	swapped = true;
      }
    }
  }
  return sorted;
}



///// insertion_sort /////
std::vector<int> insertion_sort(const std::vector<int>& to_sort)
{
  std::vector<int> sorted = to_sort;
  for ( int i = 1; i < sorted.size() ; ++i ) {
    int temp = sorted.at(i);
    auto j = i - 1;
    while ( ( j >= 0 ) && ( sorted.at( j ) > temp ) ) {
      sorted.at( j+1 ) = sorted.at( j );
      --j;
    }
    sorted.at( j+1) = temp;
  }
  return sorted;
}



///// merge_sort /////
void merge(const std::vector<int>& to_sort, std::vector<int>& sorted, int start_left, int start_right, int end)
{
  int a = start_left;
  int b = start_right;
  for ( int i = start_left ; i < end ; ++i ) {
    if ( a < start_right && ( b == end || to_sort.at(a) < to_sort.at(b)  )  ) {
      sorted.at(i) =  to_sort.at(a) ;
      ++a;
    }
    else {
      sorted.at(i) = to_sort.at(b) ;
      ++b;
    }
  }
}

std::vector<int> merge_sort(const std::vector<int>& to_sort)
{
  std::vector<int> vec = to_sort;
  std::vector<int> sorted(to_sort.size());
  // assume to_sort consists of to_sort.size sorted arrays of size 1, now start merging with neighbour.
  for ( int length = 1; length < vec.size(); length *= 2 )  {
    for ( int i = 0; i < vec.size() ; i += 2*length ) {
      int start_right = ( i+length < vec.size() ) ? i+length : vec.size();
      int end = ( i+2*length < vec.size() ) ? i+2*length : vec.size();
      merge(vec, sorted, i, start_right, end );
    }
    vec = sorted;
  }
  return sorted;  
}



///// heap_sort /////
void sift(std::vector<int>& vec, int root, int last)
{
  while ( (root * 2) + 1  <=  last ) {  // left child of node k is at 2k
    int child = root * 2 +1 ;
    if (child < last  && vec.at(child+1) > vec.at(child)) ++child;

    if ( vec.at(root) < vec.at(child) ) {
      swap(vec, root, child );
      root = child;
    }
    else break;
  }
}


void heapify(std::vector<int>& vec)
{
  // child of node k at 2k and 2k+1 -> parent of last element 2k+1 = size-1 
  for ( int start = ( vec.size() - 2 ) / 2 ; start >= 0 ; --start ) {
    sift( vec, start, vec.size() - 1 );
  }
}


std::vector<int> heap_sort(const std::vector<int>& to_sort)
{
  std::vector<int> sorted = to_sort;
  heapify(sorted);

  int i = sorted.size() - 1;
  while ( i >=0 ) {
    swap( sorted, i, 0 );
    sift(sorted, 0, --i);
  }
  return sorted;  
}



///// quicksort /////
int partition(std::vector<int>& vec, int low, int high)
{
  int pivot = vec.at( high ) ; // have to choose some point...
  int i = low;
  for (int j = low; j<high; ++j ){
    if (vec.at(j) < pivot ) {
      swap( vec, i, j );
      ++i;
    }    
  }
  swap(vec, i, high);
  return i;
}


void quicksort ( std::vector<int>& vec, int low, int high)
{
  if ( low < high ) {
    int part = partition(vec, low, high );
    quicksort( vec, low, part-1);
    quicksort( vec, part+1, high);
  }
}


std::vector<int> quick_sort(const std::vector<int>& to_sort)
{
  std::vector<int> sorted = to_sort;
  quicksort(sorted, 0, sorted.size()-1);

   return sorted;  
}
 


///// main /////
int main()
{
  std::vector<int> unsorted{300, -5, 10,2, -100, 55, 7, 5, 601, 42, 666};
  //std::vector<int> unsorted{15, 19, 10, 7, 17, 16};
  //  std::vector<int> unsorted{6, 5, 3, 1, 8, 7, 2, 4};
  std::vector<int> sorted;
  std::ostream_iterator<int> out_iter(std::cout, ", ");

  sorted = bubble_sort(unsorted);
  std::cout << "bubble_sort: " ;
  std::copy(sorted.begin(), sorted.end(), out_iter );
  std::cout << "\n";
  
  sorted = insertion_sort(unsorted);
  std::cout << "insertion_sort: " ;
  std::copy(sorted.begin(), sorted.end(), out_iter );
  std::cout << "\n";
  
  sorted = merge_sort(unsorted);
  std::cout << "merge_sort: " ;
  std::copy(sorted.begin(), sorted.end(), out_iter );
  std::cout << "\n";

  sorted = heap_sort(unsorted);
  std::cout << "heap_sort: " ;
  std::copy(sorted.begin(), sorted.end(), out_iter );
  std::cout << "\n";

  sorted = quick_sort(unsorted);
  std::cout << "quick_sort: " ;
  std::copy(sorted.begin(), sorted.end(), out_iter );
  std::cout << "\n";
}



