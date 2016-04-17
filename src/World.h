//
//  World.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_World_h
#define FreshApp_World_h

#include "Essentials.h"
#include "FreshWorld.h"
#include "Camera.h"
#include "Character.h"
#include "Conversation.h"
#include "ConversationDisplay.h"

namespace ld
{
	class TileGrid;
	
	class World : public fr::FreshWorld
	{
		FRESH_DECLARE_CLASS( World, FreshWorld );
	public:
		
		TileGrid& tileGrid() const;
		DisplayObjectContainer& actorHost() const;
		DisplayObjectContainer& hudOverlayHost() const;

		virtual void update() override;
		
		// CONVERSATION
		
		template< typename ConversationT >
		SmartPtr< Conversation > createConversation( SmartPtr< Character > initiator, SmartPtr< Character > second )
		{
			ASSERT( m_conversationDisplayClass );
			auto display = fr::createObject< ConversationDisplay >( *m_conversationDisplayClass );
			ASSERT( display );
			
			hudOverlayHost().addChild( display );
			
			auto conversation = fr::createObject< ConversationT >();
			ASSERT( conversation );
			
			conversation->start( this, initiator, second, display );
			return conversation;
		}
		
		std::string descriptiveForValue( Value value ) const;
		std::string descriptiveForTopic( Topic topic ) const;
		std::string createInitiatingSpeechText( Topic topic, Value value ) const;

		// ROOMS
		
		size_t numRooms() const;
		size_t roomContainingPoint( const vec2& p ) const;		// Returns -1 if none.
		size_t randomRoom( size_t excludedRoom = -1 ) const;
		
		vec2 randomPointInRoom( size_t room ) const;

		// CHARACTERS
		
		SmartPtr< Character > bestCharacter( std::function< real( const Character& ) >&& scoringFunction );
		
		size_t numCharacters() const;
		SmartPtr< Character > characterAt( size_t iCharacter ) const;
		
		virtual void postLoad() override;
		
	private:
		
		VAR( std::vector< rect >, m_roomRects );
		VAR( ClassInfo::cptr, m_conversationDisplayClass );
		VAR( std::vector< SmartPtr< Character >>, m_characters );
		VAR( std::vector< SmartPtr< Conversation >>, m_conversations );
		
	};
	
}

#endif
