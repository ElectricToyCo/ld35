//
//  CharacterController.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_CharacterController_h
#define FreshApp_CharacterController_h

#include "Essentials.h"
#include "FreshActorController.h"

namespace ld
{
	class Character;
	class Conversation;

	class CharacterController : public fr::FreshActorController
	{
		FRESH_DECLARE_CLASS( CharacterController, FreshActorController );
	public:
		
		enum State
		{
			Idle,
			Pursuing,
			Talking,
			Panicked
		};
	
		Character& character() const;
		
		bool occupied() const;
		
		void setOpinion( const Topic& topic, Value value );

		bool onAddressedBy( SmartPtr< Character > other );
		void endConversation();
		
		virtual void update() override;
		
		void onTravelCompleted();
		void onConversationEnding();

		Topic pickTopic( const Character& forUseWithCharacter ) const;
		Value pickTopicResponse( const Character& forUseWithCharacter, const Topic& topic ) const;

		Value valueForTopic( const Character& forUseWithCharacter, const Topic& topic ) const;

		virtual std::string getOpinionInitiatingText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const;
		virtual std::string getOpinionResponseText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const;
		
		virtual void hearSpeech( const Character& fromCharacter, const Topic& topic, Value value );

	protected:

		void onConversationBeginning();
		void onConversationInterrupted();
		
		bool travelNear( const vec2& pos, real maxDistance, size_t room = -1, real minDistance = 0 );
		
		virtual void updateIdle();
		virtual void updatePursuing();
		virtual void updateTalking();
		virtual void updatePanicked();
		
		void wanderSomewhere();
		
		void chooseNextBehavior();
		
		SmartPtr< Character > findConversant() const;
		
		bool initiateConversation( Character& withCharacter );
		
		real attitudeToward( const Character& withCharacter ) const;
		TimeType timeSinceLastConversation( const Character& withCharacter ) const;
		
	private:
		
		DVAR( State, m_state, State::Idle );
		DVAR( TimeType, m_nextThinkTime, -1.0 );
		DVAR( Range< TimeType >, m_wanderDelayRange, Range< TimeType >( 4.0, 8.0 ) );
		
		DVAR( real, m_percentChanceWanderToNewRoom, 50 );
		DVAR( real, m_percentChanceToInitiateTalk, 10 );

		VAR( SmartPtr< Character >, m_targetConversant );
		VAR( SmartPtr< Character >, m_conversant );
		VAR( WeakPtr< Character >, m_conversationInitiator );
		
		VAR( SmartPtr< Conversation >, m_conversation );

		using TopicTypeMap = std::map< Topic, Value >;

		VAR( TopicTypeMap, m_topicValues );
	};
	
	FRESH_ENUM_STREAM_IN_BEGIN( CharacterController, State )
	FRESH_ENUM_STREAM_IN_CASE( CharacterController::State, Idle )
	FRESH_ENUM_STREAM_IN_CASE( CharacterController::State, Pursuing )
	FRESH_ENUM_STREAM_IN_CASE( CharacterController::State, Talking )
	FRESH_ENUM_STREAM_IN_CASE( CharacterController::State, Panicked )
	FRESH_ENUM_STREAM_IN_END()
	
	FRESH_ENUM_STREAM_OUT_BEGIN( CharacterController, State )
	FRESH_ENUM_STREAM_OUT_CASE( CharacterController::State, Idle )
	FRESH_ENUM_STREAM_OUT_CASE( CharacterController::State, Pursuing )
	FRESH_ENUM_STREAM_OUT_CASE( CharacterController::State, Talking )
	FRESH_ENUM_STREAM_OUT_CASE( CharacterController::State, Panicked )
	FRESH_ENUM_STREAM_OUT_END()

}

#endif
