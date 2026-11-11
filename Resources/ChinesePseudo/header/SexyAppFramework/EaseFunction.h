
#pragma once

namespace Sexy
{
	
	/**
	 * The ease function provides ease-in/ease-out functionality.
	 * Interpreted as distance as a function of time, the ease function
	 * allows you to specify the velocities v0 and v1, and times a and b,
	 * and it will provide a smooth distance curve that has constant acceleration
	 * from v0 to vc over the time interval [0,a], constant velocity vc over
	 * the time interval [a,b], and constant acceleration from vc to v1 over the
	 * time interval [b,1], such that the total distance traveled over the time
	 * interval [0,1] is 1.  So:
	 * d(0) = 0
	 * d(1) = 1
	 * v(0) = v0
	 * v(a) = v(b) = vc
	 * v(1) = v1
	 *
	 * To compute vc given v0, v1, a and b, we observe that the total distance
	 * traveled is the sum of the distances traveled during each time interval
	 * [0,a], [a,b] and [b,1], and must be equal to 1.
	 * The distance traveled during each time interval can be expressed as the
	 * length of the interval times the average velocity over that interval,
	 * distance=time*average_velocity.  So,
	 * 
	 * 1 = a*(v0+vc)/2  +  (b-a)*vc  +  (1-b)*(vc+v1)/2
	 * 
	 * Which we can solve for vc to get
	 * 
	 * vc = (2 - a*v0 - (1 - b)*v1)/(b - a + 1)
	 * 
	 * d(t), the distance traveled at time t, is equivalent to the area under
	 * graph of v(t), the velocity at time t, over the interval [0,t].
	 * The distance equations below are derived geometrically since our
	 * velocity curve is piecewise linear and it's area can be computed as
	 * the sums of the areas of rectangles and triangles, as shown in the
	 * diagram below.
	 * 
	 *     v
	 *     ^
	 *     |
	 *  v1 |                          +
	 *     |                         /|
	 *     |                        +-+
	 *     |                       /| |
	 *  vc |    +----------+------+-+-+
	 *     |   /|          |      | | |
	 *     |  + |          |      | | |
	 *     | /| |          |      | | |
	 *     |/ | |          |      | | |
	 *  v0 +--+-+          |      | | |
	 *     |  | |          |      | | |
	 *   0 +--+-+----------+------+-+-+----> t
	 *     0  t a          t      b t 1
	 *
	 * For implementation efficiency, curves for the accelerating intervals
	 * are algebraically transformed into standard polynomials, and the
	 * coefficients are computed once during setup.  Also, the
	 * total area up to time a and the total area up to time b are computed
	 * once during setup.
	 */
	class EaseFunction
	{
		float m_v0;
		float m_v1;
		float m_a;
		float m_b;
		float m_vc;

		/** The constant multiplier for the t^2 term of the [0,a] polynomial. */
		float m_afactor;

		/** The constant multiplier for the t^2 term of the [b,a] polynomial. */
		float m_bfactor;

		/** The total area under the velocity curve up to time a. */
		float m_atotal;

		/** The total area under the velocity curve up to time b. */
		float m_btotal;

	public:

		EaseFunction();
		EaseFunction( float v0, float v1, float a, float b );
		void setup( float v0, float v1, float a, float b );
		float operator()( float t ) const; // t in [0..1]
		float operator()( float t, float tmax ) const; // t in [0..tmax]
		float operator()( float t, float tmin, float tmax ) const; // t in [tmin..tmax]

	};

	const static EaseFunction EaseNone( 1.0f, 1.0f, 0.5f, 0.5f );
	const static EaseFunction EaseIn( 0.0f, 1.0f, 1.0f, 1.0f );
	const static EaseFunction EaseOut( 1.0f, 0.0f, 0.0f, 0.0f );
	const static EaseFunction EaseInOut( 0.0f, 0.0f, 0.5f, 0.5f );
}
