#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D texture;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 color;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
uniform vec3 viewPos;

uniform vec4 globalAmbient;
uniform Material material;
uniform Light light;

void main()
{
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    float spec = 0;
    if (diff > 0)
    {
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    }

    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * diff;
    vec3 specular = light.specular.xyz * material.specular.xyz * spec;

    vec3 result = ambient * texture(material.texture, TexCoords).rgb * light.color + diffuse * texture(material.texture, TexCoords).rgb * light.color + specular * light.color;
    FragColor = vec4(result, 0.5);
}
