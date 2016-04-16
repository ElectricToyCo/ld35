//
//  PlayerController.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_PlayerController_h
#define FreshApp_PlayerController_h

#include "Essentials.h"
#include "FreshPlayerController.h"

namespace ld
{
	class Character;
	class ConversationDisplay;
	
	class PlayerController : public fr::FreshPlayerController
	{
		FRESH_DECLARE_CLASS( PlayerController, fr::FreshPlayerController );
	public:
		
		Character& character() const;
		
		bool onAddressedBy( SmartPtr< Character > other );
		void onConversationEnding();
		void receiveSpeechStatement( SmartPtr< ConversationDisplay > display, Character& from, const Topic& topic, real value, size_t speechIndex );
		void displaySpeech( SmartPtr< ConversationDisplay > display, Topic topic, real value, size_t speechIndex );

	protected:
		
		virtual void onActionKeyDown( fr::Keyboard::Key key ) override;
		virtual void onActionButtonDown( fr::Gamepad::Button button ) override;

		void attemptInitiatingConversation();
		void beginConversationWith( SmartPtr< Character > other );

	private:
		
	};
	
}

#endif
