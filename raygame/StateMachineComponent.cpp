#include "StateMachineComponent.h"
#include "Actor.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "PathfindComponent.h"
#include "Transform2D.h"

void StateMachineComponent::start()
{
	Component::start();

	m_seekComponent = getOwner()->getComponent<SeekComponent>();
	m_seekForce = m_seekComponent->getSteeringForce();

	m_wanderComponent = getOwner()->getComponent<WanderComponent>();
	m_wanderForce = m_wanderComponent->getSteeringForce();

	m_pathFindComponent = getOwner()->getComponent<PathfindComponent>();

	m_currentState = WANDER;
}

/// <summary>
/// Mixed pathFinding with seek and wander
/// </summary>
/// <param name="deltaTime"></param>
void StateMachineComponent::update(float deltaTime)
{
	Component::update(deltaTime);

	MathLibrary::Vector2 targetPos = m_seekComponent->getTarget()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 ownerPos = getOwner()->getTransform()->getWorldPosition();
	float distanceFromTarget = (targetPos - ownerPos).getMagnitude();

	bool targetInRange = distanceFromTarget <= m_seekRange;
	bool targetInPathRange = distanceFromTarget <= m_pathFindRange;

	switch (m_currentState)
	{
	case PATHFIND:
		m_seekComponent->setSteeringForce(0);
		m_wanderComponent->setSteeringForce(0);
		m_pathFindComponent->setEnabled(true);

		if (!targetInRange)
			setCurrentState(WANDER);
		if (targetInPathRange)
			setCurrentState(SEEK);
		break;
	case WANDER:
		m_seekComponent->setSteeringForce(30);
		m_wanderComponent->setSteeringForce(m_wanderForce);
		m_pathFindComponent->setEnabled(false);

		if (targetInPathRange)
			setCurrentState(PATHFIND);
		if(targetInRange)
			setCurrentState(SEEK);

		break;
	case SEEK:
		m_seekComponent->setSteeringForce(m_seekForce);
		m_wanderComponent->setSteeringForce(0);
		m_pathFindComponent->setEnabled(false);

		if (!targetInPathRange)
			setCurrentState(PATHFIND);
		break;
	}
}
