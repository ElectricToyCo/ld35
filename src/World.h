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
	
	class World : public fr::FreshWorld
	{
		FRESH_DECLARE_CLASS( World, FreshWorld );
	public:
		
		TileGrid& tileGrid() const;
		DisplayObjectContainer& actorHost() const;
		
		virtual void update() override;
		
	private:
		
	};
	
}

#endif
