//
//  World.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "World.h"
#include "TileGrid.h"
#include "Character.h"
#include "ConversationDisplay.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( World )
	DEFINE_VAR( World, std::vector< rect >, m_roomRects );
	DEFINE_VAR( World, ClassInfo::cptr, m_conversationDisplayClass );
	DEFINE_VAR( World, std::vector< SmartPtr< Character >>, m_characters );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( World )
	
	TileGrid& World::tileGrid() const
	{
		return getExpectedDescendant< TileGrid >( *this, "_tileGrid" );
	}

	DisplayObjectContainer& World::actorHost() const
	{
		return getExpectedDescendant< DisplayObjectContainer >( *this, "_actorHost" );
	}

	DisplayObjectContainer& World::hudOverlayHost() const
	{
		return getExpectedDescendant< DisplayObjectContainer >( *this, "_hudOverlayHost" );
	}
	
	SmartPtr< ConversationDisplay > World::createConversationDisplay()
	{
		ASSERT( m_conversationDisplayClass );
		auto display = createObject< ConversationDisplay >( *m_conversationDisplayClass );
		ASSERT( display );
		
		hudOverlayHost().addChild( display );
		return display;
	}
	
	void World::update()
	{
		Super::update();
		
		actorHost().sortChildren( []( const DisplayObject::ptr& a, const DisplayObject::ptr& b )
								 {
									 return a->position().y < b->position().y;
								 } );
	}
	
	size_t World::numRooms() const
	{
		return m_roomRects.size();
	}
	
	size_t World::roomContainingPoint( const vec2& p ) const
	{
		for( size_t i = 0; i < m_roomRects.size(); ++i )
		{
			const auto& roomRect = m_roomRects[ i ];
			if( roomRect.doesEnclose( p / UNITS_PER_TILE ))
			{
				return i;
			}
		}
		return -1;
	}
	
	size_t World::randomRoom( size_t excludedRoom ) const
	{
		ASSERT( numRooms() > 1 );
		
		while( true )
		{
			const size_t oneOfThem = randomInt( numRooms() );
			if( oneOfThem != excludedRoom )
			{
				return oneOfThem;
			}
		}
	}
	
	vec2 World::randomPointInRoom( size_t room ) const
	{
		REQUIRES( room < numRooms() );
		
		const auto rect = m_roomRects[ room ];
		return randInRange( rect.ulCorner() * UNITS_PER_TILE, rect.brCorner() * UNITS_PER_TILE );
	}
	
	SmartPtr< Character > World::bestCharacter( std::function< real( const Character& ) >&& scoringFunction )
	{
		real bestScore = 0;
		Character::ptr bestCharacter;
		actorHost().forEachDescendant< Character >( [&]( Character& character )
												   {
													   const auto score = scoringFunction( character );
													   if( score > 0 && score > bestScore )
													   {
														   bestScore = score;
														   bestCharacter = &character;
													   }
												   } );
													   
		return bestCharacter;
	}
	
	size_t World::numCharacters() const
	{
		return m_characters.size();
	}
	
	SmartPtr< Character > World::characterAt( size_t iCharacter ) const
	{
		ASSERT( iCharacter < m_characters.size() );
		return m_characters[ iCharacter ];
	}
	
	void World::postLoad()
	{
		Super::postLoad();
		
		ASSERT( m_characters.empty() );
		actorHost().forEachDescendant< Character >( [&]( Character& character )
												   {
													   m_characters.push_back( &character );
												   } );
	}
	
	std::string World::descriptiveForValue( Value value ) const
	{
		std::vector< std::string > options;
		
		switch( value )
		{
			case Value::Hate:
				options = { "despise", "loathe", "hate", "really hate", "am disgusted by" };
				break;
			case Value::Dislike:
				options = { "don't like", "dislike", "don't really like" };
				break;
			case Value::Neutral:
				options = { "don't know about", "am not sure about" };
				break;
			case Value::Like:
				options = { "like", "dig", "am into" };
				break;
			case Value::Love:
				break;
				options = { "love", "adore", "can't get enough of" };
		}
		
		ASSERT( options.empty() == false );
		return randomElement( options );
	}
	
	std::string World::descriptiveForTopic( Topic topic ) const
	{
		switch( topic.first )
		{
			case TopicType::Goodbye:
				ASSERT( false );
				return "";
			case TopicType::Food:
				return "food";
			case TopicType::Sports:
				return "sports";
			case TopicType::Music:
				return "music";
			case TopicType::Character:
			{
				auto character = characterAt( topic.second );
				return character->characterName();
			}
		}
	}
	
	std::string World::createInitiatingSpeechText( Topic topic, real value ) const
	{
		auto discrete = discreteValue( value );
		
		const std::string attitude = descriptiveForValue( discrete );
		const std::string topicDescription = descriptiveForTopic( topic );
		
		std::ostringstream stream;
		stream << "I " << attitude << " " << topicDescription << ".";
		return stream.str();
	}

}

