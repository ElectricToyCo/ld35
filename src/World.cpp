//
//  World.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "World.h"
#include "TileGrid.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( World )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( World )
	
	TileGrid& World::tileGrid() const
	{
		return getExpectedDescendant< TileGrid >( *this, "_tileGrid" );
	}

	DisplayObjectContainer& World::actorHost() const
	{
		return getExpectedDescendant< DisplayObjectContainer >( *this, "_actorHost" );
	}
	
	void World::update()
	{
		Super::update();
		
		actorHost().sortChildren( []( const DisplayObject::ptr& a, const DisplayObject::ptr& b )
								 {
									 return a->position().y < b->position().y;
								 } );
	}
	
}

