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
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( World )
	DEFINE_VAR( World, std::vector< rect >, m_roomRects );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( World )
	
	TileGrid& World::tileGrid() const
	{
		return getExpectedDescendant< TileGrid >( *this, "_tileGrid" );
	}

	DisplayObjectContainer& World::actorHost() const
	{
		return getExpectedDescendant< DisplayObjectContainer >( *this, "_actorHost" );
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
}

