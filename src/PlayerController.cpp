//
//  PlayerController.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "PlayerController.h"
#include "World.h"
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
	
	void PlayerController::onConversationEnding()
	{
		// TODO
	}
	
	void PlayerController::onActionKeyDown( Keyboard::Key key )
	{
		switch( key )
		{
			case Keyboard::Space:
				attemptInitiatingConversation();
				break;
			default:
				break;
		}
	}
	
	void PlayerController::onActionButtonDown( Gamepad::Button button )
	{
		// TODO!!! map to key
	}
	
	void PlayerController::attemptInitiatingConversation()
	{
		// Find the character I want to talk to.
		//
		const auto& me = character();
		const auto myPosition = me.position();
		auto addressee = character().world().bestCharacter( [&]( const Character& character )
														   {
															   if( &character == &me )
															   {
																   return -1.0f;
															   }
															   else
															   {
																   const auto distSquared = distanceSquared( character.position(), myPosition );
																   return 1.0f / ( distSquared > 0 ? distSquared : 0.1f );
															   }
														   } );
		
		if( addressee )
		{
			beginConversationWith( addressee );
		}
	}
	
	void PlayerController::beginConversationWith( SmartPtr< Character > other )
	{
		ASSERT( other );
		
		auto me = &character();
		
		ASSERT( other != me );
		
		other->onAddressedBy( me );
		
		// TODO!!!
	}
}

