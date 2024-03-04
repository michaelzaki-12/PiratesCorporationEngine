#version 460 core


out vec4 FragColor;
in vec3 color;
in vec2 texcoord;
in vec3 Normal;
in vec3 CurrentPos;
uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 PointLight()
{
   vec3 LightVec = lightPos - CurrentPos;
   float dist = length(LightVec);

   float a = 0.05f;
   float b = 0.01f;

   float inten = 1.0f / (a * dist * dist + b + dist + 1);
   // simple power to fit our faces not facing the light (instead of expensive ray tracing)
   float ambient = 0.2f;

   //light direction
   vec3 Light_direction = (lightPos - CurrentPos);

   //normalize the vector of our light
   vec3 normal = normalize(LightVec);

   //the diffuse of our light when it hit our normal of the object we hit
   float diffuse = max(dot(normal, Light_direction), 0.0f);
   float specularLight = 0.5f;

   //direction of the light respictivily to our camera
   vec3 viewDirection = (camPos - CurrentPos);
   // reflection of light when it hits the object
   vec3 LightReflection = reflect(-Light_direction, normal);
   //the power related to the reflection of light and the view direction of the object
   float specular_amount = pow(max(dot(viewDirection, LightReflection), 0.0f), 4);

   float specular = specularLight * specular_amount;


   return texture(tex0, texcoord) * lightColor * (diffuse * inten + ambient + (specular * inten));
}
vec4 DirectionalLight()
{
   // simple power to fit our faces not facing the light (instead of expensive ray tracing)
   float ambient = 0.2f;

   //light direction
   vec3 Light_direction = (lightPos - CurrentPos);

   //normalize the vector of our light
   vec3 normal = normalize(vec3(1.0f, 1.0f, 0.0f));

   //the diffuse of our light when it hit our normal of the object we hit
   float diffuse = max(dot(normal, Light_direction), 0.0f);
   float specularLight = 0.5f;

   //direction of the light respictivily to our camera
   vec3 viewDirection = (camPos - CurrentPos);
   // reflection of light when it hits the object
   vec3 LightReflection = reflect(-Light_direction, normal);
   //the power related to the reflection of light and the view direction of the object
   float specular_amount = pow(max(dot(viewDirection, LightReflection), 0.0f), 4);

   float specular = specularLight * specular_amount;


   return texture(tex0, texcoord) * lightColor * (diffuse + ambient + (specular));
}
vec4 SpotLight(){
   // controls how big the area that is lit up is
   float outerCone = 0.90f;
   float innerCone = 0.95f;

   // ambient lighting
   float ambient = 0.20f;

   // diffuse lighting
   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightPos - CurrentPos);
   float diffuse = max(dot(normal, lightDirection), 0.0f);

   // specular lighting
   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - CurrentPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
   float specular = specAmount * specularLight;

   // calculates the intensity of the crntPos based on its angle to the center of the light cone
   float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
   float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

   return texture(tex0, texcoord) * lightColor * (diffuse * inten + ambient + (specular * inten));
}

void main()
{
   FragColor = SpotLight();
}