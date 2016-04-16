//
//  PlayerController.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "PlayerController.h"
#include "Character.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( PlayerController )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( PlayerController )
	
	Character& PlayerController::character() const
	{
		ASSERT( dynamic_cast< Character* >( host().get() ));
		auto character = static_cast< Character* >( host().get() );
		ASSERT( character );
		return *character;
	}
	
	bool PlayerController::onAddressedBy( SmartPtr< Character > other )
	{
		REQUIRES( other );
		REQUIRES( other != &character() );

		// TODO!!!
		
		return false;		// TODO!!!
	}
}

