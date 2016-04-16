//
//  CharacterController.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "CharacterController.h"
#include "Actor.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( CharacterController )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( CharacterController )
	
	Actor& CharacterController::actor() const
	{
		auto actor = static_cast< Actor* >( host().get() );
		ASSERT( actor );
		return *actor;
	}
	
	void CharacterController::update()
	{
		
		
		Super::update();
	}
	
}

