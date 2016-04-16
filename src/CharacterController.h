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
	class Actor;
	
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
	
		Actor& actor() const;
		
		virtual void update() override;

	protected:
		
		virtual void updateIdle();
		virtual void updatePursuing();
		virtual void updateTalking();
		virtual void updatePanicked();
		
		void wanderSomewhere();
		
	private:
		
		DVAR( State, m_state, State::Idle );
		DVAR( TimeType, m_nextWanderTime, -1.0 );
		DVAR( Range< TimeType >, m_wanderDelayRange, Range< TimeType >( 4.0, 8.0 ) );
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
