//
//  ConversationOpinion.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "ConversationOpinion.h"
#include "Character.h"
#include "ConversationDisplay.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( ConversationOpinion )
	
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( ConversationOpinion )
	
	void ConversationOpinion::start( WeakPtr< World > world, SmartPtr< Character > initiator, SmartPtr< Character > second, SmartPtr< ConversationDisplay > display )
	{
		m_topic = std::make_pair( TopicType::Undecided, -1 );
		Super::start( world, initiator, second, display );
	}
	
	bool ConversationOpinion::enactSpeech( SmartPtr< Character > speaker, SmartPtr< Character > listener )
	{
		Super::enactSpeech( speaker, listener );
		
		if( speechIndex() == 0 )
		{
			m_topic = speaker->pickTopic( *listener );
			
			if( m_topic.first == TopicType::Undecided )
			{
				return false;
			}

			const auto value = speaker->valueForTopic( *listener, m_topic );
			
			if( value == Value::Undecided )
			{
				return false;
			}
			
			// Display the speech.
			//
			if( m_display )
			{
				const auto speechText = speaker->getOpinionInitiatingText( *listener, m_topic, value );
				m_display->showSpeech( speaker, speechText );
			}
			
			// Affect the listener with the speech.
			//
			listener->hearSpeech( *speaker, m_topic, value );
			
			return true;
		}
		else
		{
			ASSERT( m_topic.first != TopicType::Undecided );
			
			const auto value = speaker->pickTopicResponse( *listener, m_topic );
			
			if( value == Value::Undecided )
			{
				return false;
			}
			
			// Display the speech.
			//
			if( m_display )
			{
				const auto speechText = speaker->getOpinionResponseText( *listener, m_topic, value );
				m_display->showSpeech( speaker, speechText );
			}
			
			// Affect the listener with the speech.
			//
			listener->hearSpeech( *speaker, m_topic, value );
			
			return true;
		}
	}
	
}

