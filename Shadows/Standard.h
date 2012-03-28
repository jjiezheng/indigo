#ifndef CubeFX_Standard_h
#define CubeFX_Standard_h

#include "Accessors.h"
#include "Types.h"
#include "Log.h"

#include <string>
#include <sstream>
#include <deque>
#include <vector>
#include <map>
#include <stack>

#include "glm/glm.hpp"
#include "glm/gtx/projection.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Vector3.h"
#include "Color3.h"

#define SAFE_DELETE(o) { delete (o); (o) = nullptr; }

#endif
