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

#if 0
#	define ai_trace( x ) dev_trace( x )
#else
#	define ai_trace( x )
#endif


namespace ld
{	
	FRESH_DEFINE_CLASS( CharacterController )
	DEFINE_DVAR( CharacterController, State, m_state );
	DEFINE_DVAR( CharacterController, TimeType, m_nextWanderTime );
	DEFINE_DVAR( CharacterController, Range< TimeType >, m_wanderDelayRange );
	DEFINE_DVAR( CharacterController, real, m_percentChanceWanderToNewRoom );
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

		// Should I go to a whole new room?
		//
		const auto wantNewRoom = pctChance( m_percentChanceWanderToNewRoom );
		const bool wantNonRoom = wantNewRoom && pctChance( 10 );

		for( size_t tries = 0; tries < 4; ++tries )
		{
			// Pick a new destination that is not too far from my current position, and not in a wall.
			//
			vec2 desiredPosition = actor().position();
			const auto currentRoom = world.roomContainingPoint( desiredPosition );	// Might return -1.
			size_t desiredRoom = currentRoom;

			if( wantNewRoom && !wantNonRoom )
			{
				desiredRoom = world.randomRoom( currentRoom );
				
				ai_trace( "Going to new room " << desiredRoom );
				desiredPosition = world.randomPointInRoom( desiredRoom );
			}
			else
			{
				if( wantNonRoom )
				{
					// Be willing to go to a non-room, like a bathroom or hall.
					//
					desiredRoom = -1;
				}
				
				desiredPosition = actor().position() + makeRandomVector2( MAX_WANDER_DISTANCE );
			}
			
			ai_trace( "Trying destination " << desiredPosition );
			
			const auto newPos = tileGrid.findClearLocationNearby( desiredPosition, 3.0 * UNITS_PER_TILE, [&]( const vec2& p )
																 {
																	 const auto newRoom = world.roomContainingPoint( p );
																	 if( desiredRoom != -1 && desiredRoom != newRoom )
																	 {
																		 return 0.0f;	// Give it no score.
																	 }
																	 
																	 const auto dist = distance( p, desiredPosition );
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
				// Make sure the new position is in the desired room.
				//
				const auto newRoom = world.roomContainingPoint( newPos );
				if( desiredRoom != -1 && desiredRoom != newRoom )
				{
					// Not cool.
					continue;
				}
				
				ai_trace( "Found new destination: " << newPos );
				
				// Found a good one. Use it.
				// TODO!!! Verify in the same room, or path not too long.
				//
				bool foundPath = actor().travelTo( newPos );
				if( foundPath )
				{
					m_nextWanderTime = world.time() + 30.0;		// Escape clause just in case onTravelCompleted is never called.
					break;
				}
			}
			else
			{
				ai_trace( "Found no valid destination near: " << desiredPosition );
			}
		}
		ai_trace( "Done (maybe gave up) finding a wander destination." );
	}
	
	void CharacterController::onTravelCompleted()
	{
		m_nextWanderTime = actor().world().time() + randInRange( m_wanderDelayRange );
	}
}

