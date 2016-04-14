//
//  tv_post.vsh
//  Megadventure
//
//  Created by Jeff Wofford on 5/28/10.
//  Copyright jeffwofford.com 2010. All rights reserved.
//
#ifdef GL_ES
precision highp float;
precision mediump int;
#endif

attribute vec2 position;
attribute vec2 texCoord;

uniform highp int milliseconds;
uniform float chromaticAberration;

varying lowp vec2 fragment_texCoord;
varying lowp vec2 fragment_texCoord_red;
varying lowp vec2 fragment_texCoord_blue;
varying lowp vec2 fragment_texCoord_noise;


uniform vec2 diffuseTextureSize;

void main()
{
	vec2 texelSize = 1.0 / diffuseTextureSize;
	float time = float( milliseconds );
	
    gl_Position = vec4( position, 0.0, 1.0 );
	fragment_texCoord = texCoord;
	fragment_texCoord_red = texCoord + vec2( texelSize.x * chromaticAberration, 0 );
	fragment_texCoord_blue = texCoord + vec2( texelSize.x * -chromaticAberration, 0 );
	fragment_texCoord_noise = texCoord + fract( vec2( time / 107.0, time / 231.0 ));
}
