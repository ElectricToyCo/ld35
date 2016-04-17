//
//  Conversation.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "Conversation.h"
#include "Character.h"
#include "ConversationDisplay.h"
#include "World.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( Conversation )
	DEFINE_DVAR( Conversation, TimeType, m_initialDelay );
	DEFINE_DVAR( Conversation, TimeType, m_speechDelay );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( Conversation )

	bool Conversation::active() const
	{
		return !!m_world;
	}

	size_t Conversation::maxSpeechesMade() const
	{
		return 2;
	}
	
	void Conversation::start( WeakPtr< World > world, SmartPtr< Character > initiator, SmartPtr< Character > second, SmartPtr< ConversationDisplay > display )
	{
		ASSERT( world );
		ASSERT( initiator );
		ASSERT( second );
		ASSERT( display );
		
		m_world = world;
		m_initiator = initiator;
		m_second = second;
		m_display = display;
		
		m_nSpeechesMade = 0;
		
		scheduleCallback( m_initialDelay );
		
		PROMISES( active() );
	}
	
	void Conversation::onParticipantInterrupted( SmartPtr< Character > participant )
	{
		finish();
	}
	
	void Conversation::finish()
	{
		if( active() )
		{
			m_world->cancelCallback( FRESH_CALLBACK( onTimeForNextStep ));
			
			m_initiator->onConversationEnding();
			m_second->onConversationEnding();
			
			m_world = nullptr;
			m_initiator = nullptr;
			m_second = nullptr;
			m_display = nullptr;
		}
		PROMISES( !active() );
	}
	
	bool Conversation::enactSpeech( SmartPtr< Character > speaker, SmartPtr< Character > listener )
	{
		ASSERT( speaker );
		ASSERT( listener );
		ASSERT( speaker != listener );
		
		// Override in subclasses.
		
		return false;
	}
	
	void Conversation::continueConversation()
	{
		if( m_nSpeechesMade >= maxSpeechesMade() )
		{
			// All done.
			//
			finish();
		}
		else
		{
			// Do the next speech.
			//
			const auto speaker = (( m_nSpeechesMade & 1 ) != 0 ) ? m_second : m_initiator;
			const auto listener = speaker == m_second ? m_initiator : m_second;

			bool hadSomethingToSay = enactSpeech( speaker, listener );
			if( hadSomethingToSay )
			{
				++m_nSpeechesMade;
			}
			else
			{
				dev_trace( speaker->characterName() << " had nothing to say." );
			}
			
			scheduleCallback( m_speechDelay );
		}
	}
	
	void Conversation::scheduleCallback( TimeType delay )
	{
		ASSERT( m_world );
		m_world->scheduleCallback( FRESH_CALLBACK( onTimeForNextStep ), delay );
	}
	
	FRESH_DEFINE_CALLBACK( Conversation, onTimeForNextStep, fr::Event )
	{
		continueConversation();
	}
}

