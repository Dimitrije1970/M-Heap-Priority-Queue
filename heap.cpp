#include "heap.h"
#include <queue>

Heap::Heap(int m) : m(m), size(0), heap(new int[MAX_SIZE]) {}

void Heap::swap(int first, int second, int& steps) {
	int temp = heap[first];
	heap[first] = heap[second];
	heap[second] = temp;

	steps++;
}

void Heap::resize() {
	MAX_SIZE *= 2;
	int* new_heap = new int[MAX_SIZE];

	for (int i = 0; i < size;i++) new_heap[i] = heap[i];

	delete[] heap;
	heap = new_heap;
}

int Heap::find_index(int element) const{
	for (int i = 0; i < size; i++) {
		if (heap[i] == element) {
			return i;
		}
	}

	return -1;
}

int Heap::get() {
	if (size > 0) return heap[0];
	else return -1;
}

void Heap::add(int element, int& steps) {
	if (size + 1 == MAX_SIZE) resize();

	int index = size;
	heap[size++] = element;

	while (index > 0) {
		int parent = (index - 1) / m;
		if (heap[parent] > element) swap(parent, index, steps);

		steps++;
		index = parent;
	}
}

int Heap::remove(int start_index, int &steps) {
	if (size == 0) {
		std::cout << "Nema elemenata.";
		return -1;
	}

	int min = heap[start_index];
	heap[start_index] = heap[--size];
	int index = start_index;

	while (index < size) {
		int first_son = (index) * m + 1;
		if (first_son >= size) break;

		int* sons = new int[m];
		int num_of_sons = 0;
		for (int i = 0; i < m;i++) {
			if (first_son + i < size) {
				sons[num_of_sons++] = first_son + i;
			}
		}

		if (!num_of_sons) {
			delete[] sons;
			break;
		}

		bool is_bigger = false;
		for (int i = 0; i < num_of_sons; i++) {
			steps++;
			if (heap[sons[i]] < heap[index]) {
				is_bigger = true;
				break;
			}
		}

		if (is_bigger) {
			int min_son = sons[0];
			for (int i = 1; i < num_of_sons; i++) {
				steps++;
				if (heap[sons[i]] < heap[min_son]) {
					min_son = sons[i];
				}
			}

			swap(index, min_son, steps);
			index = min_son;
		}
		else {
			delete[] sons;
			break;
		}

		delete[] sons;
	}

	return min;
}

Heap* merge(Heap& h1, Heap& h2, int& steps) {
	Heap* new_heap = new Heap(h1.get_m());

	while (!h1.is_empty()) {
		new_heap->add(h1.remove(0, steps), steps);
	}

	while (!h2.is_empty()) {
		new_heap->add(h2.remove(0, steps), steps);
	}

	return new_heap;
}

std::ostream& operator<< (std::ostream& os, const Heap& h) {
	if (h.size == 0) return os << "Heap je prazan." << std::endl << std::endl;

	int new_line = h.m, cnt = 1;
	os << " - " << h.heap[0] << " - " << std::endl << " - ";

	for (int i = 1; i < h.size; i++) {
		os << h.heap[i] << " ";

		if (i % h.m == 0) os << " - ";
		if (i % new_line == 0) {

			os << std::endl << " - ";
			new_line += static_cast<int> (pow(h.m, ++cnt));
		}
	}

	return os << std::endl;
}

Heap::~Heap() {
	delete heap;

	size = 0;
}