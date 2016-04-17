//
//  ConversationDisplay.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_ConversationDisplay_h
#define FreshApp_ConversationDisplay_h

#include "Essentials.h"
#include "UIPopup.h"

namespace ld
{
	class Character;
	
	class ConversationDisplay : public fr::UIPopup
	{
		FRESH_DECLARE_CLASS( ConversationDisplay, UIPopup );
	public:
		
		void beginConversation( int expectedSpeeches );
		
		void showSpeech( SmartPtr< Character > speaker, const std::string& annotatedString );

		void endConversation();
		
		void interpretAnnotations( const std::string& annotatedString );
		
	private:
		
		VAR( ClassInfo::cptr, m_speechTextClass );
		VAR( ClassInfo::cptr, m_speechPopupClass );
		VAR( vec2, m_speechTextOffset );
		VAR( vec2, m_speechSpacing );
		DVAR( TimeType, m_showTextDuration, 8.0 );
		
		int m_nExpectedSpeeches = 0;
		int m_nSpeeches = 0;
	};
	
}

#endif
