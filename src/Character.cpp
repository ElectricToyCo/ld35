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

	Topic Character::pickTopic( const Character& forUseWithCharacter ) const
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->pickTopic( forUseWithCharacter );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->pickTopic( forUseWithCharacter );
			}
		}
		return std::make_pair( TopicType::Undecided, -1 );
	}

	Value Character::pickTopicResponse( const Character& forUseWithCharacter, const Topic& topic ) const
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->pickTopicResponse( forUseWithCharacter, topic );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->pickTopicResponse( forUseWithCharacter, topic );
			}
		}
		return Value::Undecided;
	}

	Value Character::valueForTopic( const Character& forUseWithCharacter, const Topic& topic ) const
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->valueForTopic( forUseWithCharacter, topic );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->valueForTopic( forUseWithCharacter, topic );
			}
		}
		return Value::Undecided;
	}

	std::string Character::getOpinionInitiatingText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->getOpinionInitiatingText( forUseWithCharacter, topic, value );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->getOpinionInitiatingText( forUseWithCharacter, topic, value );
			}
		}
		return {};
	}

	std::string Character::getOpinionResponseText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->getOpinionResponseText( forUseWithCharacter, topic, value );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->getOpinionResponseText( forUseWithCharacter, topic, value );
			}
		}
		return {};
	}

	void Character::hearSpeech( const Character& fromCharacter, const Topic& topic, Value value )
	{
		if( controller() )
		{
			if( auto playerController = controller()->as< PlayerController >() )
			{
				return playerController->hearSpeech( fromCharacter, topic, value );
			}
			else if( auto characterController = controller()->as< CharacterController >() )
			{
				return characterController->hearSpeech( fromCharacter, topic, value );
			}
		}
	}


	std::string Character::characterName() const
	{
		return m_characterName;
	}
}

