#include "WriteLock.h"



WriteLock::WriterLock WriteLock::lock_write() const
{
	return std::move(std::unique_lock<std::mutex>(mProtection));
}

WriteLock::ReaderLock WriteLock::lock_read() const
{
	return std::move(std::unique_lock<std::mutex>(mProtection));
}
