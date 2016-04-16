//
//  Actor.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "Actor.h"
#include "World.h"
using namespace fr;

namespace
{
	using namespace ld;
	const real MAX_TOUCH_PATH_NODE_DISTANCE = 0.75f * UNITS_PER_TILE;
	const real MAX_TOUCH_PATH_NODE_DISTANCE_SQUARED = MAX_TOUCH_PATH_NODE_DISTANCE * MAX_TOUCH_PATH_NODE_DISTANCE;
}

namespace ld
{	
	FRESH_DEFINE_CLASS( Actor )
	DEFINE_VAR( Actor, TileGrid::WorldSpacePath, m_path );
	DEFINE_DVAR( Actor, size_t, m_nextPathDestination );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( Actor )
	
	World& Actor::world() const
	{
		return static_cast< World& >( FreshActor::world() );
	}

	void Actor::travelTo( const vec2& pos )
	{
		const World& theWorld = world();
		TileGrid& tileGrid = theWorld.tileGrid();
		
		m_nextPathDestination = 0;
		const auto didFind = tileGrid.findClosestPath( position(), pos, m_path, coarseCollisionRadius() );
		
		if( didFind )
		{
			// Smooth?
			//
			tileGrid.smoothPath( m_path, position(), coarseCollisionRadius(), MAX_TOUCH_PATH_NODE_DISTANCE_SQUARED );
		}
	}

	void Actor::update()
	{
		Super::update();
		
		while( m_nextPathDestination < m_path.size() )
		{
			const auto currentDestination = m_path[ m_nextPathDestination ];
			
			// Move to the current destination.
			//
			const auto delta = currentDestination - position();
			
			// Reached it?
			//
			const auto distSquared = delta.lengthSquared();
			
			if( distSquared <= MAX_TOUCH_PATH_NODE_DISTANCE_SQUARED )
			{
				// Yes.
				//
				++m_nextPathDestination;
				continue;
			}
			else
			{
				const auto normal = delta / std::sqrt( distSquared );
				applyControllerImpulse( normal );
				
				break;
			}
		}
	}
	
	real Actor::coarseCollisionRadius() const
	{
		return std::abs( dimensions().majorAxisValue() );
	}
}

