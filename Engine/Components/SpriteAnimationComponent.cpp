#include "pch.h"
#include "Graphics/Texture.h"
#include "SpriteAnimationComponent.h"

void nc::SpriteAnimationComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
}

void nc::SpriteAnimationComponent::Destroy()
{
}

void nc::SpriteAnimationComponent::Read(const rapidjson::Value& value)
{
	SpriteComponent::Read(value);

	json::Get(value, "numX", m_numX);
	json::Get(value, "numY", m_numY);
	json::Get(value, "numFrames", m_numFrames);
	json::Get(value, "fps", m_fps);

	m_frameRate = 1.0f / m_fps;
}

void nc::SpriteAnimationComponent::Update()
{
	// update frame timer
	m_frameTimer += m_owner->m_engine->GetTimer().DeltaTime();
	if (m_frameTimer >= m_frameRate)
	{
		m_frameTimer = 0;
		m_frame++;
		if (m_frame >= m_numFrames)
		{
			m_frame = 0;
		}
	}

	// update frame rect
	Texture* texture = m_owner->m_engine->GetSystem<ResourceManager>()->Get<Texture>(m_textureName, m_owner->m_engine->GetSystem<Renderer>());
	Vector2 textureSize = texture->GetSize();

	Vector2 cellCount{ m_numX, m_numY };
	Vector2 cellSize = textureSize / cellCount;

	m_rect.x = static_cast<int>((m_frame % m_numX) * cellSize.x);
	m_rect.y = static_cast<int>((m_frame / m_numX) * cellSize.x);
	m_rect.w = static_cast<int>(cellSize.x);
	m_rect.h = static_cast<int>(cellSize.y);
}