#ifndef ALLOCATION_H
#define ALLOCATION_H

#define SAFE_DELETE(o) { if ((o)) { delete (o); (o) = NULL; } }
#define SAFE_FREE(o) { free (o); (o) = NULL; }

#endif
