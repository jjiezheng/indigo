#include "Allocation.h"

#include <string>

void ClearMemory(void* memory, unsigned int length) {
	memset(memory, 0, length);
}
