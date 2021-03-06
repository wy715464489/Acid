#include "FilterCrt.hpp"

#include "Display/Display.hpp"

namespace acid
{
	FilterCrt::FilterCrt(const GraphicsStage &graphicsStage) :
		IPostFilter(graphicsStage, {"Shaders/Filters/Default.vert", "Shaders/Filters/Crt.frag"}, {}),
		m_uniformScene(UniformHandler()),
		m_screenColour(Colour(0.5f, 1.0f, 0.5f)),
		m_curveAmountX(0.1f),
		m_curveAmountY(0.1f),
		m_scanLineSize(1000.0f),
		m_scanIntensity(0.1f)
	{
	}

	void FilterCrt::Render(const CommandBuffer &commandBuffer, const Vector4 &clipPlane, const ICamera &camera)
	{
		// Updates uniforms.
		m_uniformScene.Push("screenColour", m_screenColour);
		m_uniformScene.Push("curveAmountX", m_curveAmountX * Display::Get()->GetAspectRatio());
		m_uniformScene.Push("curveAmountY", m_curveAmountY);
		m_uniformScene.Push("scanLineSize", m_scanLineSize);
		m_uniformScene.Push("scanIntensity", m_scanIntensity);
		m_uniformScene.Push("moveTime", Engine::Get()->GetTime() / 100.0f);

		// Updates descriptors.
		m_descriptorSet.Push("UboScene", &m_uniformScene);
		m_descriptorSet.Push("writeColour", m_pipeline.GetTexture(5));
		m_descriptorSet.Push("samplerColour", m_pipeline.GetTexture(5));
		bool updateSuccess = m_descriptorSet.Update(m_pipeline);

		if (!updateSuccess)
		{
			return;
		}

		// Draws the object.
		m_pipeline.BindPipeline(commandBuffer);

		m_descriptorSet.BindDescriptor(commandBuffer);
		m_model->CmdRender(commandBuffer);
	}
}
