//
//  PlayerConversationPanel.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/17/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "PlayerConversationPanel.h"
#include "Character.h"
#include "SimpleButton.h"
#include "AppStage.h"
#include "PlayerController.h"
using namespace fr;

namespace
{
	int intForKey( Keyboard::Key key )
	{
		if( key >= Keyboard::Key::Alpha0 && key <= Keyboard::Key::Alpha9 )
		{
			return key - Keyboard::Key::Alpha0;
		}
		else if( key >= Keyboard::Key::Numpad0 && key <= Keyboard::Key::Numpad9 )
		{
			return key - Keyboard::Key::Numpad0;
		}
		return -1;
	}
}

namespace ld
{	
	FRESH_DEFINE_CLASS( PlayerConversationPanel )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( PlayerConversationPanel )

	void PlayerConversationPanel::onAddedToStage()
	{
		Super::onAddedToStage();

		stage().addEventListener( EventKeyboard::KEY_UP, FRESH_CALLBACK( onStageKeyUp ));

		auto& typeSelector = getExpectedDescendant< UIPopup >( *this, "_conversationTypeSelectorHost" );
		getExpectedDescendant< SimpleButton >( typeSelector, "_proper_opinion" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeChosen ));
		getExpectedDescendant< SimpleButton >( typeSelector, "_proper_send" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeChosen ));
		
		auto& opinionTopicSelector = getExpectedDescendant< UIPopup >( *this, "_topicHost" );
		getExpectedDescendant< SimpleButton >( opinionTopicSelector, "_food" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionTopicChosen ));
		getExpectedDescendant< SimpleButton >( opinionTopicSelector, "_sports" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionTopicChosen ));
		getExpectedDescendant< SimpleButton >( opinionTopicSelector, "_music" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionTopicChosen ));
		
		auto& opinionValueSelector = getExpectedDescendant< UIPopup >( *this, "_valueHost" );
		getExpectedDescendant< SimpleButton >( opinionValueSelector, "_hate" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionValueChosen ));
		getExpectedDescendant< SimpleButton >( opinionValueSelector, "_dislike" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionValueChosen ));
		getExpectedDescendant< SimpleButton >( opinionValueSelector, "_neutral" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionValueChosen ));
		getExpectedDescendant< SimpleButton >( opinionValueSelector, "_like" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionValueChosen ));
		getExpectedDescendant< SimpleButton >( opinionValueSelector, "_love" ).addEventListener( TAPPED, FRESH_CALLBACK( onConversationTypeOpinionValueChosen ));
	}
	
	void PlayerConversationPanel::beginPlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character )
	{
		REQUIRES( player );
		REQUIRES( character );
		
		m_player = player;
		m_conversant = character;
		

		auto& typeSelector = getExpectedDescendant< UIPopup >( *this, "_conversationTypeSelectorHost" );
		typeSelector.showWithDuration( 0 );
		
		getExpectedDescendant< UIPopup >( *this, "_topicHost" ).hiddenTranslation( vec2( 118, 0 ));
		getExpectedDescendant< UIPopup >( *this, "_topicHost" ).hideWithDuration( 0 );

		getExpectedDescendant< UIPopup >( *this, "_valueHost" ).hiddenTranslation( vec2( 118, 0 ));
		getExpectedDescendant< UIPopup >( *this, "_valueHost" ).hideWithDuration( 0 );

		show();
	}
	
	void PlayerConversationPanel::togglePlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character )
	{
		REQUIRES( player );
		
		if( isShown() )
		{
			hide();
		}
		else
		{
			beginPlayerInitiatedConversation( player, character );
		}
	}
	
	void PlayerConversationPanel::chooseConversationType( int type )
	{
		auto& typeSelector = getExpectedDescendant< UIPopup >( *this, "_conversationTypeSelectorHost" );
		typeSelector.hide();
		
		m_chosenType = type;
		
		getExpectedDescendant< UIPopup >( *this, "_topicHost" ).show();
	}

	void PlayerConversationPanel::chooseOpinionTopic( TopicType topicType )
	{
		auto& selector = getExpectedDescendant< UIPopup >( *this, "_topicHost" );
		selector.hiddenTranslation( -selector.hiddenTranslation() );
		selector.hide();
		
		m_opinionTopic = topicType;
		
		getExpectedDescendant< UIPopup >( *this, "_valueHost" ).show();
	}
	
	void PlayerConversationPanel::chooseOpinionValue( Value value )
	{
		m_opinionValue = value;
		
		// Enact this speech.
		//
		if( auto playerController = m_player->controller()->as< PlayerController >())
		{
			playerController->sayOpinion( m_conversant, std::make_pair( m_opinionTopic, -1 ), m_opinionValue );
		}
		
		hide();
	}
	
	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onStageKeyUp, fr::EventKeyboard )
	{
		if( isFullyShown() )
		{
			if( getExpectedDescendant< UIPopup >( *this, "_conversationTypeSelectorHost" ).isFullyShown() )
			{
				int type = intForKey( event.key() );
				
				if( 1 <= type && type <= 2 )		// TODO MAGIC MAX
				{
					chooseConversationType( type - 1 );
				}
			}
			else if( getExpectedDescendant< UIPopup >( *this, "_topicHost" ).isFullyShown() )
			{
				int type = intForKey( event.key() );
				
				if( 1 <= type && type <= 3 )
				{
					chooseOpinionTopic( static_cast< TopicType >( type ));
				}
			}
			else if( getExpectedDescendant< UIPopup >( *this, "_valueHost" ).isFullyShown() )
			{
				int type = intForKey( event.key() );
				
				if( 1 <= type && type <= 5 )
				{
					chooseOpinionValue( static_cast< Value >( type ));
				}
			}
		}
	}
	
	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onConversationTypeChosen, fr::EventTouch )
	{
		if( event.target()->name().find( "_opinion" ) != std::string::npos )
		{
			chooseConversationType( 0 );
		}
		else if( event.target()->name().find( "_send" ) != std::string::npos )
		{
			chooseConversationType( 1 );
		}
	}
	
	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onConversationTypeOpinionTopicChosen, fr::EventTouch )
	{
		if( event.target()->name().find( "_food" ) != std::string::npos )
		{
			chooseOpinionTopic( TopicType::Food );
		}
		else if( event.target()->name().find( "_sports" ) != std::string::npos )
		{
			chooseOpinionTopic( TopicType::Sports );
		}
		else if( event.target()->name().find( "_music" ) != std::string::npos )
		{
			chooseOpinionTopic( TopicType::Music );
		}
	}
	
	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onConversationTypeOpinionValueChosen, fr::EventTouch )
	{
		if( event.target()->name().find( "_hate" ) != std::string::npos )
		{
			chooseOpinionValue( Value::Hate );
		}
		else if( event.target()->name().find( "_dislike" ) != std::string::npos )
		{
			chooseOpinionValue( Value::Dislike );
		}
		else if( event.target()->name().find( "_neutral" ) != std::string::npos )
		{
			chooseOpinionValue( Value::Neutral );
		}
		else if( event.target()->name().find( "_like" ) != std::string::npos )
		{
			chooseOpinionValue( Value::Like );
		}
		else if( event.target()->name().find( "_love" ) != std::string::npos )
		{
			chooseOpinionValue( Value::Love );
		}
	}
	
	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onConversationTypeSendCharacterChosen, fr::EventTouch )
	{
		// TODO
	}
	
	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onConversationTypeSendTopicChosen, fr::EventTouch )
	{
		// TODO
	}
}

