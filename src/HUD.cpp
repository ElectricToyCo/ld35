//
//  HUD.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "HUD.h"
#include "CharacterInspector.h"
#include "Character.h"
#include "PlayerConversationPanel.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( HUD )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( HUD )
	
	void HUD::inspectCharacter( SmartPtr< Character > character )
	{
		auto& inspector = getExpectedDescendant< CharacterInspector >( *this );
		
		inspector.inspectCharacter( character );
	}
	
	void HUD::toggleCharacterInspection( SmartPtr< Character > character )
	{
		auto& inspector = getExpectedDescendant< CharacterInspector >( *this );
		
		inspector.toggleCharacterInspection( character );
	}
	
	bool HUD::isInspectorShowing() const
	{
		auto& inspector = getExpectedDescendant< CharacterInspector >( *this );
		return inspector.isFullyShown();
	}
	
	void HUD::showTutorialMessage( const std::string& message )
	{
		auto& popup = getExpectedDescendant< UIPopup >( *this, "_tutorialMessage" );
		auto& text = getExpectedDescendant< TextField >( popup, "_message" );
		text.text( message );
		popup.show();
	}
	
	void HUD::hideTutorialMessage()
	{
		auto& popup = getExpectedDescendant< UIPopup >( *this, "_tutorialMessage" );
		popup.hide();
	}

	PlayerConversationPanel& HUD::playerConversationPanel() const
	{
		return getExpectedDescendant< PlayerConversationPanel >( *this, "_playerConversationPanel" );
	}
	
	bool HUD::isPlayerConversationPanelShowing() const
	{
		auto& popup = playerConversationPanel();
		return popup.isFullyShown();
	}
	
	void HUD::beginPlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character )
	{
		REQUIRES( player );
		auto& popup = playerConversationPanel();
		popup.beginPlayerInitiatedConversation( player, character );
	}
	
	void HUD::togglePlayerInitiatedConversation( SmartPtr< Character > player, SmartPtr< Character > character )
	{
		REQUIRES( player );
		auto& popup = playerConversationPanel();
		popup.togglePlayerInitiatedConversation( player, character );
	}
	
	void HUD::announceMission( const std::string& heading, const std::string& message )
	{
		auto& host = getExpectedDescendant< UIPopup >( *this, "_missionAnnouncement" );
		
		getExpectedDescendant< TextField >( host, "_heading" ).text( heading );
		getExpectedDescendant< TextField >( host, "_message" ).text( message );
		
		host.show();
		host.hideWithDuration( 1.0, false, 2.0 );
	}
}

