#ifndef WRITELOCK_H_INCLUDED
#define WRITELOCK_H_INCLUDED

#include <mutex>

/// \todo this is currently not a read_write lock but a simple mutex.
class WriteLock
{
	typedef std::unique_lock<std::mutex> ReaderLock;
	typedef std::unique_lock<std::mutex> WriterLock;
public:
	ReaderLock lock_read() const;
	WriterLock lock_write() const;
private:
	mutable std::mutex mProtection;
};

#endif // WRITELOCK_H_INCLUDED
