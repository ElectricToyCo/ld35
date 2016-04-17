//
//  Conversation.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_Conversation_h
#define FreshApp_Conversation_h

#include "Essentials.h"

namespace ld
{
	class World;
	class Character;
	class ConversationDisplay;
	
	class Conversation : public fr::Object
	{
		FRESH_DECLARE_CLASS( Conversation, Object );
	public:

		bool active() const;
		
		virtual void start( WeakPtr< World > world, SmartPtr< Character > initiator, SmartPtr< Character > second, SmartPtr< ConversationDisplay > display );
		
		void onParticipantInterrupted( SmartPtr< Character > participant );
		
		void finish();

	protected:

		WeakPtr< World > m_world;
		SmartPtr< Character > m_initiator;
		SmartPtr< Character > m_second;
		SmartPtr< ConversationDisplay > m_display;
		
		virtual size_t maxSpeechesMade() const;
		size_t speechIndex() const { return m_nSpeechesMade; }

		virtual bool enactSpeech( SmartPtr< Character > speaker, SmartPtr< Character > listener );

		void continueConversation();
		
		void scheduleCallback( TimeType delay );
		
	private:
		
		DVAR( TimeType, m_initialDelay, 1.0 );
		DVAR( TimeType, m_speechDelay, 4.0 );
		
		size_t m_nSpeechesMade = 0;
		
		FRESH_DECLARE_CALLBACK( Conversation, onTimeForNextStep, fr::Event );
	};
	
}

#endif
