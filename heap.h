#ifndef _heap_h_
#define _heap_h_

#include <iostream>

class Heap {
private:
	int MAX_SIZE = 50;

	int m, size;
	int* heap;

	void swap(int first, int second, int& steps);
	void resize();

public:
	Heap(int m);
	Heap(const Heap& heap)=delete;

	int get_m() { return m; }
	bool is_empty() { return size == 0; }

	int get();
	int find_index(int element) const;

	void add(int elem, int& steps);
	int remove(int start_index, int& steps);

	friend Heap* merge(Heap& h1, Heap& h2, int& steps);
	friend std::ostream& operator<< (std::ostream& os, const Heap& h);
	
	~Heap();
};

#endif