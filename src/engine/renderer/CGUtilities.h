#ifndef CGUTILITIES_H
#define CGUTILITIES_H


#include <assert.h> 
#include "io/Log.h"
#include "CG/cg.h"

class CGUtilities {

public:

	static void checkForError() {
#ifdef ADEBUG
		checkForGLError();
		checkForCGError();
#endif
	}

	static void checkForCGError() {
		CGerror error;
		const char* errorString = cgGetLastErrorString(&error);
		if (errorString) {
			LOG(LOG_CHANNEL_GL_UTILS, "CG Error: %s", errorString);
		}
		assert(error == CG_NO_ERROR);
	}
};

#endif