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

namespace ld
{
	class TileGrid;
	class Character;
	class ConversationDisplay;
	
	class World : public fr::FreshWorld
	{
		FRESH_DECLARE_CLASS( World, FreshWorld );
	public:
		
		TileGrid& tileGrid() const;
		DisplayObjectContainer& actorHost() const;
		DisplayObjectContainer& hudOverlayHost() const;

		virtual void update() override;
		
		// CONVERSATION
		
		SmartPtr< ConversationDisplay > createConversationDisplay();
		std::string descriptiveForValue( Value value ) const;
		std::string descriptiveForTopic( Topic topic ) const;
		std::string createInitiatingSpeechText( Topic topic, real value ) const;

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
		
	};
	
}

#endif
