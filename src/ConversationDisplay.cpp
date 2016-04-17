//
//  ConversationDisplay.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "ConversationDisplay.h"
#include "Character.h"
#include "TextField.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( ConversationDisplay )
	DEFINE_VAR( ConversationDisplay, ClassInfo::cptr, m_speechTextClass );
	DEFINE_VAR( ConversationDisplay, vec2, m_speechTextOffset );
	DEFINE_VAR( ConversationDisplay, vec2, m_speechSpacing );
	DEFINE_DVAR( ConversationDisplay, TimeType, m_showTextDuration );

	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( ConversationDisplay )

	void ConversationDisplay::beginConversation( int expectedSpeeches )
	{
		m_nExpectedSpeeches = expectedSpeeches;
		m_nSpeeches = 0;
	}
	
	void ConversationDisplay::showSpeech( SmartPtr< Character > speaker, const std::string& annotatedString )
	{
		REQUIRES( speaker );
		
		dev_trace( speaker->characterName() << " says, \"" << annotatedString << "\"" );

		ASSERT( m_speechTextClass );

		auto textField = createObject< TextField >( *m_speechTextClass );
		ASSERT( textField );
		
		std::string displayString = annotatedString;
		interpretAnnotations( displayString );
		
		textField->text( displayString );
		
		addChild( textField );
		textField->position( speaker->position() + m_speechTextOffset + m_speechSpacing * ( -m_nExpectedSpeeches + m_nSpeeches ));
		
		show();
		hideWithDuration( m_showTextDuration, false, true );
		
		++m_nSpeeches;
	}
	
	void ConversationDisplay::endConversation()
	{
		// TODO
		hide();
	}
	
	void ConversationDisplay::interpretAnnotations( const std::string& annotatedString )
	{
		// TODO
	}
}

