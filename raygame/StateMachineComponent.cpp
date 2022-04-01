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
/// While the player is not in range the enemy wanders 
/// Starts to pathfind if the player enters its range
/// Starts to seek if the player enters the smaller range
/// </summary>
/// <param name="deltaTime"></param>
void StateMachineComponent::update(float deltaTime)
{
	Component::update(deltaTime);

	MathLibrary::Vector2 targetPos = m_seekComponent->getTarget()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 ownerPos = getOwner()->getTransform()->getWorldPosition();
	float distanceFromTarget = (targetPos - ownerPos).getMagnitude();

	//The distances from the target based on different ranges
	bool targetInRange = distanceFromTarget <= m_seekRange;
	bool targetInPathRange = distanceFromTarget <= m_pathFindRange;

	switch (m_currentState)
	{
	case PATHFIND:
		//Sets the steering forces 
		m_seekComponent->setSteeringForce(0);
		m_wanderComponent->setSteeringForce(0);
		m_pathFindComponent->setEnabled(true);

		//only steps into wander if its not in range
		if (!targetInRange)
			setCurrentState(WANDER);
		//only steps into seek if it is in the range
		if (targetInPathRange)
			setCurrentState(SEEK);
		break;
	case WANDER:
		//Sets the steering forces 
		m_seekComponent->setSteeringForce(30);
		m_wanderComponent->setSteeringForce(m_wanderForce);
		m_pathFindComponent->setEnabled(false);

		//only steps into pathFind if it is in the range
		if (targetInPathRange)
			setCurrentState(PATHFIND);
		//only steps into seek if it is in the range
		if(targetInRange)
			setCurrentState(SEEK);

		break;
	case SEEK:
		//Sets the steering forces 
		m_seekComponent->setSteeringForce(m_seekForce);
		m_wanderComponent->setSteeringForce(0);
		m_pathFindComponent->setEnabled(false);

		//only steps into pathfind if its not in range
		if (!targetInPathRange)
			setCurrentState(PATHFIND);
		break;
	}
}
