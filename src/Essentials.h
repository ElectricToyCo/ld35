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
		Goodbye,
		Food,
		Sports,
		Music,
		Character
	};
	
	using Topic = std::pair< TopicType, size_t >;
	
	FRESH_ENUM_STREAM_IN_BEGIN( ld, TopicType )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Goodbye )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Food )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Sports )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Music )
	FRESH_ENUM_STREAM_IN_CASE( TopicType, Character )
	FRESH_ENUM_STREAM_IN_END()
	
	FRESH_ENUM_STREAM_OUT_BEGIN( ld, TopicType )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Goodbye )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Food )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Sports )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Music )
	FRESH_ENUM_STREAM_OUT_CASE( TopicType, Character )
	FRESH_ENUM_STREAM_OUT_END()

	enum class Value
	{
		Hate,
		Dislike,
		Neutral,
		Like,
		Love
	};
	
	
	// |   |   |   |   |   |
	// |         +         |
	
	inline Value discreteValue( real value )
	{
		const size_t divisions = 5;
		const real span = 1.0f / divisions;
		
		if( value < -1.5f * span )
		{
			return Value::Hate;
		}
		else if( value < -0.5f * span )
		{
			return Value::Dislike;
		}
		else if( value > 0.5f * span )
		{
			return Value::Like;
		}
		else if( value > 1.5f * span )
		{
			return Value::Love;
		}
		else
		{
			return Value::Neutral;
		}
		
	}
}

#endif
