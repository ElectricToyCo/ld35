//
//  ConversationOpinion.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_ConversationOpinion_h
#define FreshApp_ConversationOpinion_h

#include "Essentials.h"
#include "Conversation.h"

namespace ld
{
	
	class ConversationOpinion : public Conversation
	{
		FRESH_DECLARE_CLASS( ConversationOpinion, Conversation );
	public:
		
		virtual void start( WeakPtr< World > world, SmartPtr< Character > initiator, SmartPtr< Character > second, SmartPtr< ConversationDisplay > display ) override;
		virtual bool enactSpeech( SmartPtr< Character > speaker, SmartPtr< Character > listener ) override;
		
	private:
		
		Topic m_topic = std::make_pair( TopicType::Undecided, -1 );
		
	};
	
}

#endif
