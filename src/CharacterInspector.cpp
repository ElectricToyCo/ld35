//
//  CharacterInspector.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "CharacterInspector.h"
#include "Character.h"
#include "TextField.h"
#include "UIPopup.h"
#include "DisplayObjectProxy.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( CharacterInspector )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( CharacterInspector )
	
	void CharacterInspector::update()
	{
		Super::update();
		
		if( m_character )
		{
			const auto showTopic = [&]( TopicType type, const std::string& displayName )
			{
				auto value = m_character->valueForTopic( *m_character, std::make_pair( type, -1 ));
				
				if( auto display = getDescendantByName< Sprite >( displayName ))
				{
					display->setTextureByName( textureNameForValue( value ));
				}
			};
			
			// TODO!!! Create these with their unchanging topic indicators.
			showTopic( TopicType::Food, "_food" );
			showTopic( TopicType::Sports, "_sports" );
			showTopic( TopicType::Music, "_music" );
			
			// Show per-character values.
			//
			// TODO
		}
	}
	
	void CharacterInspector::inspectCharacter( SmartPtr< Character > character )
	{
		// Prior character?
		//
		if( m_character )
		{
			m_character->unhighlight();
		}
		
		m_character = character;
		
		if( m_character )
		{
			show();
			m_character->highlight();
			
			getExpectedDescendant< DisplayObjectProxy >( *this, "_proxyProper" ).object( m_character->visual() );
			getExpectedDescendant< DisplayObjectProxy >( *this, "_proxyShadow" ).object( m_character->visual() );
			
			getExpectedDescendant< TextField >( *this, "_charName" ).text( m_character ? m_character->characterName() : "-" );
		}
		else
		{
			hide();
		}

	}

	void CharacterInspector::toggleCharacterInspection( SmartPtr< Character > character )
	{
		if( isShown() )
		{
			hide();
		}
		else
		{
			inspectCharacter( character );
		}
	}
	
	void CharacterInspector::hideWithDuration( TimeType duration, bool deleteWhenHidden, TimeType queueIfShowingWithDelay )
	{
		Super::hideWithDuration( duration, deleteWhenHidden, queueIfShowingWithDelay );
		
		if( m_character )
		{
			m_character->unhighlight();
			m_character = nullptr;
		}
	}
}

