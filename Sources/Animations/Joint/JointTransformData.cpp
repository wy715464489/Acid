#include "JointTransformData.hpp"

namespace fl
{
	JointTransformData::JointTransformData(const std::string &jointNameId, const Matrix4 &jointLocalTransform) :
		m_jointNameId(jointNameId),
		m_jointLocalTransform(new Matrix4(jointLocalTransform))
	{
	}

	JointTransformData::~JointTransformData()
	{
		delete m_jointLocalTransform;
	}
}
