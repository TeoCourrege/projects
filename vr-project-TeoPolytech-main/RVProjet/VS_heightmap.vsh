attribute highp vec3 rv_Position;
attribute highp vec2 rv_Color;
attribute highp vec3 rv_TexCoord;
attribute highp vec3 rv_Normal;

uniform   highp mat4 u_ModelMatrix;
uniform   highp mat4 u_ViewMatrix;
uniform   highp mat4 u_ProjectionMatrix;
uniform   highp float u_Opacity;
uniform   highp vec4 u_Color;

uniform   highp sampler2D u_heightmap;
uniform   highp float u_facteur;

varying   highp vec4 outColor;
varying   highp vec2 outTexCoord;
varying   highp vec3 outPos;
varying   highp vec3 outNormal;



void main(void)
{
    vec3 pos=rv_Position;
    pos.y += u_facteur * texture2D(u_heightmap, rv_TexCoord.xy).r;
    outPos = vec3(u_ModelMatrix * vec4(pos, 1.0));
    outNormal = vec3(u_ModelMatrix * vec4(rv_Normal, 0.0));
    outColor = vec4(u_Color.rgb, u_Opacity);
    outTexCoord = rv_TexCoord.st;
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(outPos, 1.0);
}
