// post-processing fragment shader
#version 410
in vec2 vTexCoord;
uniform sampler2D colourTarget;
uniform bool blur;
uniform bool distort;
uniform bool blank;
out vec4 FragColour;
// just output the colour unchanged
vec4 BoxBlur(vec2 texCoord);
vec4 Blank(vec2 texCoord);
vec4 Distort(vec2 texCoord);
void main() {
// calculate texel size
vec2 texSize = textureSize( colourTarget, 0 );
vec2 texelSize = 1.0f / texSize;
// adjust texture coordinate
vec2 scale = (texSize - texelSize) / texSize;
vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;
if (blur)
{
   FragColour += BoxBlur(texCoord);
}
if (distort)
{
   FragColour += Distort(texCoord);
}
if (blank)
{
   FragColour += Blank(texCoord);
}
}

// simple box blur
vec4 BoxBlur(vec2 texCoord) 
{
vec2 texel = 1.0f / textureSize(colourTarget, 0);
// 9-tap box kernel
vec4 colour = texture(colourTarget, texCoord);
colour += texture(colourTarget, texCoord + texel * vec2(-1,1));
colour += texture(colourTarget, texCoord + texel * vec2(-1,0));
colour += texture(colourTarget, texCoord + texel * vec2(-1,-1));
colour += texture(colourTarget, texCoord + texel * vec2(0,1));
colour += texture(colourTarget, texCoord + texel * vec2(0,-1));
colour += texture(colourTarget, texCoord + texel * vec2(1,1));
colour += texture(colourTarget, texCoord + texel * vec2(1,0));
colour += texture(colourTarget, texCoord + texel * vec2(1,-1));
return colour / 9;
}

vec4 Blank(vec2 texCoord) {
return texture( colourTarget, texCoord );
}

vec4 Distort(vec2 texCoord) {
vec2 mid = vec2(0.5f);
float distanceFromCentre = distance(texCoord, mid);
vec2 normalizedCoord = normalize(texCoord - mid);
float bias = distanceFromCentre +
sin(distanceFromCentre * 15) * 0.05f;
vec2 newCoord = mid + bias * normalizedCoord;
return texture(colourTarget, newCoord);
}