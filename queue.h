#ifndef QUEUE_H_
#define QUEUE_H_

template <typename T>
class Queue {
public:
	virtual bool empty() const = 0;
	virtual bool push(T const&) = 0;
	virtual T pop() = 0;
	virtual bool pop(T&) = 0;
	virtual T head() const = 0;
	virtual bool head(T&) const = 0;
	virtual ~Queue() {}
};

#endif /* QUEUE_H_ */
