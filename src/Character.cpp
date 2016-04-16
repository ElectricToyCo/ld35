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
#include "ConversationDisplay.h"

using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( Character )
	DEFINE_VAR( Character, std::string, m_characterName );
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
	
	void Character::onConversationEnding()
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->onConversationEnding();
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->onConversationEnding();
			}
		}
	}
	
	void Character::receiveSpeechStatement( SmartPtr< ConversationDisplay > display, Character& from, const Topic& topic, real value, size_t speechIndex )
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->receiveSpeechStatement( display, from, topic, value, speechIndex );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->receiveSpeechStatement( display, from, topic, value, speechIndex );
			}
		}
	}

	void Character::displaySpeech( SmartPtr< ConversationDisplay > display, Topic topic, real value, size_t speechIndex )
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->displaySpeech( display, topic, value, speechIndex );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->displaySpeech( display, topic, value, speechIndex );
			}
		}
	}

	std::string Character::characterName() const
	{
		return m_characterName;
	}
	

}

