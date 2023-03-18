#include "priority_queue.h"

PriorityQueue::PriorityQueue() : heap(new Heap(2)) {}

bool PriorityQueue::is_empty() const{
	return heap->is_empty();
}

int PriorityQueue::front() const{
	return heap->get();
}

void PriorityQueue::insert(int element) {
	int steps = 0;
	heap->add(element, steps);
}

int PriorityQueue::remove() {
	int steps = 0;
	return heap->remove(0, steps);
}

PriorityQueue::~PriorityQueue() {
	delete heap;
	heap = nullptr;
}