/*=====================================================================
Code By Nicholas Chapman.

  nickamy@paradise.net.nz

You may use this code for any non-commercial project,
as long as you do not remove this description.

You may *not* use this code for any commercial project.
=====================================================================*/
#ifndef __COLOUR_H__
#define __COLOUR_H__

//#include "../utils/random.h"

//namespace RayT
//{

class Colour
{
public:
	Colour(){}

	Colour(float r_, float g_, float b_)
	:	r(r_), g(g_), b(b_) 
	{}

	Colour(const Colour& rhs)
	:	r(rhs.r),
		g(rhs.g),
		b(rhs.b)
	{}

	~Colour(){}

	static Colour red()		{	return Colour(1.0f ,0.0f ,0.0f); }
	static Colour green()	{	return Colour(0.0f ,1.0f ,0.0f); }
	static Colour blue() 	{	return Colour(0.0f ,0.0f ,1.0f); }
	static Colour grey()	{	return Colour(0.5f ,0.5f ,0.5f); }
	static Colour yellow()	{	return Colour(0.0f ,1.0f ,1.0f); }

	inline void set(float r_, float g_, float b_)
	{
		r = r_;
		g = g_;
		b = b_;
	}

	inline Colour operator * (float scale) const
	{
		return Colour(r * scale, g * scale, b * scale);
	}

	inline Colour& operator *= (float scale)
	{
		r *= scale;
		g *= scale;
		b *= scale;

		return *this;
	}

	inline Colour operator + (const Colour& rhs) const
	{
		return Colour(r + rhs.r, g + rhs.g, b + rhs.b);
	}

	inline void operator = (const Colour& rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
	}

	inline void operator += (const Colour& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
	}

	inline Colour& operator *= (const Colour& rhs)
	{
		r *= rhs.r;
		g *= rhs.g;
		b *= rhs.b;
	
		return *this;
	}

	inline const Colour operator * (const Colour& rhs) const
	{
		return Colour(r * rhs.r, g * rhs.g, b * rhs.b);
	}

	inline void setToMult(const Colour& other, float factor)
	{
		r = other.r * factor;
		g = other.g * factor;
		b = other.b * factor;
	}

	inline void addMult(const Colour& other, float factor)
	{
		r += other.r * factor;
		g += other.g * factor;
		b += other.b * factor;
	}

	inline void add(const Colour& other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
	}

	inline void clipComponents()
	{
		if(r < 0.0f)
			r = 0.0f;
		else if(r > 1.0f)
			r = 1.0f;

		if(g < 0.0f)
			g = 0.0f;
		else if(g > 1.0f)
			g = 1.0f;

		if(b < 0.0f)
			b = 0.0f;
		else if(b > 1.0f)
			b = 1.0f;
	}

    inline void positiveClipComponents()
	{
		if(r > 1.0f)
			r = 1.0f;

		if(g > 1.0f)
			g = 1.0f;

		if(b > 1.0f)
			b = 1.0f;
	}

	/*static inline const Colour randomColour()
	{
		return Colour(Random::unit(), Random::unit(), Random::unit());
	}*/

	const float* toFloatArray() const { return (const float*)this; }
	const float* data() const { return (const float*)this; }
	

	float r,g,b;
};



//}//end namespace RayT

#endif //__COLOUR_H__