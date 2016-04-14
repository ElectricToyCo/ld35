//
//  horizontal_blur.fsh
//  Megadventure
//
//  Created by Jeff Wofford on 2013/11/20.
//  Copyright jeffwofford.com 2013. All rights reserved.
//
#ifdef GL_ES
precision highp float;
precision mediump int;
#endif

uniform sampler2D diffuseTexture;

uniform float bloomBrightness;
uniform float bloomContrast;

varying vec2 fragment_texCoord;

vec4 tonemap( vec4 color )
{
	return clamp(( color - 0.5 + bloomBrightness ) * bloomContrast + 0.5 + bloomBrightness, 0.0, 1.0 );
}

void main()
{
	gl_FragColor = tonemap( texture2D( diffuseTexture, fragment_texCoord ));
}