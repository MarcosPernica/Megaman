#ifndef LOCKABLE
#define LOCKABLE
class Lockable{
	public:
	virtual void lock() = 0;
	virtual void unlock() = 0;
	//Lockable()=0;
};
#endif
