#ifndef INTERSECTION_RESULT_H
#define INTERSECTION_RESULT_H

class IntersectionResult {

public:

	IntersectionResult()
		: intersected(false)
		, distance(0.0f) { }

public:

	bool intersected;
	float distance;

};



#endif