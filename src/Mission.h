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
		
		VAR( vec2, m_position );				// Ignored if 0,0
		DVAR( size_t, m_initialRoom, -1 );		// Trumped by non-zero position
	};
	
	////////////////

	class TutorialManager;
	
	class Mission : public fr::Object
	{
		FRESH_DECLARE_CLASS( Mission, Object );
	public:

		SYNTHESIZE_GET( std::string, message );
		
		virtual void setup( WeakPtr< World > world );
		
		virtual void update();
		
		enum class Status
		{
			Undecided,
			Succeeded,
			Failed
		};
		
		Status conclusionStatus( const World& world ) const;

	protected:
		
		bool hasAchievedGoals( const World& world ) const;
		bool isUnsolvable( const World& world ) const;
		
	private:
		
		VAR( WeakPtr< World >, m_world );
		VAR( std::vector< MissionCharacterSetup::ptr >, m_characters );
		VAR( SmartPtr< TutorialManager >, m_tutorial );
		DVAR( bool, m_endWithTutorial, false );
		VAR( std::string, m_message );
	};
	
}

#endif
