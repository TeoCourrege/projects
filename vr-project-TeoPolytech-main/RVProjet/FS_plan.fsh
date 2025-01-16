varying highp vec4 outColor;

void main(void)
{
    gl_FragColor = (1.0 - gl_FragCoord.z*0.6) * outColor;
    gl_FragColor.a = outColor.a;
}
