//
//  World.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "World.h"
#include "TileGrid.h"
#include "Mission.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( World )
	DEFINE_VAR( World, std::vector< rect >, m_roomRects );
	DEFINE_VAR( World, ClassInfo::cptr, m_conversationDisplayClass );
	DEFINE_VAR( World, std::vector< SmartPtr< Character >>, m_characters );
	DEFINE_VAR( World, std::vector< SmartPtr< Conversation >>, m_conversations );
	DEFINE_VAR( World, SmartPtr< Mission >, m_mission );
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
	
	void World::update()
	{
		Super::update();
		
		actorHost().sortChildren( []( const DisplayObject::ptr& a, const DisplayObject::ptr& b )
								 {
									 return a->position().y < b->position().y;
								 } );
		
		if( m_mission )
		{
			// Check for mission complete.
			//
			const auto missionStatus = m_mission->conclusionStatus( *this );
			if( missionStatus != Mission::Status::Undecided )
			{
				// Time to conclude the world.
				//
				// TODO!!!
			}
		}
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
	
	void World::addCharacter( Character::ptr character, size_t initialRoom )
	{
		REQUIRES( character );
		
		// Position the character.
		//
		if( initialRoom != -1 )
		{
			character->position( randomPointInRoom( initialRoom ));
		}
		else
		{
			const auto gridExtents = vector_cast< real >( tileGrid().extents() ) - UNITS_PER_TILE * 6.0f;
			const auto halfExtents = gridExtents / 2.0f;
			const auto clearSpot = tileGrid().findClearLocationNearby( halfExtents,
																	  halfExtents.minorAxisValue(), []( const vec2& p )
																	  {
																		  return randInRange( 1.0f, 2.0f );
																	  } );
			
			character->position( clearSpot );
		}
		
		actorHost().addChild( character );
		m_characters.push_back( character );
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
	
	void World::onAddedToStage()
	{
		Super::onAddedToStage();
		
		if( m_mission )
		{
			m_mission->setup( *this );
		}
	}
	
	std::string World::descriptiveForValue( Value value ) const
	{
		std::vector< std::string > options;
		
		switch( value )
		{
			case Value::Undecided:
				options = { "don't know anything about", "have never heard of" };
				break;
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
				options = { "love", "adore", "can't get enough of" };
				break;
		}
		
		ASSERT( options.empty() == false );
		return randomElement( options );
	}
	
	std::string World::descriptiveForTopic( Topic topic ) const
	{
		switch( topic.first )
		{
			case TopicType::Undecided:
				ASSERT( false );
				return "something";
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
	
	std::string World::createInitiatingSpeechText( Topic topic, Value value ) const
	{
		const std::string attitude = descriptiveForValue( value );
		const std::string topicDescription = descriptiveForTopic( topic );
		
		std::ostringstream stream;
		stream << "I " << attitude << " " << topicDescription << ".";
		return stream.str();
	}

}

