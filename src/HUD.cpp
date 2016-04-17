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
}

