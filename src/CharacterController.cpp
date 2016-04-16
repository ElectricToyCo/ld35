//
//  CharacterController.cpp
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#include "CharacterController.h"
#include "Character.h"
#include "World.h"
#include "TileGrid.h"
#include "ConversationDisplay.h"
using namespace fr;

namespace
{
	using namespace ld;
	const real MAX_WANDER_DISTANCE = 4 * UNITS_PER_TILE;
	const real MIN_CONVERSATION_DISTANCE = 0.5 * UNITS_PER_TILE;
	const real MAX_CONVERSATION_DISTANCE = 2.0 * UNITS_PER_TILE;
	
	const TimeType SPEECH_RESPONSE_DELAY = 2.0;
}

#if 0
#	define ai_trace( x ) dev_trace( x )
#else
#	define ai_trace( x )
#endif

#if 0
#	define conversation_trace( x ) dev_trace( x )
#else
#	define conversation_trace( x )
#endif

namespace ld
{
	FRESH_DEFINE_CLASS( SpeechResponse )
	DEFINE_DVAR( SpeechResponse, size_t, m_speechIndex );
	DEFINE_VAR( SpeechResponse, SmartPtr< ConversationDisplay >, m_display );
	DEFINE_DVAR( SpeechResponse, TimeType, m_deliveryTime );
	DEFINE_VAR( SpeechResponse, WeakPtr< Character >, m_speaker );
	DEFINE_VAR( SpeechResponse, WeakPtr< Character >, m_conversant );
	DEFINE_DVAR( SpeechResponse, Topic, m_topic );
	DEFINE_DVAR( SpeechResponse, real, m_value );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( SpeechResponse )
	
	void SpeechResponse::schedule( size_t speechIndex, TimeType deliveryTime, SmartPtr< ConversationDisplay > display, Character& me, Character& conversant, Topic topic, real value )
	{
		m_speechIndex = speechIndex;
		m_deliveryTime = deliveryTime;
		m_display = display;
		m_speaker = &me;
		m_conversant = &conversant;
		m_topic = topic;
		m_value = value;
	}
	
	bool SpeechResponse::isDeliveryTime( TimeType now ) const
	{
		return now >= m_deliveryTime;
	}
	
	void SpeechResponse::deliver()
	{
		ASSERT( m_speaker );
		ASSERT( m_conversant );

		m_speaker->displaySpeech( m_display, m_topic, m_value, m_speechIndex );
		m_conversant->receiveSpeechStatement( m_display, *m_speaker, m_topic, m_value, m_speechIndex );
	}

	//////////////////////////////////
	
	FRESH_DEFINE_CLASS( SpeechResponseGoodbye )
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( SpeechResponseGoodbye )
	
	void SpeechResponseGoodbye::scheduleGoodbye( TimeType deliveryTime, Character& me, Character& conversant )
	{
		schedule( 0, deliveryTime, nullptr, me, conversant, std::make_pair( TopicType::Goodbye, -1 ), 0 );
	}
	
	void SpeechResponseGoodbye::deliver()
	{
		ASSERT( m_speaker );
		ASSERT( m_conversant );
		m_speaker->onConversationEnding();
		m_conversant->onConversationEnding();
	}

	//////////////////////////////////
	
	FRESH_DEFINE_CLASS( CharacterController )
	DEFINE_DVAR( CharacterController, State, m_state );
	DEFINE_DVAR( CharacterController, TimeType, m_nextThinkTime );
	DEFINE_DVAR( CharacterController, Range< TimeType >, m_wanderDelayRange );
	DEFINE_DVAR( CharacterController, real, m_percentChanceWanderToNewRoom );
	DEFINE_DVAR( CharacterController, real, m_percentChanceToInitiateTalk );
	DEFINE_VAR( CharacterController, SmartPtr< Character >, m_targetConversant );
	DEFINE_VAR( CharacterController, SmartPtr< Character >, m_conversant );
	DEFINE_VAR( CharacterController, WeakPtr< Character >, m_conversationInitiator );
	DEFINE_VAR( CharacterController, SpeechResponse::ptr, m_pendingSpeech );
	DEFINE_VAR( CharacterController, TopicTypeMap, m_topicValues );
	DEFINE_VAR( CharacterController, CharacterValueMap, m_characterValues );
	FRESH_IMPLEMENT_STANDARD_CONSTRUCTORS( CharacterController )
	
	Character& CharacterController::character() const
	{
		ASSERT( dynamic_cast< Character* >( host().get() ));
		auto character = static_cast< Character* >( host().get() );
		ASSERT( character );
		return *character;
	}
	
	bool CharacterController::occupied() const
	{
		return m_conversant != nullptr || m_targetConversant != nullptr;
	}
	
	void CharacterController::update()
	{
		const auto now = character().world().time();
		
		if( m_nextThinkTime < 0 || now >= m_nextThinkTime )
		{
			if( !occupied() )
			{
				chooseNextBehavior();
			}
		}

		switch( m_state )
		{
			case Idle:
				updateIdle();
				break;
			case Pursuing:
				updatePursuing();
				break;
			case Talking:
				updateTalking();
				break;
			case Panicked:
				updatePanicked();
				break;
		}
		
		Super::update();
	}
	
	bool CharacterController::travelNear( const vec2& pos, real maxDistance, size_t room, real minDistance )
	{
		ai_trace( "Trying destination " << pos );
		
		const auto& world = character().world();
		const auto& tileGrid = world.tileGrid();

		const auto newPos = tileGrid.findClearLocationNearby( pos, maxDistance, [&]( const vec2& p )
															 {
																 const auto newRoom = world.roomContainingPoint( p );
																 if( room != -1 && room != newRoom )
																 {
																	 return 0.0f;	// Give it no score.
																 }
																 
																 const auto dist = distance( p, pos );
																 if( dist > 0 )
																 {
																	 return 1.0f / dist;
																 }
																 else
																 {
																	 return 1000.0f;
																 }
															 },
															 minDistance
															 );
		
		if( newPos.x >= 0 && newPos.y >= 0 )
		{
			// Make sure the new position is in the desired room.
			//
			const auto newRoom = world.roomContainingPoint( newPos );
			if( room != -1 && room != newRoom )
			{
				// Not cool.
				return false;
			}
			
			ai_trace( "Found new destination: " << newPos );
			
			// Found a good one. Use it.
			//
			bool foundPath = character().travelTo( newPos );
			if( foundPath )
			{
				return true;
			}
		}

		ai_trace( "Found no valid destination near: " << pos );
		return false;
	}
	
	void CharacterController::updateIdle()
	{
		// TODO
	}
	
	void CharacterController::updatePursuing()
	{
		// Move near the target character.
		//
		// TODO
	}
	
	void CharacterController::updateTalking()
	{
		// Time to deliver a speech?
		//
		ASSERT( m_conversant );
		ASSERT( m_state == Talking );
		
		if( m_pendingSpeech && m_pendingSpeech->isDeliveryTime( character().world().time() ))
		{
			m_pendingSpeech->deliver();
			m_pendingSpeech = nullptr;
		}		
	}
	
	void CharacterController::updatePanicked()
	{
		// Run away from the repulsive character (the player).
		//
		// TODO
	}
	
	void CharacterController::wanderSomewhere()
	{
		const World& world = character().world();

		// Should I go to a whole new room?
		//
		const auto wantNewRoom = pctChance( m_percentChanceWanderToNewRoom );
		const bool wantNonRoom = wantNewRoom && pctChance( 10 );

		for( size_t tries = 0; tries < 4; ++tries )
		{
			// Pick a new destination that is not too far from my current position, and not in a wall.
			//
			vec2 desiredPosition = character().position();
			const auto currentRoom = world.roomContainingPoint( desiredPosition );	// Might return -1.
			size_t desiredRoom = currentRoom;

			if( wantNewRoom && !wantNonRoom )
			{
				desiredRoom = world.randomRoom( currentRoom );
				
				ai_trace( "Going to new room " << desiredRoom );
				desiredPosition = world.randomPointInRoom( desiredRoom );
			}
			else
			{
				if( wantNonRoom )
				{
					// Be willing to go to a non-room, like a bathroom or hall.
					//
					desiredRoom = -1;
				}
				
				desiredPosition = character().position() + makeRandomVector2( MAX_WANDER_DISTANCE );
			}

			bool foundDestination = travelNear( desiredPosition, 3.0 * UNITS_PER_TILE, desiredRoom );
			
			if( foundDestination )
			{
				m_nextThinkTime = world.time() + 30.0;		// Escape clause just in case onTravelCompleted is never called.
				break;
			}
		}
		ai_trace( "Done (maybe gave up) finding a wander destination." );
	}
	
	void CharacterController::onTravelCompleted()
	{
		if( m_state == Pursuing && m_targetConversant && distanceSquared( character().position(), m_targetConversant->position() ))
		{
			// Start talking if possible.
			//
			ASSERT( m_targetConversant && &character() != m_targetConversant );
			const auto succeeded = initiateConversation( *m_targetConversant );
			
			if( succeeded )
			{
				return;
			}
			else
			{
				ASSERT( !m_conversant );
				m_targetConversant = nullptr;
			}
		}
		
		m_nextThinkTime = character().world().time() + randInRange( m_wanderDelayRange );
	}
	
	bool CharacterController::initiateConversation( Character& withCharacter )
	{
		auto& me = character();
		
		conversation_trace( &me << " talks to " << &withCharacter );
		
		const bool wasConversationAccepted = withCharacter.onAddressedBy( &me );

		if( wasConversationAccepted )
		{
			m_conversationInitiator = &me;
			m_conversant = m_targetConversant;
			ASSERT( m_conversant == &withCharacter );
			
			onConversationBeginning();
			
			// Choose a conversation type.
			//
			// TODO!!!
			
			// Choose a topic of conversation.
			//
			auto topic = pickTopic( *m_conversant );
			auto value = valueForTopic( topic );
			
			auto display = me.world().createConversationDisplay();
			ASSERT( display );
			
			display->beginConversation( 2 );		// TODO!!!
			
			ASSERT( !m_pendingSpeech );
			
			m_pendingSpeech = createObject< SpeechResponse >();
			m_pendingSpeech->schedule( 0, me.world().time() + SPEECH_RESPONSE_DELAY,
									   display, me, *m_conversant, topic, value );
		}
		
		return wasConversationAccepted;
	}
	
	Topic CharacterController::pickTopic( const Character& forUseWithCharacter ) const
	{
		// TODO!!!
		return std::make_pair( TopicType::Food, -1 );
	}
	
	void CharacterController::chooseNextBehavior()
	{
		ASSERT( !m_conversant );
		ASSERT( !m_targetConversant );
		
		// Should we go talk to someone?
		//
		if( pctChance( m_percentChanceToInitiateTalk ))
		{
			m_targetConversant = findConversant();
			
			if( m_targetConversant )
			{
				conversation_trace( &character() << " pursuing " << m_targetConversant );

				m_state = Pursuing;
				
				// Move to the conversant.
				bool foundDestination = travelNear( m_targetConversant->position(), MAX_CONVERSATION_DISTANCE, -1 /*room don't care*/, MIN_CONVERSATION_DISTANCE );
				
				if( !foundDestination )
				{
					m_targetConversant = nullptr;
					m_nextThinkTime = -1;	// Immediately.
				}
			}
		}
		else
		{
			// Just wandering.
			//
			m_state = Idle;
			wanderSomewhere();
		}
	}
	
	Character::ptr CharacterController::findConversant() const
	{
		const auto& me = character();
		const auto myPosition = me.position();
		const auto myCurrentRoom = me.currentRoom();
		auto& world = character().world();
		
		return world.bestCharacter( [&]( const Character& character )
								   {
									   if( &character == &me )
									   {
										   return -1.0f;
									   }
									   else
									   {
										   const auto attitudeScore = attitudeToward( character );

										   const auto tooSoonScore = static_cast< real >( timeSinceLastConversation( character ));
										   
										   const auto distSquared = distanceSquared( character.position(), myPosition );
										   real distanceScore = 1.0f / ( distSquared > 0 ? distSquared : 0.1f );
										   distanceScore *= ( myCurrentRoom == character.currentRoom() ? 2.0f : 1.0f );
										   
										   return distanceScore * 1.0f
										   +	  attitudeScore * 1.0f
										   +	  tooSoonScore  * 0.1f;
									   }
								   } );
	}
	
	real CharacterController::attitudeToward( const Character& withCharacter ) const
	{
		// TODO Psychology.
		return 0.0f;
	}
	
	TimeType CharacterController::timeSinceLastConversation( const Character& withCharacter ) const
	{
		// TODO Memory
		return 60.0f;
	}

	bool CharacterController::onAddressedBy( SmartPtr< Character > other )
	{
		REQUIRES( other );
		REQUIRES( other != &character() );
		
		if( m_conversant || ( m_targetConversant && m_targetConversant != other ) )
		{
			onConversationInterrupted();
		}		
		
		m_targetConversant = nullptr;
		m_conversant = other;
		m_conversationInitiator = m_conversant;
		onConversationBeginning();
		
		travelNear( m_conversant->position(), MAX_CONVERSATION_DISTANCE, -1 /* room don't care */, MIN_CONVERSATION_DISTANCE );

		return true;
	}
	
	void CharacterController::onConversationBeginning()
	{
		REQUIRES( m_conversant );
		
		m_targetConversant = nullptr;
		m_state = Talking;
		character().stopTravel();
		
		ASSERT( !m_pendingSpeech );
	}
	
	void CharacterController::endConversation()
	{
		REQUIRES( m_conversant );
		REQUIRES( m_conversationInitiator == &character() );
		ASSERT( m_state == Talking );
		ASSERT( !m_targetConversant );
		
		m_conversant->onConversationEnding();
		onConversationEnding();
	}
	
	void CharacterController::onConversationInterrupted()
	{
		// TODO!!!
		onConversationEnding();
	}
	
	void CharacterController::onConversationEnding()
	{
		if( m_state == Talking )
		{
			ASSERT( !m_targetConversant );
			m_conversationInitiator = nullptr;
			m_conversant = nullptr;
			m_pendingSpeech = nullptr;
			m_state = Idle;
		}
		PROMISES( !occupied() );
	}
	
	void CharacterController::receiveSpeechStatement( SmartPtr< ConversationDisplay > display, Character& from, const Topic& topic, real value, size_t speechIndex )
	{
		if( m_state == Talking )
		{
			ASSERT( &from == m_conversant );

			auto& me = character();
			
			if( m_conversationInitiator == &character() )
			{
				auto goodbyeSpeech = createObject< SpeechResponseGoodbye >();
				goodbyeSpeech->scheduleGoodbye( me.world().time() + SPEECH_RESPONSE_DELAY,
											    me, from );
				m_pendingSpeech = goodbyeSpeech;
			}
			else
			{
				// Schedule a response.
				//
				ASSERT( !m_pendingSpeech );
				
				m_pendingSpeech = createObject< SpeechResponse >();
				m_pendingSpeech->schedule( speechIndex, me.world().time() + SPEECH_RESPONSE_DELAY,
										   display, me, from, topic, valueForTopic( topic ));
			}
		}
	}
	
	real CharacterController::valueForTopic( const Topic& topic ) const
	{
		if( topic.first == TopicType::Character )
		{
			return valueForCharacter( topic.second );
		}
		else
		{
			auto iter = m_topicValues.find( topic.first );
			if( iter != m_topicValues.end() )
			{
				return iter->second;
			}
			else
			{
				return 0;
			}
		}
	}
	
	real CharacterController::valueForCharacter( size_t iCharacter ) const
	{
		auto iter = m_characterValues.find( iCharacter );
		if( iter != m_characterValues.end() )
		{
			return iter->second;
		}
		else
		{
			return 0;
		}
	}
	
	void CharacterController::displaySpeech( SmartPtr< ConversationDisplay > display, Topic topic, real value, size_t speechIndex )
	{
		auto& me = character();

		std::string speechText;
		if( speechIndex == 0 )
		{
			speechText = me.world().createInitiatingSpeechText( topic, value );
		}
		else
		{
			// TODO non-initiating.
			speechText = me.world().createInitiatingSpeechText( topic, value );
		}
		
		display->showSpeech( &me, speechText );
		
		m_conversant->receiveSpeechStatement( display, me, topic, value, speechIndex );
	}
}

