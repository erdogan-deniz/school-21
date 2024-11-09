#extension GL_EXT_gpu_shader4 : require
flat varying  vec3 NormalFlat;
varying  vec3 NormalSmooth;
varying  vec3 FragPos;
varying vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform bool is_textured;
uniform bool have_normals;
uniform bool flat_shading;

uniform sampler2D texture1;

void main() {
    vec3 color;
    if (is_textured)
        color = texture2D(texture1, TexCoord).rgb;
    else
        color = objectColor;

    vec3 Normal;
    if (flat_shading)
        Normal = NormalFlat;
    else
        Normal = NormalSmooth;


    vec3 result = color;
    if (have_normals) {
        // ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = specularStrength * spec * lightColor;
        result *= (ambient + diffuse + specular);
    }

    gl_FragColor = vec4(result, 1.0);
}
