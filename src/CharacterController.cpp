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
		
		for( size_t tries = 0; tries < 4; ++tries )
		{
			// Pick a new destination that is not too far from my current position, and not in a wall.
			//
			const auto randomPosition = actor().position() + makeRandomVector2( MAX_WANDER_DISTANCE );
			
			dev_trace( "Trying random destination " << randomPosition );
			
			const auto newPos = tileGrid.findClearLocationNearby( randomPosition, 3.0 * UNITS_PER_TILE, [&]( const vec2& p )
																 {
																	 const auto dist = distance( p, randomPosition );
																	 if( dist > 0 )
																	 {
																		 return 1.0f / dist;
																	 }
																	 else
																	 {
																		 return 1000.0f;
																	 }
																 } );

			if( newPos.x >= 0 && newPos.y >= 0 )
			{
				dev_trace( "Found new destination: " << newPos );
				
				// Found a good one. Use it.
				// TODO!!! Verify in the same room, or path not too long.
				//
				bool foundPath = actor().travelTo( newPos );
				if( foundPath )
				{
					m_nextWanderTime = world.time() + randInRange( m_wanderDelayRange );
					break;
				}
			}
			else
			{
				dev_trace( "Found no valid destination near: " << randomPosition );
			}
		}
		dev_trace( "Done (maybe gave up) finding a wander destination." );
	}
}

