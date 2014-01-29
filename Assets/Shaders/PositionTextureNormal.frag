uniform sampler2D s_Texture01;

varying vec2 v_vTexCoord;
varying vec3 v_vNormal;

void main()
{
    vec4 vTextureColor = texture2D( s_Texture01, v_vTexCoord );
    gl_FragColor = vTextureColor;
}