#pragma once

#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include "IShape.hpp"

namespace fl
{
	class FL_EXPORT ShapeSphere :
		public IShape
	{
	private:
		btSphereShape *m_shape;
	public:
		ShapeSphere(const float &radius = 1.0f);

		~ShapeSphere();

		void Load(LoadedValue *value) override;

		void Write(LoadedValue *destination) override;

		std::string GetName() const override { return "ShapeSphere"; };

		btCollisionShape *GetCollisionShape() const override { return m_shape; };
	};
}
