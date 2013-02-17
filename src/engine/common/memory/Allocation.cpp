#include "Allocation.h"

#include <string>
#include <string.h>

void ClearMemory(void* memory, unsigned int length) {
	memset(memory, 0, length);
}
