//
//  Mission.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "Mission.h"
#include "Character.h"
#include "World.h"
using namespace fr;

namespace ld
{	
	FRESH_DEFINE_CLASS( MissionCharacterOpinion )
	DEFINE_DVAR( MissionCharacterOpinion, TopicType, m_topic );
	DEFINE_DVAR( MissionCharacterOpinion, size_t, m_character );
	DEFINE_DVAR( MissionCharacterOpinion, Value, m_value );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( MissionCharacterOpinion )
	
	////////////////
	
	FRESH_DEFINE_CLASS( MissionCharacterState )
	DEFINE_VAR( MissionCharacterState, SmartPtr< Character >, m_character );
	DEFINE_VAR( MissionCharacterState, std::vector< MissionCharacterOpinion::ptr >, m_opinions );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( MissionCharacterState )
	
	////////////////
	
	FRESH_DEFINE_CLASS( MissionCharacterSetup )
	DEFINE_DVAR( MissionCharacterSetup, size_t, m_initialRoom );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( MissionCharacterSetup )
	
	////////////////
	
	FRESH_DEFINE_CLASS( Mission )
	DEFINE_VAR( Mission, std::vector< MissionCharacterSetup::ptr >, m_characters );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( Mission )
	
	void Mission::setup( World& world )
	{
		for( auto character : m_characters )
		{
			ASSERT( character );
			
			for( auto opinion : character->m_opinions )
			{
				ASSERT( opinion );
				character->m_character->setOpinion( std::make_pair( opinion->m_topic, opinion->m_character ), opinion->m_value );
			}
			
			world.addCharacter( character->m_character, character->m_initialRoom );
		}
	}
	
	Mission::Status Mission::conclusionStatus( const World& world ) const
	{
		// TODO!!!
		return Status::Undecided;
	}
}

