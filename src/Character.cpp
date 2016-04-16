//
//  Character.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "Character.h"
#include "CharacterController.h"
#include "PlayerController.h"

using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( Character )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( Character )
	
	bool Character::onAddressedBy( SmartPtr< Character > initiator )
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->onAddressedBy( initiator );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->onAddressedBy( initiator );
			}
		}
		return false;
	}
	
}

