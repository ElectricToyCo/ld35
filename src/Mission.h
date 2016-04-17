//
//  Mission.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_Mission_h
#define FreshApp_Mission_h

#include "Essentials.h"

namespace ld
{
	class Character;
	class World;
	
	class MissionCharacterOpinion : public fr::Object
	{
		FRESH_DECLARE_CLASS( MissionCharacterOpinion, Object );
	public:

		DVAR( TopicType, m_topic, TopicType::Undecided );
		DVAR( size_t, m_character, -1 );
		DVAR( Value, m_value, Value::Undecided );
	};
	
	////////////////
	
	class MissionCharacterState : public fr::Object
	{
		FRESH_DECLARE_CLASS( MissionCharacterState, Object );
	public:
		
		VAR( SmartPtr< Character >, m_character );
		VAR( std::vector< MissionCharacterOpinion::ptr >, m_opinions );
	};

	////////////////
	
	class MissionCharacterSetup : public MissionCharacterState
	{
		FRESH_DECLARE_CLASS( MissionCharacterSetup, MissionCharacterState );
	public:
		
		DVAR( size_t, m_initialRoom, -1 );
	};
	
	////////////////

	class Mission : public fr::Object
	{
		FRESH_DECLARE_CLASS( Mission, Object );
	public:
		
		void setup( World& world );
		
		enum class Status
		{
			Undecided,
			Succeed,
			Failed
		};
		
		Status conclusionStatus( const World& world ) const;
		
	private:
		
		VAR( std::vector< MissionCharacterSetup::ptr >, m_characters );
		
	};
	
}

#endif
