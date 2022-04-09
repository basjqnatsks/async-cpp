#pragma once
#include <mutex>
#include <queue>




template <typename T>
class Queue {
private:

	//Main Queue
	std::queue<T*> __Queue;

	//Lock Threadsafe
	std::mutex __Lock;

public:
	Queue() {

	}
	~Queue() {

	}
	void PrintQueue() {
		std::cout << this->__Queue.size();
	}

	void Push(T * var) {
		if (var != nullptr) {
			//Locks Queue
			this->__Lock.lock();
			//puts back of queue while locked safely
			this->__Queue.push(var);
			//unlocks queue for other memers
			this->__Lock.unlock();
		}
	}
	T * pop() {
		//Temp var for pop
		T *TypeVar = nullptr;
		//lock queue
		this->__Lock.lock();
		//check if queue empty safely
		if (!this->__Queue.empty()) {
			//pop off queue
			TypeVar = this->__Queue.front();
			this->__Queue.pop();
		}
		//unlock queue
		this->__Lock.unlock();
		//return Popped var
		return TypeVar;
	}

private:



};