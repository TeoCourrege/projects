varying   highp vec2 outTexCoord;
varying   highp vec3 outPos;
varying   highp vec3 outNormal;
varying   highp vec4 outColor;

uniform highp float light_specular_strength;
uniform highp vec3 light_position;
uniform highp vec3 eye_position;

uniform samplerCube skybox;

void main(void)
{
    //calcul de la composante diffuse
    vec3 norm = normalize(outNormal);
    vec3 lightdir = normalize(light_position - outPos);
    float coeff_diffusion = max(dot(lightdir, norm), 0.0);

    //calcul de la composante spéculaire
    vec3 viewdir = normalize(outPos - eye_position);
    vec3 reflectdir = reflect(viewdir, norm);
    float coeff_specular = pow(max(dot(viewdir, reflectdir), 0.0), light_specular_strength);

    //couleur finale
    gl_FragColor = textureCube(skybox, reflectdir);
    gl_FragColor.a = outColor.a;
}
