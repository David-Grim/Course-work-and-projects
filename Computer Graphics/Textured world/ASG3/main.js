/*MAIN.JS
David Grim
dgrim
CSE160
*/
//Starter code taken from youtube video "WebGL Tutorial 02 - Rotating 3D Cube"
//by Indigo Code (everything up to being able to render a rotating cube in space)
var xEye = 4;
var yEye = 2
var zEye = 2;

var xUp = 0;
var yUp = 1;
var zUp = 0;

var xAt = 2;
var yAt = 1;
var zAt = -2;
var viewMatrix = new Float32Array(16);
var vertexShaderText = 
[
'precision mediump float;',
'',
'attribute vec3 vertPosition;',
'attribute vec2 vertTexCoord;',
'varying vec2 fragTexCoord;',
'uniform mat4 mWorld;',
'uniform mat4 mView;',
'uniform mat4 mProj;',
'',
'void main()',
'{',
'  fragTexCoord = vertTexCoord;',
'  gl_Position = mProj * mView * mWorld * vec4(vertPosition, 1.0);',
'}'
].join('\n');

var fragmentShaderText =
[
'precision mediump float;',
'',
'varying vec2 fragTexCoord;',
'uniform sampler2D sampler;',
'',
'void main()',
'{',
'  gl_FragColor = texture2D(sampler, fragTexCoord);',
'}'
].join('\n');


 function main() {

  var canvas = document.getElementById('game-surface');
  var gl = canvas.getContext('webgl');

  if (!gl) {
    console.log('WebGL not supported, falling back on experimental-webgl');
    gl = canvas.getContext('experimental-webgl');
  }

  if (!gl) {
    alert('Your browser does not support WebGL');
  }

  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  gl.enable(gl.DEPTH_TEST);
  gl.frontFace(gl.CCW);

  var vertexShader = gl.createShader(gl.VERTEX_SHADER);
  var fragmentShader = gl.createShader(gl.FRAGMENT_SHADER);

  gl.shaderSource(vertexShader, vertexShaderText);
  gl.shaderSource(fragmentShader, fragmentShaderText);

  gl.compileShader(vertexShader);
  if (!gl.getShaderParameter(vertexShader, gl.COMPILE_STATUS)) {
    console.error('ERROR compiling vertex shader!', gl.getShaderInfoLog(vertexShader));
    return;
  }

  gl.compileShader(fragmentShader);
  if (!gl.getShaderParameter(fragmentShader, gl.COMPILE_STATUS)) {
    console.error('ERROR compiling fragment shader!', gl.getShaderInfoLog(fragmentShader));
    return;
  }

  var program = gl.createProgram();
  gl.attachShader(program, vertexShader);
  gl.attachShader(program, fragmentShader);
  gl.linkProgram(program);
  if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
    console.error('ERROR linking program!', gl.getProgramInfoLog(program));
    return;
  }
  gl.validateProgram(program);
  if (!gl.getProgramParameter(program, gl.VALIDATE_STATUS)) {
    console.error('ERROR validating program!', gl.getProgramInfoLog(program));
    return;
  }

var boxVertices = 
	[ // X, Y, Z           U, V
		// Top
		-1.0, 1.0, -1.0,   0, 0,
		-1.0, 1.0, 1.0,    0, 1,
		1.0, 1.0, 1.0,     1, 1,
		1.0, 1.0, -1.0,    1, 0,

		// Left
		-1.0, 1.0, 1.0,    0, 0,
		-1.0, -1.0, 1.0,   1, 0,
		-1.0, -1.0, -1.0,  1, 1,
		-1.0, 1.0, -1.0,   0, 1,

		// Right
		1.0, 1.0, 1.0,    1, 1,
		1.0, -1.0, 1.0,   0, 1,
		1.0, -1.0, -1.0,  0, 0,
		1.0, 1.0, -1.0,   1, 0,

		// Front
		1.0, 1.0, 1.0,    1, 1,
		1.0, -1.0, 1.0,    1, 0,
		-1.0, -1.0, 1.0,    0, 0,
		-1.0, 1.0, 1.0,    0, 1,

		// Back
		1.0, 1.0, -1.0,    0, 0,
		1.0, -1.0, -1.0,    0, 1,
		-1.0, -1.0, -1.0,    1, 1,
		-1.0, 1.0, -1.0,    1, 0,

		// Bottom
		-1.0, -1.0, -1.0,   1, 1,
		-1.0, -1.0, 1.0,    1, 0,
		1.0, -1.0, 1.0,     0, 0,
		1.0, -1.0, -1.0,    0, 1,
	];
  
  var boxIndices =
  [
    // Top
    0, 1, 2,
    0, 2, 3,

    // Left
    5, 4, 6,
    6, 4, 7,

    // Right
    8, 9, 10,
    8, 10, 11,

    // Front
    13, 12, 14,
    15, 14, 12,

    // Back
    16, 17, 18,
    16, 18, 19,

    // Bottom
    21, 20, 22,
    22, 20, 23,

  ];

 ///////////////////////CAT//////////////////////////////////////////////////////////////////////////////////
  //front
 drawCube(gl,boxVertices,boxIndices,program,canvas,0,4,0,1,1,.75,"cat",0);
 //middle
 drawCube(gl,boxVertices,boxIndices,program,canvas,1,4,0,1,1,.75,"cat",0);
 //butt
 drawCube(gl,boxVertices,boxIndices,program,canvas,2,4,0,1,1,.75,"cat",0);
 //back right leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,2,3,.5,.1,1.5,.18,"cat",3);
 //back left leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,2,3,-.5,.1,1.5,.18,"cat",4);
 //front right leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.75,3,.5,.1,1.5,.18,"cat",4);
 //front left leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.75,3,-.5,.1,1.5,.18,"cat",3);
 //front left foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.95,2,-.5,.1,.18,.18,"cat",3);
 //front right foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.95,2,.5,.1,.18,.18,"cat",4);
 //back right foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,1.8,2,.5,.1,.18,.18,"cat",3);
 //back left foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,1.8,2,-.5,.1,.18,.18,"cat",4);
 //tail start
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,4.9,0,.15,.25,.25,"cat",1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,5.8,0,.15,.22,.25,"cat",1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,6.3,-.3,.15,.22,.25,"cat",1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,5.4,-.4,.15,.22,.25,"cat",1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,5.8,-.4,.15,.22,.25,"cat",1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,6,-.25,.15,.22,.25,"cat",1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,6.3,-.25,.15,.17,.17,"cat",1);
 //tailend
 //neck
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.95,4.7,0,.3,.3,.3,"cat",0);
 //head
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1.5,5.8,0,.75,.75,.75,"cat",2);
 //right ear
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,6.4,.5,.15,.22,.25,"cat",2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,6.6,.5,.1,.2,.2,"cat",2);
 //left ear
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,6.4,-.5,.15,.22,.25,"cat",2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,6.6,-.5,.1,.2,.2,"cat",2);
 //snout
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.25,5.5,0,.35,.35,.35,"cat",2);
 //nose
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,5.25,0,.08,.08,.08,"cat",2);
 //whiskers
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,5.5,0,.04,.04,1.2,"cat",2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,5.55,0,.04,.04,1.2,"cat",2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,5.65,0,.04,.04,1.2,"cat",2);
 //eyes
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.2,5.8,-.5,.10,.20,.20,"cat",2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.2,5.8,.5,.10,.20,.20,"cat",2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.25,5.8,-.5,.10,.20,.05,"cat",2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.25,5.8,.5,.10,.20,.05,"cat",2);
 /////////////////////END CAT/////////////////////////////////////////////////////////////////////////////
 
//skybawks
 drawCube(gl,boxVertices,boxIndices,program,canvas,0,0,0,1000,1000,1000,"sky",5);
 //the ground
 drawCube(gl,boxVertices,boxIndices,program,canvas,0,0,0,125,1,125,"ground",0);
//boxes
for(var i = -25; i<25; i+=2){
drawCube(gl,boxVertices,boxIndices,program,canvas,i,2,25,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,25,2,i,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,i,2,-25,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,-25,2,i,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,-25,4,i,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,i,4,-25,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,i,6,-25,1,1,1,"box",0);
}
drawCube(gl,boxVertices,boxIndices,program,canvas,4,8,-25,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,10,8,-25,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,-25,6,-20,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,-25,6,-10,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,-25,6,10,1,1,1,"box",0);
drawCube(gl,boxVertices,boxIndices,program,canvas,25,2,4,1,1,1,"box",0);


};

function drawCube(gl,boxVertices,boxIndices,program,canvas,xTrans,yTrans,zTrans,xScale,yScale,zScale,tex,rotate){
var boxVertexBufferObject = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, boxVertexBufferObject);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(boxVertices), gl.STATIC_DRAW);

	var boxIndexBufferObject = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, boxIndexBufferObject);
	gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(boxIndices), gl.STATIC_DRAW);

	var positionAttribLocation = gl.getAttribLocation(program, 'vertPosition');
	var texCoordAttribLocation = gl.getAttribLocation(program, 'vertTexCoord');
	gl.vertexAttribPointer(
		positionAttribLocation, 
		3, 
		gl.FLOAT, 
		gl.FALSE,
		5 * Float32Array.BYTES_PER_ELEMENT, 
		0 
	);
	gl.vertexAttribPointer(
		texCoordAttribLocation, 
		2, 
		gl.FLOAT, 
		gl.FALSE,
		5 * Float32Array.BYTES_PER_ELEMENT, 
		3 * Float32Array.BYTES_PER_ELEMENT 
	);

	gl.enableVertexAttribArray(positionAttribLocation);
	gl.enableVertexAttribArray(texCoordAttribLocation);

  if(tex == "box"){
  	var boxTexture = gl.createTexture();
 	gl.bindTexture(gl.TEXTURE_2D, boxTexture);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texImage2D(
		gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA,
		gl.UNSIGNED_BYTE,
		document.getElementById('crate-image')
	);
    gl.bindTexture(gl.TEXTURE_2D, null);
  }
  if(tex == "sky"){
  	var boxTexture = gl.createTexture();
 	gl.bindTexture(gl.TEXTURE_2D, boxTexture);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texImage2D(
		gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA,
		gl.UNSIGNED_BYTE,
		document.getElementById('sky-image')
	);
    gl.bindTexture(gl.TEXTURE_2D, null);
  }
   if(tex == "ground"){
  	var boxTexture = gl.createTexture();
 	gl.bindTexture(gl.TEXTURE_2D, boxTexture);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.REPEAT);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.REPEAT);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texImage2D(
		gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA,
		gl.UNSIGNED_BYTE,
		document.getElementById('ground-image')
	);
    gl.bindTexture(gl.TEXTURE_2D, null);
  }

  if(tex == "cat"){
  	var boxTexture = gl.createTexture();
 	gl.bindTexture(gl.TEXTURE_2D, boxTexture);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texImage2D(
		gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA,
		gl.UNSIGNED_BYTE,
		document.getElementById('cat-image')
	);
    gl.bindTexture(gl.TEXTURE_2D, null);
  }

  gl.useProgram(program);

 var matWorldUniformLocation = gl.getUniformLocation(program, 'mWorld');
 var matViewUniformLocation = gl.getUniformLocation(program, 'mView');
 var matProjUniformLocation = gl.getUniformLocation(program, 'mProj');

	var worldMatrix = new Float32Array(16);
	var viewMatrix = new Float32Array(16);
	var projMatrix = new Float32Array(16);
	mat4.identity(worldMatrix);
	//document.onkeypress = function(ev){keydown(ev, gl, matViewUniformLocation, viewMatrix); };
	//mat4.lookAt(viewMatrix, [xEye, 30, zEye],[xEye, 2, 95+zEye], [0, 1, 0]);
	//document.onkeypress = function(ev){keydown(ev, gl, matViewUniformLocation, viewMatrix); };
	mat4.perspective(projMatrix, glMatrix.toRadian(80), canvas.clientWidth / canvas.clientHeight, .1, 100000.0);

	gl.uniformMatrix4fv(matWorldUniformLocation, gl.FALSE, worldMatrix);
	gl.uniformMatrix4fv(matViewUniformLocation, gl.FALSE, viewMatrix);
	gl.uniformMatrix4fv(matProjUniformLocation, gl.FALSE, projMatrix);


  var xRotationMatrix = new Float32Array(16);
  var yRotationMatrix = new Float32Array(16);
  var yRotationMatrix2 = new Float32Array(16);
  var translateMatrix = new Float32Array(16);
  var scaleMatrix = new Float32Array(16);
  
  var identityMatrix = new Float32Array(16);
  mat4.identity(identityMatrix);
  
  var translation = vec3.create();
  var scaling = vec3.create();
  var translation2 = vec3.create();
  var angle = 0;
  var angle2 = 0;
  var angle3 = 0;
  var mouseheld = false;
  document.onkeydown = function(ev){keydown(ev, gl, matViewUniformLocation, viewMatrix); };
  canvas.onmousedown = function(ev){mouseheld=true; mouseMove(ev, gl, matViewUniformLocation, viewMatrix); }; 
  canvas.onmouseup = function(ev){ mouseheld=false; }; 
  canvas.onmousemove = function(ev){ if(mouseheld==true)mouseMove(ev, gl, matViewUniformLocation, viewMatrix) };

var loop = function(){
  	//angle =  performance.now()/17000/6*2*Math.PI;
  	angle2 = performance.now()/175/6*2*Math.PI;
  	angle3 = .25*Math.sin(2*performance.now()/1000/6*2*Math.PI);
	angle4 = .1*Math.sin(2*performance.now()/1700/6*2*Math.PI);
	angle5 = .1*Math.tan(2*performance.now()/1700/6*2*Math.PI);
	angle6 =  performance.now()/1700/6*2*Math.PI;
  	vec3.set (translation, xTrans, yTrans, zTrans);
 	vec3.set (scaling, xScale, yScale, zScale);
  	mat4.fromTranslation (translateMatrix,translation);
 	mat4.fromScaling(scaleMatrix,scaling);
 	mat4.rotate(yRotationMatrix, identityMatrix, angle, [0, 1, 0]);
  	mat4.mul(yRotationMatrix,yRotationMatrix, translateMatrix);
  	mat4.mul(yRotationMatrix, yRotationMatrix, scaleMatrix);
  	mat4.mul(worldMatrix, yRotationMatrix, identityMatrix);
 
  	if(rotate == 1){//twirl the tail
  		mat4.rotate(yRotationMatrix2, identityMatrix, angle2, [0, 1, 0]);
  		mat4.mul(worldMatrix, yRotationMatrix, yRotationMatrix2);
  	}
  	if(rotate == 2){//rotate the head back and forth
		mat4.rotate(xRotationMatrix, identityMatrix, angle3, [0, 1, 0]);
		mat4.mul(worldMatrix, xRotationMatrix, yRotationMatrix);
  	}
	if(rotate == 3){//move legs
		mat4.rotate(xRotationMatrix, identityMatrix, angle4, [1, 0, 0]);
		mat4.mul(worldMatrix, xRotationMatrix, yRotationMatrix);
  	}
	if(rotate == 4){//move legs 2: Boogaloo
		mat4.rotate(xRotationMatrix, identityMatrix, angle5, [1, 0, 0]);
		mat4.mul(worldMatrix, xRotationMatrix, yRotationMatrix);
  	}
  	if(tex == "cat"){
  		vec3.set (translation,0, -1, -10);
  		mat4.rotate(xRotationMatrix, identityMatrix, angle, [1, 0, 0]);
  		mat4.fromTranslation (translateMatrix,translation);
  		mat4.mul(worldMatrix, yRotationMatrix, xRotationMatrix);
  		mat4.mul(worldMatrix, translateMatrix, yRotationMatrix);

  	}
	
	mat4.lookAt(viewMatrix, [xEye, yEye, zEye],[xAt, yAt, zAt], [xUp, yUp, zUp]);
	gl.uniformMatrix4fv(matViewUniformLocation, gl.FALSE, viewMatrix);
	
  	gl.uniformMatrix4fv(matWorldUniformLocation, gl.FALSE, worldMatrix);
  	gl.bindTexture(gl.TEXTURE_2D, boxTexture);
	gl.activeTexture(gl.TEXTURE0);
  	gl.drawElements(gl.TRIANGLES,boxIndices.length, gl.UNSIGNED_SHORT, 0);
  	requestAnimationFrame(loop);
};
requestAnimationFrame(loop);
}

function keydown(ev, gl, n, u_ViewMatrix, viewMatrix) {
	var temp = 0;
	
    if(ev.keyCode == 68) { // The right arrow key was pressed

	 xEye += 0.3;
	  xAt += .3;
	}
    if (ev.keyCode == 65) { // The left arrow key was pressed
       xEye -= 0.3;
	   xAt -= .3;
    }
	if(ev.keyCode == 87){
	   zEye -= 0.3;
	   zAt -= .3;
	}
	if(ev.keyCode == 83){
	   zEye += 0.3;
	   zAt += .3;
	}
	if(ev.keyCode == 81){
	  // zEye += 0.1;
	   xAt -= .3;
	}
	if(ev.keyCode == 69){

	   xAt += .3;
	}
	if(ev.keyCode == 90){
		
	   yAt += .3;
	}
	if(ev.keyCode == 88){
		
	   yAt -= .3;
	}
	if(ev.keyCode == 70){
		xEye *= -1;
		zEye *= -1;
		xAt *= -1;
		zAt *= -1;
		temp++;
	}
		else { return; } // Prevent the unnecessary drawing
}

function mouseMove(ev, gl, matViewUniformLocation, viewMatrix){
	//ev.clientX = xAt;
	xAt = .08*ev.clientX-30;
	yAt = -.08*ev.clientY+30;
	//yAt += ev.clientY;
	//zEye = ev.clientZ;
	
}
	