//
//  TutorialManager.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/17/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_TutorialManager_h
#define FreshApp_TutorialManager_h

#include "Essentials.h"

namespace ld
{
	class AppStage;
	class World;
	class HUD;
	class Character;
	class TutorialManager;

	class TutorialStep : public fr::Object
	{
		FRESH_DECLARE_CLASS( TutorialStep, Object );
	public:

		bool completed() const;
		virtual void begin( WeakPtr< World > world );
		void update();
		virtual void end();
		
	protected:
		
		TimeType now() const;

		virtual void reallyBegin();
		virtual bool conditionCompleted() const;
		
		bool isMarkedCompleted() const;
		void markCompleted();
		
		World& world() const;
		AppStage& ldStage() const;
		HUD& hud() const;
		Character& player() const;

		void showMessage( const std::string& message );
		void hideMessage();

	private:

		VAR( WeakPtr< World >, m_world );
		DVAR( TimeType, m_preDelay, 2.0 );
		DVAR( TimeType, m_postDelay, 1.0 );
		VAR( std::string, m_message );
		DVAR( TimeType, m_startTime, -1 );
		DVAR( TimeType, m_completionTime, -1 );
	};
	
	//////////////////////////////////////////////////////////////////
	
	class TutorialManager : public fr::Object
	{
		FRESH_DECLARE_CLASS( TutorialManager, Object );
	public:
		
		virtual void setup( WeakPtr< World > world );
		virtual void update();

	protected:
		
		virtual bool completed() const;
		
		void beginStep( size_t step );
		virtual void onStepBeginning( size_t step );
		virtual void endStep( size_t step );
		
		void advanceStep();
		void gotoStep( size_t step );
		
		World& world() const;
		
	private:
		
		VAR( WeakPtr< World >, m_world );
		DVAR( size_t, m_currentStep, 0 );
		
		VAR( std::vector< TutorialStep::ptr >, m_steps );
	};
	
}

#endif
