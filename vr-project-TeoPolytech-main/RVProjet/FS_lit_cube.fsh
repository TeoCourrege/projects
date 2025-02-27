varying   highp vec3 outPos;
varying   highp vec3 outNormal;
varying   highp vec4 outColor;

uniform highp vec4 light_ambient_color;
uniform highp vec4 light_diffuse_color;
uniform highp vec4 light_specular_color;
uniform highp float light_specular_strength;
uniform highp vec3 light_position;
uniform highp vec3 eye_position;

void main(void)
{
    //calcul de la composante ambiante
    vec4 ambient = light_ambient_color*outColor;

    //calcul de la composante diffuse
    vec3 norm = normalize(outNormal);
    vec3 lightdir = normalize(light_position - outPos);
    float coeff_diffusion = max(dot(lightdir, norm), 0.0);
    vec4 diffuse = (coeff_diffusion * light_diffuse_color)*outColor;

    //calcul de la composante spéculaire
    vec3 viewdir = normalize(outPos - eye_position);
    vec3 reflectdir = reflect(lightdir, norm);
    float coeff_specular = pow(max(dot(viewdir, reflectdir), 0.0), light_specular_strength);
    vec4 specular = (coeff_specular * light_specular_color) * vec4(1.0, 1.0, 1.0, 1.0);
    //couleur finale
    gl_FragColor = ambient + diffuse + specular ;
    gl_FragColor.a = outColor.a;
}
