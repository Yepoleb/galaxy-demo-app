#include "PhysicsEngine.h"

using namespace gogtron;
using namespace gogtron::physics;

bool PhysicsEngine::IsPointInsideRect(std::uint32_t x, std::uint32_t y, const renderer::Sprite& sprite)
{
	return x > sprite.GetX() && x < sprite.GetX() + sprite.GetWidth()
		&& y > sprite.GetY() && y < sprite.GetY() + sprite.GetHeight();
}