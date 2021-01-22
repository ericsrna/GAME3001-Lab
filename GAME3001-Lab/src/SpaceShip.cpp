#include "SpaceShip.h"

SpaceShip::SpaceShip():m_maxSpeed(10.0f)
{
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);
	//setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y,
		m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 60.0f));
}

void SpaceShip::update()
{
	m_Move();
}

void SpaceShip::clean()
{
}

void SpaceShip::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void SpaceShip::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void SpaceShip::setRotation(float angle)
{
	m_rotationAngle = angle;
}

float SpaceShip::getRotation() const
{
	return m_rotationAngle;
}

void SpaceShip::m_Move()
{
	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;
	
	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}