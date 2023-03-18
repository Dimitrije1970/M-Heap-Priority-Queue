#ifndef _priority_queue_h_
#define _priority_queue_h_

#include "heap.h"

class PriorityQueue {
private:
	Heap* heap;

public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue& pq) = delete;

	bool is_empty() const;
	int front() const;

	void insert(int element);
	int remove();

	~PriorityQueue();
};

#endif