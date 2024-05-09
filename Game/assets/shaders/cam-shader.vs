#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 ViewProjection;
uniform vec2 spriteSheetSize;
uniform vec2 spriteSize;
uniform vec2 tcxy;

void main()
{
    vec2 ntc = vec2(((tcxy.x+aTexCoord.x) * spriteSize.x)/spriteSheetSize.x, ((tcxy.y + aTexCoord.y) * spriteSize.y)/spriteSheetSize.y);
    gl_Position = ViewProjection * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = ntc;
}