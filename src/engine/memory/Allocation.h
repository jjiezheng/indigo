#ifndef ALLOCATION_H
#define ALLOCATION_H

void ClearMemory(void* memory, unsigned int length);

#define SAFE_DELETE(o) { if ((o)) { delete (o); (o) = 0; } }
#define SAFE_FREE(o) { free (o); (o) = 0; }

#define SAFE_DELETE_ARRAY(o) { if ((o)) { delete[] (o); (o) = 0; } }

#endif
