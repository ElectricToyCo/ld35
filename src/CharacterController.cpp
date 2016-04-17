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
#include "Conversation.h"
#include "ConversationOpinion.h"
using namespace fr;

namespace
{
	using namespace ld;
	const real MAX_WANDER_DISTANCE = 4 * UNITS_PER_TILE;
	const real MIN_CONVERSATION_DISTANCE = 0.5 * UNITS_PER_TILE;
	const real MAX_CONVERSATION_DISTANCE = 2.0 * UNITS_PER_TILE;
	
	int getInfluenceAmount( Value valueForInfluencer, Value influencersValue )
	{
		const auto influencerAmount = valueToInfluence( valueForInfluencer );
		const auto valueInt = valueToInfluence( influencersValue );
		
		return clamp( influencerAmount * valueInt, -2, 2 );		// TODO!!! Significant game logic.
	}
	
	Value influencedValue( Value value, int influence )
	{
		const int intValue = static_cast< int >( value != Value::Undecided ? value : Value::Neutral ) - 3;
		ASSERT( -2 <= intValue && intValue <= 2 );
		
		const int newIntValue = clamp( intValue + influence, -2, 2 ) + 3;
		ASSERT( 1 <= newIntValue && newIntValue <= 5 );
		return static_cast< Value >( newIntValue );
	}
}

#if 0
#	define ai_trace( x ) dev_trace( character().characterName() << ": " << x )
#else
#	define ai_trace( x )
#endif

#if 0
#	define conversation_trace( x ) dev_trace( character().characterName() << ": " << x )
#else
#	define conversation_trace( x )
#endif

namespace ld
{
	FRESH_DEFINE_CLASS( CharacterController )
	DEFINE_DVAR( CharacterController, State, m_state );
	DEFINE_DVAR( CharacterController, TimeType, m_nextThinkTime );
	DEFINE_DVAR( CharacterController, Range< TimeType >, m_wanderDelayRange );
	DEFINE_DVAR( CharacterController, real, m_percentChanceWanderToNewRoom );
	DEFINE_DVAR( CharacterController, real, m_percentChanceToInitiateTalk );
	DEFINE_VAR( CharacterController, SmartPtr< Character >, m_targetConversant );
	DEFINE_VAR( CharacterController, SmartPtr< Character >, m_conversant );
	DEFINE_VAR( CharacterController, WeakPtr< Character >, m_conversationInitiator );
	DEFINE_VAR( CharacterController, SmartPtr< Conversation >, m_conversation );
	DEFINE_DVAR( CharacterController, real, m_percentChanceWanderlust );
	DEFINE_VAR( CharacterController, TopicTypeMap, m_topicValues );
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
		ASSERT( valid() );
		return m_state != Idle;
	}
	
	void CharacterController::setOpinion( const Topic& topic, Value value )
	{
		m_topicValues[ topic ] = value;
	}
	
	void CharacterController::update()
	{
		ASSERT( valid() );

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
		
		ASSERT( valid() );
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
		ASSERT( valid() );

		// TODO
		
		ASSERT( valid() );
	}
	
	void CharacterController::updatePursuing()
	{
		ASSERT( valid() );

		// Move near the target character.

		ASSERT( valid() );
	}
	
	void CharacterController::updateTalking()
	{
		ASSERT( valid() );

		// Time to deliver a speech?
		//
		ASSERT( m_conversant );
		ASSERT( m_state == Talking );

		// TODO!!

		ASSERT( valid() );
	}
	
	void CharacterController::updatePanicked()
	{
		ASSERT( valid() );
		// Run away from the repulsive character (the player).
		//
		// TODO
		
		ASSERT( valid() );
	}
	
	void CharacterController::wanderSomewhere()
	{
		ASSERT( valid() );

		const World& world = character().world();

		// Should I go to a whole new room?
		//
		const auto wantNewRoom = pctChance( std::max( m_percentChanceWanderToNewRoom, m_percentChanceWanderlust ));
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
				m_percentChanceWanderlust = 0;
				m_nextThinkTime = world.time() + 30.0;		// Escape clause just in case onTravelCompleted is never called.
				ASSERT( valid() );
				return;
			}
		}
		ai_trace( "Gave up finding a wander destination." );
		
		ASSERT( valid() );
	}
	
	void CharacterController::onTravelCompleted()
	{
		ASSERT( valid() );

		if( m_state == Pursuing && m_targetConversant && distanceSquared( character().position(), m_targetConversant->position() ))
		{
			// Start talking if possible.
			//
			ASSERT( m_targetConversant && &character() != m_targetConversant );
			const auto succeeded = initiateConversation( *m_targetConversant );
			
			if( succeeded )
			{
				ASSERT( valid() );
				return;
			}
			else
			{
				ASSERT( !m_conversant );
				m_targetConversant = nullptr;
				m_state = Idle;
			}
		}
		
		m_nextThinkTime = character().world().time() + randInRange( m_wanderDelayRange );
		
		ASSERT( valid() );
	}
	
	bool CharacterController::initiateConversation( Character& withCharacter )
	{
		ASSERT( valid() );

		auto& me = character();
		
		conversation_trace( &me << " talks to " << &withCharacter );
		
		if( withCharacter.occupied() )
		{
			return false;
		}
		else
		{
			const bool wasConversationAccepted = withCharacter.onAddressedBy( &me );

			if( wasConversationAccepted )
			{
				m_conversationInitiator = &me;
				m_conversant = m_targetConversant;
				ASSERT( m_conversant == &withCharacter );
				
				// Choose a conversation type.
				//
				// TODO!!!
				
				m_conversation = me.world().createConversation< ConversationOpinion >( m_conversationInitiator, m_conversant );
			}
			
			ASSERT( valid() );

			return wasConversationAccepted;
		}
	}
	
	Topic CharacterController::pickTopic( const Character& forUseWithCharacter ) const
	{
		const auto myIndex = character().world().indexForCharacter( character() );
		const auto hisIndex = character().world().indexForCharacter( forUseWithCharacter );
		
		using Pair = typename decltype( m_topicValues )::value_type;
		
		std::vector< Pair > validTopics;
		std::copy_if( m_topicValues.begin(), m_topicValues.end(), std::back_inserter( validTopics ),
					 [&]( const Pair& pair )
					 {
						 return pair.second != Value::Undecided &&
						 
						 // Characters don't offer to talk about themselves or their partner.
						 ( pair.first.first != TopicType::Character || ( pair.first.second != myIndex && pair.first.second != hisIndex ));
					 } );
		
		if( !validTopics.empty() )
		{
			return randomElement( validTopics ).first;
		}
		else
		{
			return std::make_pair( TopicType::Undecided, -1 );
		}
	}
	
	Value CharacterController::pickTopicResponse( const Character& forUseWithCharacter, const Topic& topic ) const
	{
		return valueForTopic( forUseWithCharacter, topic );
	}
	
	void CharacterController::chooseNextBehavior()
	{
		ASSERT( valid() );

		ASSERT( !m_conversant );
		ASSERT( !m_targetConversant );
		ASSERT( m_state == Idle );
		
		// Should we go talk to someone?
		//
		if( pctChance( m_percentChanceToInitiateTalk ))
		{
			m_targetConversant = findConversant();
			
			if( m_targetConversant )
			{
				conversation_trace( character().characterName() << " pursuing " << m_targetConversant->characterName() );

				m_state = Pursuing;
				
				// Move to the conversant.
				bool foundDestination = travelNear( m_targetConversant->position(), MAX_CONVERSATION_DISTANCE, -1 /*room don't care*/, MIN_CONVERSATION_DISTANCE );
				
				if( !foundDestination )
				{
					m_targetConversant = nullptr;
					m_state = Idle;
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
		
		ASSERT( valid() );
	}
	
	Character::ptr CharacterController::findConversant() const
	{
		ASSERT( valid() );

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
		ASSERT( valid() );
		
		REQUIRES( other );
		REQUIRES( other != &character() );
		
		if( m_conversant )
		{
			onConversationInterrupted();
		}
		else if( m_targetConversant && m_targetConversant != other )
		{
			// Was pursuing someone other than the person trying to talk to me.
			//
			m_targetConversant = nullptr;
			m_state = Idle;
		}
		
		m_targetConversant = nullptr;
		m_conversant = other;
		m_conversationInitiator = m_conversant;
		onConversationBeginning();
		
		travelNear( m_conversant->position(), MAX_CONVERSATION_DISTANCE, -1 /* room don't care */, MIN_CONVERSATION_DISTANCE );

		ASSERT( valid() );

		return true;
	}
	
	bool CharacterController::valid() const
	{
		switch( m_state )
		{
			case Idle:
			case Panicked:
				return !m_conversant && !m_targetConversant && !m_conversationInitiator && !m_conversation;
			case Pursuing:
				return m_targetConversant && !m_conversant && !m_conversationInitiator && !m_conversation;
			case Talking:
				return !m_targetConversant && m_conversant && m_conversationInitiator;
		}
	}
	
	void CharacterController::onConversationBeginning()
	{
		REQUIRES( m_conversant );
		
		character().stopTravel();

		m_targetConversant = nullptr;
		m_state = Talking;
		
		ASSERT( valid() );
	}
	
	void CharacterController::endConversation()
	{
		ASSERT( valid() );

		REQUIRES( m_conversant );
		REQUIRES( m_conversationInitiator == &character() );
		ASSERT( m_state == Talking );
		ASSERT( !m_targetConversant );
		
		m_conversant->onConversationEnding();
		onConversationEnding();
		
		ASSERT( valid() );
	}
	
	void CharacterController::onConversationInterrupted()
	{
		ASSERT( valid() );

		if( m_conversation )
		{
			m_conversation->onParticipantInterrupted( &character() );
		}
		
		ASSERT( valid() );
	}
	
	void CharacterController::onConversationEnding()
	{
		ASSERT( valid() );

		ASSERT( m_state == Talking );
		
		ASSERT( !m_targetConversant );
		
		if( m_conversation )
		{
			character().world().onConversationFinished( m_conversation );
		}
		
		m_conversation = nullptr;
		m_conversationInitiator = nullptr;
		m_conversant = nullptr;
		m_state = Idle;
		
		m_percentChanceWanderlust = 100;
	
		PROMISES( !occupied() );
		
		ASSERT( valid() );
	}
	
	Value CharacterController::valueForTopic( const Character& forUseWithCharacter, const Topic& topic ) const
	{
		auto iter = m_topicValues.find( topic );
		if( iter != m_topicValues.end() )
		{
			const auto baseValue = iter->second;
			const auto influenced = influencedValue( baseValue, totalInfluence( topic ));
			return influenced;
		}
		else
		{
			return Value::Undecided;
		}
	}
	
	std::string CharacterController::getOpinionInitiatingText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const
	{
		return character().world().createInitiatingSpeechText( topic, value );
	}

	std::string CharacterController::getOpinionResponseText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const
	{
		// TODO
		return character().world().createInitiatingSpeechText( topic, value );
	}

	void CharacterController::hearSpeech( const Character& fromCharacter, const Topic& topic, Value value )
	{
		setInfluenceFromCharacter( fromCharacter, topic, value );
	}

	void CharacterController::setInfluenceFromCharacter( const Character& other, Topic topic, Value value )
	{
		const auto hisIndex = character().world().indexForCharacter( other );
		
		const auto valueForInfluencer = valueForTopic( character(), std::make_pair( TopicType::Character, hisIndex ));
		
		const auto influence = getInfluenceAmount( valueForInfluencer, value );
		m_perTopicInfluences[ topic ][ hisIndex ] = influence;
	}
	
	int CharacterController::totalInfluence( Topic topic ) const
	{
		auto iter = m_perTopicInfluences.find( topic );
		if( iter != m_perTopicInfluences.end() )
		{
			int influence = 0;
			
			const auto& map = iter->second;
			for( auto pair : map )
			{
				influence += pair.second;
			}
			
			return influence;
		}
		else
		{
			return 0;
		}
	}
}

