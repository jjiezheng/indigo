#include "NavierStokesSimulation.h"

#include <assert.h>

#include "memory/Allocation.h"

#include "maths/Vector2.h"
#include "maths/Point.h"

#define SWAP(a,b) {float * tmp=a;a=b;b=tmp;}
#define IX(i,j) ((i)+(N+2)*(j))
#define SWAP(x0,x) {float * tmp=x0;x0=x;x=tmp;}
#define FOR_EACH_CELL for ( i=1 ; i<=N ; i++ ) { for ( j=1 ; j<=N ; j++ ) {
#define END_FOR }}

void add_source ( int N, float * x, float * s, float dt )
{
	int i, size=(N+2)*(N+2);
	for ( i=0 ; i<size ; i++ ) x[i] += dt*s[i];
}

void set_bnd ( int N, int b, float * x )
{
	int i;

	for ( i=1 ; i<=N ; i++ ) {
		x[IX(0  ,i)] = b==1 ? -x[IX(1,i)] : x[IX(1,i)];
		x[IX(N+1,i)] = b==1 ? -x[IX(N,i)] : x[IX(N,i)];
		x[IX(i,0  )] = b==2 ? -x[IX(i,1)] : x[IX(i,1)];
		x[IX(i,N+1)] = b==2 ? -x[IX(i,N)] : x[IX(i,N)];
	}
	x[IX(0  ,0  )] = 0.5f*(x[IX(1,0  )]+x[IX(0  ,1)]);
	x[IX(0  ,N+1)] = 0.5f*(x[IX(1,N+1)]+x[IX(0  ,N)]);
	x[IX(N+1,0  )] = 0.5f*(x[IX(N,0  )]+x[IX(N+1,1)]);
	x[IX(N+1,N+1)] = 0.5f*(x[IX(N,N+1)]+x[IX(N+1,N)]);
}

void lin_solve ( int N, int b, float * x, float * x0, float a, float c, int it )
{
	int i, j, k;

	for ( k=0 ; k<it ; k++ ) {
		FOR_EACH_CELL
			x[IX(i,j)] = (x0[IX(i,j)] + a*(x[IX(i-1,j)]+x[IX(i+1,j)]+x[IX(i,j-1)]+x[IX(i,j+1)]))/c;
		END_FOR
		set_bnd ( N, b, x );
	}
}

void diffuse ( int N, int b, float * x, float * x0, float diff, float dt, int it )
{
	float a=dt*diff*N*N;
	lin_solve ( N, b, x, x0, a, 1+4*a, it );
}

void advect ( int N, int b, float * d, float * d0, float * u, float * v, float dt )
{
	int i, j, i0, j0, i1, j1;
	float x, y, s0, t0, s1, t1, dt0;

	dt0 = dt*N;
	FOR_EACH_CELL
		x = i-dt0*u[IX(i,j)]; y = j-dt0*v[IX(i,j)];
		if (x<0.5f) x=0.5f; if (x>N+0.5f) x=N+0.5f; i0=(int)x; i1=i0+1;
		if (y<0.5f) y=0.5f; if (y>N+0.5f) y=N+0.5f; j0=(int)y; j1=j0+1;
		s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1;
		d[IX(i,j)] = s0*(t0*d0[IX(i0,j0)]+t1*d0[IX(i0,j1)])+s1*(t0*d0[IX(i1,j0)]+t1*d0[IX(i1,j1)]);
	END_FOR

	set_bnd ( N, b, d );
}

void project ( int N, float * u, float * v, float * p, float * div, int it )
{
	int i, j;

	FOR_EACH_CELL
		div[IX(i,j)] = -0.5f*(u[IX(i+1,j)]-u[IX(i-1,j)]+v[IX(i,j+1)]-v[IX(i,j-1)])/N;
		p[IX(i,j)] = 0;
	END_FOR	

	set_bnd ( N, 0, div ); set_bnd ( N, 0, p );

	lin_solve ( N, 0, p, div, 1, 4, it );

	FOR_EACH_CELL
		u[IX(i,j)] -= 0.5f*N*(p[IX(i+1,j)]-p[IX(i-1,j)]);
		v[IX(i,j)] -= 0.5f*N*(p[IX(i,j+1)]-p[IX(i,j-1)]);
	END_FOR

	set_bnd ( N, 1, u ); set_bnd ( N, 2, v );
}

void dens_step ( int N, float * x, float * x0, float * u, float * v, float diff, float dt, int it )
{
	add_source ( N, x, x0, dt );
	SWAP ( x0, x ); diffuse ( N, 0, x, x0, diff, dt, it );
	SWAP ( x0, x ); advect ( N, 0, x, x0, u, v, dt );
}

void vel_step ( int N, float * u, float * v, float * u0, float * v0, float visc, float dt, int it )
{
	add_source ( N, u, u0, dt ); add_source ( N, v, v0, dt );
	SWAP ( u0, u ); diffuse ( N, 1, u, u0, visc, dt, it );
	SWAP ( v0, v ); diffuse ( N, 2, v, v0, visc, dt, it );
	project ( N, u, v, u0, v0, it );
	SWAP ( u0, u ); SWAP ( v0, v );
	advect ( N, 1, u, u0, u0, v0, dt ); 
	advect ( N, 2, v, v0, u0, v0, dt );
	project ( N, u, v, u0, v0, it );
}

void NavierStokesSimulation::update(float dt) {
	int N = gridSize_.width;
	float* u = velocityX_;
	float* v = velocityY_;
	float* u_prev = lastVelocityX_;
	float* v_prev = lastVelocityY_;
	float visc = viscosity_;
	float diff = diffuseRate_;
	float* dens = density_;
	float* dens_prev = lastDensity_;

	int it = solverIterations_;

	vel_step ( N, u, v, u_prev, v_prev, visc, dt, it );
	dens_step ( N, dens, dens_prev, u, v, diff, dt, it );

	ClearMemory(u_prev, dataSize_);
	ClearMemory(v_prev, dataSize_);
	ClearMemory(dens_prev, dataSize_);
}

void NavierStokesSimulation::setGridSize(const CSize& gridSize) {
	gridSize_ = gridSize;

	userDataSize_ = gridSize.width * gridSize.height * sizeof(float);

	SAFE_DELETE_ARRAY(userDensity_);
	userDensity_ = new float[userDataSize_];
	ClearMemory(userDensity_, userDataSize_);

	dataSize_ = (gridSize.width + 2) * (gridSize.height + 2) * sizeof(float);


	SAFE_DELETE_ARRAY(density_);
	density_ = new float[dataSize_];
	ClearMemory(density_, dataSize_);

	SAFE_DELETE_ARRAY(lastDensity_);
	lastDensity_ = new float[dataSize_];
	ClearMemory(lastDensity_, dataSize_);

	SAFE_DELETE_ARRAY(userDensity_);
	userDensity_ = new float[userDataSize_];
	ClearMemory(userDensity_, userDataSize_);


	SAFE_DELETE_ARRAY(velocityX_);
	velocityX_ = new float[dataSize_];
	ClearMemory(velocityX_, dataSize_);

	SAFE_DELETE_ARRAY(lastVelocityX_);
	lastVelocityX_ = new float[dataSize_];
	ClearMemory(lastVelocityX_, dataSize_);

	SAFE_DELETE_ARRAY(userVelocityX_);
	userVelocityX_ = new float[dataSize_];
	ClearMemory(userVelocityX_, dataSize_);


	SAFE_DELETE_ARRAY(velocityY_);
	velocityY_ = new float[dataSize_];
	ClearMemory(velocityY_, dataSize_);

	SAFE_DELETE_ARRAY(lastVelocityY_);
	lastVelocityY_ = new float[dataSize_];
	ClearMemory(lastVelocityY_, dataSize_);

	SAFE_DELETE_ARRAY(userVelocityY_);
	userVelocityY_ = new float[dataSize_];
	ClearMemory(userVelocityY_, dataSize_);

}

void NavierStokesSimulation::addDensity(const Point& location, float densityAmount) {
	unsigned int dataIndex = gridIndex(location.x + 1, location.y + 1);
	lastDensity_[dataIndex] = densityAmount;	
}

void NavierStokesSimulation::setVelocity(const Point& gridPosition, const Vector2& velocity) {
	unsigned int dataIndex = gridIndex(gridPosition.x + 1, gridPosition.y + 1);
	lastVelocityX_[dataIndex] = velocity.x;
	lastVelocityY_[dataIndex] = velocity.y;
}

const float* NavierStokesSimulation::density() {
	copyUserArray(density_, userDensity_);
	return userDensity_;
}

const float* NavierStokesSimulation::velocityX() {
	copyUserArray(velocityX_, userVelocityX_);
	return userVelocityX_;
}

const float* NavierStokesSimulation::velocityY() {
	copyUserArray(velocityY_, userVelocityY_);
	return userVelocityY_;
}

void NavierStokesSimulation::copyUserArray(float* in, float* out) {
	ClearMemory(out, userDataSize_);
	unsigned int userOffset = 0;
	unsigned int offset = 2 + gridSize_.width + 1;
	for (int y = 0; y < gridSize_.height; y++) {
		memcpy(userOffset + out, offset + in, gridSize_.width * sizeof(float));
		offset += gridSize_.width + 2;
		userOffset += gridSize_.width;
	}
}

