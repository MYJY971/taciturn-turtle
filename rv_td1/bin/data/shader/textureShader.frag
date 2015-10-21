#version 330 core


uniform sampler2D tex0;
uniform sampler2D tex1;

in vec2 text;

out vec4 outColor;

void main()
{

    //vec4 test0 = mix(vec4(texture(tex0,text)), vec4(texture(tex1,text)), 0.5) ;
    //vec4 t = vec4(test0.x,test0.y,test0.z,1.0);
    
    vec4 txt1 = texture(tex0, text);
    vec4 txt2 = texture(tex1, text);
    vec4 test = txt1 + txt2 ;
    
    if(test.x>0.9 && test.y>0.9 && test.z>0.9)
    	outColor = txt1;
    else
    	outColor = vec4(txt2.x,txt2.y,txt2.z,1.0);
    		
    
}
