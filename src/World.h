//
//  World.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_World_h
#define FreshApp_World_h

#include "Essentials.h"
#include "FreshWorld.h"
#include "Camera.h"

namespace ld
{
	class TileGrid;
	class Character;
	
	class World : public fr::FreshWorld
	{
		FRESH_DECLARE_CLASS( World, FreshWorld );
	public:
		
		TileGrid& tileGrid() const;
		DisplayObjectContainer& actorHost() const;
		
		virtual void update() override;

		// ROOMS
		
		size_t numRooms() const;
		size_t roomContainingPoint( const vec2& p ) const;		// Returns -1 if none.
		size_t randomRoom( size_t excludedRoom = -1 ) const;
		
		vec2 randomPointInRoom( size_t room ) const;

		SmartPtr< Character > bestCharacter( std::function< real( const Character& ) >&& scoringFunction );
		
	private:
		
		VAR( std::vector< rect >, m_roomRects );
		
	};
	
}

#endif
