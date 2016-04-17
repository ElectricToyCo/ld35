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
	}
	
	void PlayerConversationPanel::beginPlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character )
	{
		REQUIRES( player );
		REQUIRES( character );
		
		m_player = player;
		m_conversant = character;
		

		auto& typeSelector = getExpectedDescendant< UIPopup >( *this, "_conversationTypeSelectorHost" );
		typeSelector.showWithDuration( 0 );
		
		getExpectedDescendant< UIPopup >( *this, "_opinionHost" ).hideWithDuration( 0 );
		
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
		
		getExpectedDescendant< UIPopup >( *this, "_opinionHost" ).show();
	}

	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onStageKeyUp, fr::EventKeyboard )
	{
		if( isFullyShown() && getExpectedDescendant< UIPopup >( *this, "_conversationTypeSelectorHost" ).isFullyShown() )
		{
			int type = intForKey( event.key() );
			
			if( type != -1 )
			{
				chooseConversationType( type );
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
		// TODO
	}
	
	FRESH_DEFINE_CALLBACK( PlayerConversationPanel, onConversationTypeOpinionValueChosen, fr::EventTouch )
	{
		// TODO
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

