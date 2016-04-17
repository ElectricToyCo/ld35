//
//  Essentials.h
//  ld35
//
//  Created by Jeff Wofford on 2013/11/19.
//  Copyright (c) 2013 Jeff Wofford. All rights reserved.
//

#ifndef ld35_Essentials_h
#define ld35_Essentials_h

#include "FreshVector.h"
#include "Color.h"
#include "Object.h"
#include "ObjectPtr.h"
#include "CommandProcessor.h"
#include "MovieClip.h"
#include "ClassFilter.h"
#include "FreshFile.h"
#include "DisplayPackage.h"
#include "AudioSystem.h"
#include "TextField.h"
#include "UIPopup.h"
#include "StructSerialization.h"

#if FRESH_TELEMETRY_ENABLED
#	include "UserTelemetry.h"
#endif

namespace fr
{
	class Sound;
}

namespace ld
{
	using fr::ClassInfo;
	using fr::ClassName;
	using fr::path;
	using fr::real;
	using fr::uint;
	using fr::vec2;
	using fr::vec3;
	using fr::vec4;
	typedef fr::Vector2i vec2i;
	typedef fr::Vector2ui vec2ui;
	using fr::mat4;
	using fr::Color;
	using fr::SmartPtr;
	using fr::WeakPtr;
	using fr::TimeType;
	using fr::Range;
	using fr::rect;
	using fr::Rectanglei;
	using fr::angle;
	using fr::clamp;
	using fr::lerp;
	using fr::ObjectId;
	using fr::ClassFilter;
	using fr::dynamic_freshptr_cast;
	
	const real UNITS_PER_TILE = 16;
	
	enum class TopicType
	{
		Undecided,
		Food,
		Sports,
		Music,
		Character
	};
	
	using Topic = std::pair< TopicType, size_t >;
	
	FRESH_ENUM_STREAM_IN_BEGIN( ld, TopicType )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Undecided )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Food )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Sports )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Music )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Character )
	FRESH_ENUM_STREAM_IN_END()
	
	FRESH_ENUM_STREAM_OUT_BEGIN( ld, TopicType )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Undecided )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Food )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Sports )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Music )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Character )
	FRESH_ENUM_STREAM_OUT_END()

	enum class Value
	{
		Undecided,
		Hate,
		Dislike,
		Neutral,
		Like,
		Love,
	};

	FRESH_ENUM_STREAM_IN_BEGIN( ld, Value )
	FRESH_ENUM_STREAM_IN_CASE( Value, Undecided )
	FRESH_ENUM_STREAM_IN_CASE( Value, Hate )
	FRESH_ENUM_STREAM_IN_CASE( Value, Dislike )
	FRESH_ENUM_STREAM_IN_CASE( Value, Neutral )
	FRESH_ENUM_STREAM_IN_CASE( Value, Like )
	FRESH_ENUM_STREAM_IN_CASE( Value, Love )
	FRESH_ENUM_STREAM_IN_END()
	
	FRESH_ENUM_STREAM_OUT_BEGIN( ld, Value )
	FRESH_ENUM_STREAM_OUT_CASE( Value, Undecided )
	FRESH_ENUM_STREAM_OUT_CASE( Value, Hate )
	FRESH_ENUM_STREAM_OUT_CASE( Value, Dislike )
	FRESH_ENUM_STREAM_OUT_CASE( Value, Neutral )
	FRESH_ENUM_STREAM_OUT_CASE( Value, Like )
	FRESH_ENUM_STREAM_OUT_CASE( Value, Love )
	FRESH_ENUM_STREAM_OUT_END()

	
	inline fr::ObjectName textureNameForValue( Value value )
	{
		switch( value )
		{
			case Value::Undecided:
				return "value_display_undecided";
			case Value::Hate:
				return "value_display_hate";
			case Value::Dislike:
				return "value_display_dislike";
			case Value::Neutral:
				return "value_display_neutral";
			case Value::Like:
				return "value_display_like";
			case Value::Love:
				return "value_display_love";
		}
	}
	
	inline int valueToInfluence( Value value )
	{
		switch( value )
		{
			case Value::Undecided:
				return 0;
			case Value::Hate:
				return -2;
			case Value::Dislike:
				return -1;
			case Value::Neutral:
				return 0;
			case Value::Like:
				return 1;
			case Value::Love:
				return 2;
		}
	}
}

#endif
