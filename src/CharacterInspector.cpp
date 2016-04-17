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
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( CharacterInspector )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( CharacterInspector )
	
	void CharacterInspector::inspectCharacter( SmartPtr< Character > character )
	{
		m_character = character;
		
		if( auto popup = firstAncestorOfType< UIPopup >( *this ))
		{
			if( m_character )
			{
				popup->show();
			}
			else
			{
				popup->hide();
			}
		}
		
		getExpectedDescendant< TextField >( *this, "_charName" ).text( m_character ? m_character->characterName() : "-" );
	}

	void CharacterInspector::drawChildren( TimeType relativeFrameTime, RenderInjector* injector )
	{
		Renderer::instance().pushMatrix();
		Renderer::instance().pushColor();
		
		Renderer::instance().translate( 0, -72 );
		Renderer::instance().scale( vec2( 2 ));
		Renderer::instance().multiplyColor( Color::DarkGray );
		m_character->draw( relativeFrameTime, injector );
		Renderer::instance().popColor();
		
		Renderer::instance().translate( 0, -1 );
		m_character->draw( relativeFrameTime, injector );

		Renderer::instance().popMatrix();
		
		Super::drawChildren( relativeFrameTime, injector );
	}
}

