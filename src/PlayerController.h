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
		
		bool occupied() const;
		
		bool onAddressedBy( SmartPtr< Character > other );
		void onConversationBeginning();
		void onConversationEnding();

		virtual Topic pickTopic( const Character& forUseWithCharacter ) const;
		virtual Value pickTopicResponse( const Character& forUseWithCharacter, const Topic& topic ) const;

		virtual Value valueForTopic( const Character& forUseWithCharacter, const Topic& topic ) const;
		virtual std::string getOpinionInitiatingText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const;
		virtual std::string getOpinionResponseText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const;
		
		virtual void hearSpeech( const Character& fromCharacter, const Topic& topic, Value value );

	protected:
		
		virtual void onActionKeyDown( fr::Keyboard::Key key ) override;
		virtual void onActionButtonDown( fr::Gamepad::Button button ) override;

		void attemptInitiatingConversation();
		void toggleInspectNearest();
		void beginConversationWith( SmartPtr< Character > other );

	private:
		
	};
	
}

#endif
