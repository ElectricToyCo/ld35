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
	class ConversationDisplay;

	class SpeechResponse : public fr::Object
	{
		FRESH_DECLARE_CLASS( SpeechResponse, Object );
	public:
		
		virtual void schedule( size_t speechIndex, TimeType deliveryTime, SmartPtr< ConversationDisplay > display, Character& me, Character& conversant, Topic topic, real value );
		
		bool isDeliveryTime( TimeType now ) const;
		
		virtual void deliver();

	protected:
		
		DVAR( size_t, m_speechIndex, 0 );
		VAR( SmartPtr< ConversationDisplay >, m_display );
		DVAR( TimeType, m_deliveryTime, -1.0 );
		VAR( WeakPtr< Character >, m_speaker );
		VAR( WeakPtr< Character >, m_conversant );
		DVAR( Topic, m_topic, std::make_pair( TopicType::Food, -1 ) );
		DVAR( real, m_value, 0 );
	};
	
	////////////////////////////////////////////////////////////////////////////
	
	class SpeechResponseGoodbye : public SpeechResponse
	{
		FRESH_DECLARE_CLASS( SpeechResponseGoodbye, SpeechResponse );
	public:
		
		void scheduleGoodbye( TimeType deliveryTime, Character& me, Character& conversant );
							  
		virtual void deliver();
	};
	
	////////////////////////////////////////////////////////////////////////////

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
		
		bool onAddressedBy( SmartPtr< Character > other );
		void endConversation();
		
		virtual void update() override;
		
		void onTravelCompleted();
		void onConversationEnding();
		void receiveSpeechStatement( SmartPtr< ConversationDisplay > display, Character& from, const Topic& topic, real value, size_t speechIndex );
		void displaySpeech( SmartPtr< ConversationDisplay > display, Topic topic, real value, size_t speechIndex );

		real valueForTopic( const Topic& topic ) const;
		real valueForCharacter( size_t iCharacter ) const;

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
		
		Topic pickTopic( const Character& forUseWithCharacter ) const;
		
	private:
		
		DVAR( State, m_state, State::Idle );
		DVAR( TimeType, m_nextThinkTime, -1.0 );
		DVAR( Range< TimeType >, m_wanderDelayRange, Range< TimeType >( 4.0, 8.0 ) );
		
		DVAR( real, m_percentChanceWanderToNewRoom, 50 );
		DVAR( real, m_percentChanceToInitiateTalk, 10 );

		VAR( SmartPtr< Character >, m_targetConversant );
		VAR( SmartPtr< Character >, m_conversant );
		VAR( WeakPtr< Character >, m_conversationInitiator );

		VAR( SpeechResponse::ptr, m_pendingSpeech );
		
		using TopicTypeMap = std::map< TopicType, real >;
		using CharacterValueMap = std::map< size_t, real >;

		VAR( TopicTypeMap, m_topicValues );
		VAR( CharacterValueMap, m_characterValues );
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
