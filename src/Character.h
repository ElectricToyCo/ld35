//
//  Character.h
//  FreshApp
//
//  Created by Jeff Wofford on 4/16/16.
//  Copyright (c) 2016 Jeff Wofford. All rights reserved.
//

#ifndef FreshApp_Character_h
#define FreshApp_Character_h

#include "Essentials.h"
#include "Actor.h"

namespace ld
{
	class Character : public Actor
	{
		FRESH_DECLARE_CLASS( Character, Actor );
	public:

		virtual std::string characterName() const;
		
		SYNTHESIZE_GET( Color, favoriteColor )
		
		bool occupied() const;
		
		fr::DisplayObject::ptr visual() const;
		
		void setOpinion( const Topic& topic, Value value );

		void highlight( Color highlightColor = 0xffdbcbff );
		void unhighlight();		

		virtual bool onAddressedBy( SmartPtr< Character > initator );
		virtual void onConversationBeginning();
		virtual void onConversationEnding();
		virtual Topic pickTopic( const Character& forUseWithCharacter ) const;
		virtual Value pickTopicResponse( const Character& forUseWithCharacter, const Topic& topic ) const;

		virtual Value valueForTopic( const Topic& topic ) const;
		virtual Value valueForTopic( const Character& forUseWithCharacter, const Topic& topic ) const;
		virtual std::string getOpinionInitiatingText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const;
		virtual std::string getOpinionResponseText( const Character& forUseWithCharacter, const Topic& topic, Value value ) const;
		
		virtual void hearSpeech( const Character& fromCharacter, const Topic& topic, Value value );
		
		virtual void onTapped( const fr::EventTouch& event ) override;
		
	private:
		
		VAR( std::string, m_characterName );
		VAR( Color, m_favoriteColor );
		
	};
	
}

#endif
