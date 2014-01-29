uniform mat4 mWorldViewInverseTranspose;

attribute vec4 u_vPosition;
attribute vec2 u_vTexCoords;
attribute vec3 u_vNormal;

varying vec2 v_vTexCoord;
varying vec3 v_vNormal;

void main()
{
//    v_vNormal = ( mWorldViewInverseTranspose * vec4( u_vNormal, 1.0 ) ).xyz;
    v_vNormal   = u_vNormal;
    v_vTexCoord = u_vTexCoords;
	gl_Position = mWorldViewProjection * u_vPosition;
}