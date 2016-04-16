//
//  CharacterController.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "CharacterController.h"
#include "Actor.h"
#include "World.h"
#include "TileGrid.h"
using namespace fr;

namespace
{
	using namespace ld;
	const real MAX_WANDER_DISTANCE = 4 * UNITS_PER_TILE;
}

namespace ld
{	
	FRESH_DEFINE_CLASS( CharacterController )
	DEFINE_DVAR( CharacterController, State, m_state );
	DEFINE_DVAR( CharacterController, TimeType, m_nextWanderTime );
	DEFINE_DVAR( CharacterController, Range< TimeType >, m_wanderDelayRange );

	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( CharacterController )
	
	Actor& CharacterController::actor() const
	{
		ASSERT( dynamic_cast< Actor* >( host().get() ));
		auto actor = static_cast< Actor* >( host().get() );
		ASSERT( actor );
		return *actor;
	}
	
	void CharacterController::update()
	{
		switch( m_state )
		{
			case Idle:
				updateIdle();
				break;
			case Pursuing:
				updatePursuing();
				break;
			case Talking:
				updateTalking();
				break;
			case Panicked:
				updatePanicked();
				break;
		}
		
		Super::update();
	}
	
	void CharacterController::updateIdle()
	{
		const auto now = actor().world().time();
		
		// Wander around.
		//
		if( m_nextWanderTime < 0 || now >= m_nextWanderTime )
		{
			wanderSomewhere();
		}
	}
	
	void CharacterController::updatePursuing()
	{
		// Move near the target character.
		//
		// TODO
	}
	
	void CharacterController::updateTalking()
	{
		// Stand here.
		// TODO
	}
	
	void CharacterController::updatePanicked()
	{
		// Run away from the repulsive character (the player).
		//
		// TODO
	}
	
	void CharacterController::wanderSomewhere()
	{
		const World& world = actor().world();
		const TileGrid& tileGrid = world.tileGrid();
		
		// Pick a new destination that is not too far from my current position, and not in a wall.
		//
		for( size_t tries = 0; tries < 10; ++tries )
		{
			const auto newPos = actor().position() + makeRandomVector2( MAX_WANDER_DISTANCE );
			
			if( tileGrid.isInBounds( newPos ) && tileGrid.getTile( newPos ).isSolid() == false )
			{
				// Found a good one. Use it.
				// TODO!!! Verify in the same room, or path not too long.
				//
				actor().travelTo( newPos );
				
				m_nextWanderTime = world.time() + randInRange( m_wanderDelayRange );
				break;
			}
		}
	}
}

