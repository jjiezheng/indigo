#ifndef STANDARD_H
#define STANDARD_H

#include <string>
#include <sstream>
#include <deque>
#include <vector>
#include <map>
#include <stack>

#include "maths/Vector3.h"
#include "renderer/Color3.h"
#include "io/Log.h"

#include "Accessors.h"
#include "Types.h"

#define SAFE_DELETE(o) { delete (o); (o) = nullptr; }
#define SAFE_FREE(o) { free (o); (o) = nullptr; }

#endif
