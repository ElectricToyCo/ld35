//
//  Character.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_Character_h
#define FreshApp_Character_h

#include "Essentials.h"
#include "Actor.h"

namespace ld
{
	class ConversationDisplay;
	
	class Character : public Actor
	{
		FRESH_DECLARE_CLASS( Character, Actor );
	public:
		
		virtual bool onAddressedBy( SmartPtr< Character > initator );
		virtual void onConversationEnding();
	
		void receiveSpeechStatement( SmartPtr< ConversationDisplay > display, Character& from, const Topic& topic, real value, size_t speechIndex );
		void displaySpeech( SmartPtr< ConversationDisplay > display, Topic topic, real value, size_t speechIndex );
		
		virtual std::string characterName() const;
		
	private:
		
		VAR( std::string, m_characterName );
		
	};
	
}

#endif
