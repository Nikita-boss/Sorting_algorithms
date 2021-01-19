#include <iostream>
#include <vector>
#include <chrono>     // Time
#include <algorithm>  // std::swap, iter_swap, copy
#include <iterator>   // std::ostream_iterator
#include <stdlib.h>   // rand function

/* The program analyses the running time of the sorting algorithms */

//***************************************************************
//                       1. Insertion Sort Algorithm (Simple)
//***************************************************************

void insertion_sort( int array[], int array_length) {
  int current_index{},  key{};
  for (int j{1}; j < array_length; ++j) {
      key = array[j];
      current_index = j - 1;
        while (current_index >= 0 && array[current_index] > key) {
          array[current_index+1] = array [current_index];
          --current_index;
        }
      array[current_index+1] = key;
  }
}

//***************************************************************
//                       2. Insertion Sort Algorithm (Generic)
//***************************************************************

template <typename RandomAccessIterator>
void insertion_sort_generic (RandomAccessIterator begin , RandomAccessIterator end) 
{                                                                             
    for(auto i = begin + 1; i < end; ++i) {
        auto k = *i;
        auto current_index = i - 1;
        while(current_index >= begin && *current_index > k)  {
          std::iter_swap(current_index, current_index+1);
          --current_index;
        }
    }  
} 

//***************************************************************
//                       3. Buuble Sort Algorithm (Simple)
//***************************************************************

void bubble_sort (int array[], int array_length) {
  // Step through each element of the array (except the last, which will already be sorted by the time we get to it)
  for (int number_iter{0}; number_iter < array_length-1; ++number_iter) {
    // Search through all elements up to the end of the array - 1
    // The last element has no pair to compare against
    for (int current_index{0}; current_index < array_length-1; ++current_index) {
      // If the current element is larger than the element after it, swap them
      if (array[current_index+1] < array[current_index]) {
        std::swap (array[current_index+1], array[current_index]);
      }
    }
  }
}

//***************************************************************
//                       4. Bubble Sort Algorithm (Optimised)
//***************************************************************

void bubble_sort_optimised (int array[], int array_length) {
 
  for (int number_iter{0}; number_iter < array_length-1; ++number_iter) {

   bool swapped{ false }; // Keep track of whether any elements were swapped this iteration
    for (int current_index{0}; current_index < array_length-number_iter-1; ++current_index) {
     
      if (array[current_index+1] < array[current_index]) {
        std::swap (array[current_index+1], array[current_index]);
        swapped = true;
      }
    }
    // If we haven't swapped any elements this iteration, we're done early
        if (!swapped) {
            // std::cout << "The list was sorted after: " << number_iter << " iterations." << '\n';
            break;
        }
   }  
}

//***************************************************************
//                      5. Bubble Sort Algorithm (Template Optimised)
//***************************************************************

template <typename RandomAccessIterator>
void bubble_sort_generic (RandomAccessIterator begin, RandomAccessIterator end) {
  bool swapped = true;
  int number_iter {0};
  while (begin != --end && swapped) {  //Optimisation: 1. through decrementation: --end; 2. through bool swapped   
    swapped = false;
    for (auto i = begin; i != end; ++i) { // end - returns an iterator pointing to the past-the-end elements in the sequence.
      if (* (i + 1) < *i) { 
        std::iter_swap(i, i+1); //Swaps the elements pointed to by a and b.
        swapped = true;
      }
    }
    ++number_iter;
  }
}

//***************************************************************
//                       6. Selection Sort Algorithm
//***************************************************************

void selection_sort (int array [], int length) {
	for (int startIndex {0}; startIndex < length - 1; ++startIndex) {
		int smallestIndex{ startIndex };
		for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex) {
			if (array[currentIndex] < array[smallestIndex])
				smallestIndex = currentIndex;
		}
		std::swap(array[startIndex], array[smallestIndex]);
	}
}
//***************************************************************
//                       7. Selection Sort Algorithm (Generic)
//***************************************************************

template <typename RandomAccessIterator>
void selection_sort_generic (RandomAccessIterator begin, RandomAccessIterator end) {
	for (auto i = begin; i != end - 1; ++i) {
		std::iter_swap (i, std::min_element(i, end));     
	}
}

//***************************************************************
//                       8. Merge Sort Algorithm
//***************************************************************

void merge (int array [], int first_index, int middle_index, int last_index) {
  int subArrLen1 {middle_index-first_index+1}, subArrLen2 {last_index-middle_index};
  std::vector<int> left(middle_index-first_index+1+1);
  std::vector<int> right(last_index-middle_index+1);
  int inf = std::numeric_limits<int>::max();
  left[subArrLen1] = inf;
  right[subArrLen2] = inf;
    for (int i{0}; i < subArrLen1; ++i) {
      left[i] = array[first_index+i];
    }
    for (int i{0}; i < subArrLen2; ++i) {
      right[i] = array[middle_index+i+1];
    }

  int left_index {0}, right_index {0};
    for (int array_index {first_index}; array_index < last_index + 1 ; ++array_index) {
      if (left[left_index] <= right[right_index]) {
        array[array_index] = left[left_index];
        ++left_index;
      }
      else {
        array[array_index] = right[right_index];
        ++right_index;
      }
    } 
}

void merge_sort (int array [], int first_index, int last_index) {
  int middle_index{};
  if (first_index < last_index) {
    middle_index= (first_index+last_index)/2;
    merge_sort(array,first_index,middle_index);
    merge_sort(array, middle_index+1, last_index);
    merge(array,first_index,middle_index,last_index);
  }
}

//***************************************************************
//                       9. Quick Sort Algorithm (Simple)
//***************************************************************

int partition (int array [], int first_index, int last_index) {
  int pivot {array[last_index]};
  int part_index {first_index-1};
    for (int current_index {first_index}; current_index < last_index; ++current_index) {
      if (array[current_index] <= pivot) {
        ++part_index;
        std::swap(array[current_index], array[part_index]);
      }
    }
  std::swap(array[last_index], array[part_index+1]);
  return part_index+1;  
}

void quick_sort (int array[], int first_index, int last_index) {
  if (first_index < last_index) {
    int pivot = partition (array, first_index, last_index);
    quick_sort(array, first_index, pivot-1);
    quick_sort(array, pivot+1, last_index);
  }
}

//***************************************************************
//                       10. Quick sort (Improved and Optimised)
//***************************************************************

template <typename RandomAccessIterator>
void insertion_sort(RandomAccessIterator begin , RandomAccessIterator end) 
{                                                                             
    for(auto i = begin + 1; i < end; ++i) {
        auto k = *i;
        auto current_index = i - 1;
        while(current_index >= begin && *current_index > k)  {
          std::iter_swap(current_index, current_index+1);
          --current_index;
        }
    }  
} 

int partition_optimised (int array [], int first_index, int last_index) {
  int pivot {array[last_index]}; // Pivot chosen as the median from quicksort function; left_count - used for optimisation point 2 to count repeated elements as pivots
  int part_index {first_index-1};  // Partition index (i) for the elements that are less than the pivot
    for (int current_index {first_index}; current_index < last_index; ++current_index) {
      if (array[current_index] <= pivot) {
        ++part_index;
        std::swap(array[current_index], array[part_index]);
      }
    }
  std::swap(array[last_index], array[part_index+1]);

  return part_index+1;  
}

void quick_sort_optimised (int array[], int first_index, int last_index) {

  if (first_index < last_index) {
    int middle_index {(first_index+last_index)/2};
    if (array[middle_index] < array[first_index]) {
      std::swap(array[middle_index], array[first_index]); }
    else if (array[last_index] < array[first_index]) {
      std::swap(array[last_index],  array[first_index]); }
    else if (array[middle_index] < array[last_index]) {
      std::swap(array[middle_index], array[last_index]); }

    if ((last_index - first_index) < 10) {
      insertion_sort (&array[first_index], &array[last_index+1]);
    }
    else {
       int pivot = partition_optimised (array, first_index, last_index);
       quick_sort_optimised(array, first_index, pivot-1);
        quick_sort_optimised(array, pivot+1, last_index);
    }
  }
}

//***************************************************************
//                       Main 
//***************************************************************

int main () {
  // Create an unsorted list
  srand(time(NULL));
  constexpr int number_elements {100'000};
  int array[number_elements] {};
    for (unsigned long i{0}; i < std::size(array); ++i) {
      array [i] = rand() % std::size(array) - (std::size(array)/2);
    } 

  int array_copy [number_elements] {};   // Restore the unsorted version of the array once it has been sorted by one of the sorting algorithms
  std::copy(std::begin(array), std::end(array), array_copy);

  std::chrono::system_clock::time_point time1,time2;

  std::cout << "The number of elements to sort is " << number_elements << '\n';

  time1 = std::chrono::system_clock::now();
  insertion_sort (array, std::size(array));
  time2 = std::chrono::system_clock::now();
  double insertion_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
  std::cout << "Time taken by insertion sort algorithm: " 
            << insertion_sort_time << " microseconds" <<'\n';   
  std::copy(std::begin(array_copy),std::end(array_copy), array);  // IMPORTANT: return the array to the unsorted version


  time1 = std::chrono::system_clock::now();
  insertion_sort_generic (std::begin(array), std::end(array));
  time2 = std::chrono::system_clock::now();
  double insertion_sort_generic_time = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
  std::cout << "Time taken by generic insertion sort algorithm: " 
            << insertion_sort_generic_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array); // IMPORTANT: return the array to the unsorted version

  time1 = std::chrono::system_clock::now();
  bubble_sort (array, std::size(array));
  time2 = std::chrono::system_clock::now();
  double bubble_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(time2-time1).count();
  std::cout << "Time taken by simple bubble sort algorithm: "
         << bubble_sort_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array); // IMPORTANT: return the array to the unsorted version 
  
  time1 = std::chrono::system_clock::now();
  bubble_sort_optimised (array, std::size(array));
  time2 = std::chrono::system_clock::now();
  double bubble_sort_optimised_time = std::chrono::duration_cast<std::chrono::microseconds>(time2-time1).count();
  std::cout << "Time taken by optimised bubble sort algorithm: "
         << bubble_sort_optimised_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array);  // IMPORTANT: return the array to the unsorted version
  
  time1 = std::chrono::system_clock::now();
  bubble_sort_generic (std::begin(array), std::end(array));
  time2 = std::chrono::system_clock::now();
  double bubble_sort_generic_time = std::chrono::duration_cast<std::chrono::microseconds>(time2-time1).count();
  std::cout << "Time taken by optimised generic bubble sort algorithm: "
         << bubble_sort_generic_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array);  // IMPORTANT: return the array to the unsorted version

  time1 = std::chrono::system_clock::now();
	selection_sort (array, std::size(array));
	time2 = std::chrono::system_clock::now();
	double selection_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
	std::cout << "Time taken by selectin sort algorithm: "
         << selection_sort_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array);  // IMPORTANT: return the array to the unsorted version

	time1 = std::chrono::system_clock::now();
	selection_sort_generic (std::begin(array), std::end(array));
	time2 = std::chrono::system_clock::now();
	double selection_sort_generic_time = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
	std::cout << "Time taken by generic selectin sort algorithm: "
         << selection_sort_generic_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array);   // IMPORTANT: return the array to the unsorted version 

  int first_index {0}, last_index{std::size(array)-1};
  time1 = std::chrono::system_clock::now();
  merge_sort (array,first_index,last_index);
  time2 = std::chrono::system_clock::now();
  double merge_sort_time2 = std::chrono::duration_cast<std::chrono:: microseconds>(time2-time1).count();
  std::cout << "Time taken by simple merge sort algorithm: "
         << merge_sort_time2 << " microseconds" << '\n';     
  std::copy(std::begin(array_copy),std::end(array_copy), array);  
 
  first_index =  0;
  last_index = std::size(array)-1;
  time1 = std::chrono::system_clock::now();
  quick_sort (array, first_index, last_index);
  time2 = std::chrono::system_clock::now();
  double quick_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
  std::cout << "Time taken by simple quick sort algorithm: "
         << quick_sort_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array); 


  first_index = 0, last_index = std::size(array)-1;
  time1 = std::chrono::system_clock::now();
  quick_sort_optimised (array, first_index, last_index);
  time2 = std::chrono::system_clock::now();
  double quick_sort_optimised_time = std::chrono::duration_cast<std::chrono::microseconds>(time2-time1).count();
  std::cout << "Time taken by optimised quick sort algorithm: "
         << quick_sort_optimised_time << " microseconds" << '\n'; 
  std::copy(std::begin(array_copy),std::end(array_copy), array); 

  time1 = std::chrono::system_clock::now();
  std::sort(std::begin(array), std::end(array));
  time2 = std::chrono::system_clock::now();
  double LIBRARY_SORT_time = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();
  std::cout << "Time taken by LIBRARY sort algorithm: "
         << LIBRARY_SORT_time << " milliseconds" << '\n'; 


  //std::cout << "The sorted list in ascending order is: " << '\n';
  //copy (std::begin(array), std::end(array), std::ostream_iterator<int>(std::cout, " ")); //Ostream iterators are output iterators that write sequentially to an output stream (such as cout).
  return 0;
}