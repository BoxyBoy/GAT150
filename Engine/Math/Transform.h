#pragma once
#include "Vector2.h"
#include "Matrix33.h"

namespace nc
{
	struct Transform
	{
		Vector2 position;
		float scale{ 1 };
		float angle{ 0 };

		Matrix33 matrix;
		
		Transform() : position{ 0,0 }, scale{ 1 }, angle{ 0 } {}
		Transform(Vector2 position, float scale = 1.0f, float angle = 0.0f) : position{ position }, scale{ scale }, angle{ angle } {}

		void Update();
		void Update(const Matrix33& mx);

		friend std::istream& operator >> (std::istream& stream, Transform& transform);

	};
}
