//
//  composite.fsh
//  Fresh
//
//  Created by Jeff Wofford on 2015/08/21.
//  Copyright jeffwofford.com 2015. All rights reserved.
//
#ifdef GL_ES
precision highp float;
precision mediump int;
#endif

uniform sampler2D originalTexture;
uniform sampler2D blurTexture;
uniform sampler2D pixelBevelTexture;
uniform float bloomIntensity;
uniform float bevelIntensity;

varying lowp vec2 fragment_texCoord;
varying lowp vec2 fragment_texCoord_pixel_bevel;

float BlendOverlayf( float base, float blend )
{
    return (base < 0.5 ? (2.0 * base * blend) : (1.0 - 2.0 * (1.0 - base) * (1.0 - blend)));
}

vec4 BlendOverlay4( vec4 base, vec4 blend )
{
    return vec4( BlendOverlayf( base.r, blend.r ),
                 BlendOverlayf( base.g, blend.g ),
                 BlendOverlayf( base.b, blend.b ),
                 base.a );
}

void main()
{
    vec4 diffuse = texture2D( originalTexture, fragment_texCoord.st );
    vec4 bloom = texture2D( blurTexture, fragment_texCoord.st );	    
    vec4 bevel = texture2D( pixelBevelTexture, fragment_texCoord_pixel_bevel.st );    

    diffuse = mix( diffuse, BlendOverlay4( diffuse, bevel ), bevelIntensity );

	gl_FragColor = diffuse + bloom * bloomIntensity;
}