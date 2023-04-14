#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  
  priority_queue(std::vector<T> const& values) : m_heap(values) {
      for (int i = (m_heap.size() / 2) - 1; i >= 0; --i) {
          percolate_down(i);
      }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push(const T& entry) {
      m_heap.push_back(entry);
      percolate_up(m_heap.size() - 1);
  }

  void percolate_up(int idx) {
      while (idx > 0) {
          int parent_idx = (idx - 1) / 2;
          if (m_heap[parent_idx] <= m_heap[idx]) {
              break;
          }
          std::swap(m_heap[parent_idx], m_heap[idx]);
          idx = parent_idx;
      }
  }
  void percolate_down(size_t index) {
      size_t left_child = 2 * index + 1;
      size_t right_child = 2 * index + 2;
      size_t smallest = index;

      if (left_child < m_heap.size() && m_heap[left_child] < m_heap[smallest]) {
          smallest = left_child;
      }
      if (right_child < m_heap.size() && m_heap[right_child] < m_heap[smallest]) {
          smallest = right_child;
      }

      if (smallest != index) {
          std::swap(m_heap[index], m_heap[smallest]);
          percolate_down(smallest);
      }
  }


  void pop() {
      assert(!m_heap.empty());
      m_heap[0] = m_heap.back();
      m_heap.pop_back();
      percolate_down(0);
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap(const std::vector<T>& heap) {
      for (size_t i = 0; i < heap.size(); ++i) {
          size_t left_child = 2 * i + 1;
          size_t right_child = 2 * i + 2;
          if (left_child < heap.size() && heap[i] > heap[left_child]) {
              return false;
          }
          if (right_child < heap.size() && heap[i] > heap[right_child]) {
              return false;
          }
      }
      return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};
template <class T>
void heapify(std::vector<T>& v, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && v[left] > v[largest]) {
        largest = left;
    }

    if (right < n && v[right] > v[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(v[i], v[largest]);
        heapify(v, n, largest);
    }
}

template <class T>
void heap_sort(std::vector<T>& v) { 
    int n = v.size(); 
     
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i); 
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(v[0], v[i]); 
        heapify(v, i, 0); 
    }
}


#endif
