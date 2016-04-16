//
//  Actor.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_Actor_h
#define FreshApp_Actor_h

#include "Essentials.h"
#include "FreshActor.h"
#include "FreshActorController.h"
#include "TileGrid.h"

namespace ld
{
	class World;
	
	class Actor : public fr::FreshActor
	{
		FRESH_DECLARE_CLASS( Actor, FreshActor );
	public:
		
		World& world() const;
		
		bool travelTo( const vec2& pos );
		void stopTravel();
		
		virtual void update() override;
		
		real coarseCollisionRadius() const;
		
		size_t currentRoom() const;
		
	private:

		VAR( TileGrid::WorldSpacePath, m_path );
		DVAR( size_t, m_nextPathDestination, 0 );
	};
	
}

#endif
