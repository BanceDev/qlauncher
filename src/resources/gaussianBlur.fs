// gaussianBlur.fs
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 blurDirection; // (1,0) for horizontal, (0,1) for vertical
uniform float blurSize;

void main()
{
    vec2 texelSize = vec2(1.0) / vec2(textureSize(texture0, 0));
    vec2 offset = blurDirection * texelSize * blurSize;
    
    vec4 sum = vec4(0.0);
    sum += texture(texture0, fragTexCoord + offset * -4.0) * 0.05;
    sum += texture(texture0, fragTexCoord + offset * -3.0) * 0.09;
    sum += texture(texture0, fragTexCoord + offset * -2.0) * 0.12;
    sum += texture(texture0, fragTexCoord + offset * -1.0) * 0.15;
    sum += texture(texture0, fragTexCoord) * 0.16;
    sum += texture(texture0, fragTexCoord + offset * 1.0) * 0.15;
    sum += texture(texture0, fragTexCoord + offset * 2.0) * 0.12;
    sum += texture(texture0, fragTexCoord + offset * 3.0) * 0.09;
    sum += texture(texture0, fragTexCoord + offset * 4.0) * 0.05;
    
    finalColor = sum;
}
