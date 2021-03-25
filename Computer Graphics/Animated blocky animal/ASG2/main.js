/*MAIN.JS
David Grim
dgrim
CSE160
*/
//Starter code taken from youtube video "WebGL Tutorial 02 - Rotating 3D Cube"
//by Indigo Code (everything up to being able to render a rotating cube in space)

var vertexShaderText = 
[
'precision mediump float;',
'attribute vec3 vertPosition;',
'attribute vec3 vertColor;',
'varying vec3 fragColor;',
'uniform mat4 mWorld;',
'uniform mat4 mView;',
'uniform mat4 mProj;',
'uniform mat4 modelMatrix;',
'uniform mat4 scaleMatrix;',
'void main()',
'{',
'  fragColor = vertColor;',
'  gl_Position = mProj * mView * mWorld* vec4(vertPosition, 1.0);',
'}'
].join('\n');

var fragmentShaderText =
[
'precision mediump float;',
'varying vec3 fragColor;',
'void main()',
'{',
'  gl_FragColor = vec4(fragColor, 1.0);',
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
  gl.enable(gl.CULL_FACE);
  gl.frontFace(gl.CCW);
  gl.cullFace(gl.BACK);

  //
  // Create shaders
  // 

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
 [ // X, Y, Z           R, G, B
    // Top
    -1.0, 1.0, -1.0,   0.4, 1, 0.5,
    -1.0, 1.0, 1.0,    0.4, 1, 0.5,
    1.0, 1.0, 1.0,     0.4, 1, 0.5,
    1.0, 1.0, -1.0,    0.4, 1, 0.5,

    // Left
    -1.0, 1.0, 1.0,    0.4, .8, 0.5,
    -1.0, -1.0, 1.0,   0.4, .8, 0.5,
    -1.0, -1.0, -1.0,  0.4, .8, 0.5,
    -1.0, 1.0, -1.0,   0.4, .8, 0.5,

    // Right
    1.0, 1.0, 1.0,    0.7, 0.2, 0.5,
    1.0, -1.0, 1.0,   0.7, 0.2, 0.5,
    1.0, -1.0, -1.0,  0.7, 0.2, 0.5,
    1.0, 1.0, -1.0,   0.7, 0.2, 0.5,

    // Front
    1.0, 1.0, 1.0,    0.8, 0.2, 0.5,
    1.0, -1.0, 1.0,    0.8, 0.2, 0.5,
    -1.0, -1.0, 1.0,    0.8, 0.2, 0.5,
    -1.0, 1.0, 1.0,    0.8, 0.2, 0.5,

    // Back
    1.0, 1.0, -1.0,    0.7, 0.2, 0.3,
    1.0, -1.0, -1.0,    0.7, 0.2, 0.3,
    -1.0, -1.0, -1.0,    0.7, 0.2, 0.3,
    -1.0, 1.0, -1.0,    0.7, 0.2, 0.3,

    // Bottom
    -1.0, -1.0, -1.0,   0, 1, 1,
    -1.0, -1.0, 1.0,    0, 1, 1,
    1.0, -1.0, 1.0,     0, 1, 1,
    1.0, -1.0, -1.0,    0, 1, 1,


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

 //front
 drawCube(gl,boxVertices,boxIndices,program,canvas,0,0,0,1,1,.75,0);
 //middle
 drawCube(gl,boxVertices,boxIndices,program,canvas,1,0,0,1,1,.75,0);
 //butt
 drawCube(gl,boxVertices,boxIndices,program,canvas,2,0,0,1,1,.75,0);
 //back right leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,2,1,.5,.1,1.5,.18,3);
 //back left leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,2,1,-.5,.1,1.5,.18,4);
 //front right leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.75,1,.5,.1,1.5,.18,4);
 //front left leg
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.75,1,-.5,.1,1.5,.18,3);
 //front left foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.95,2.32,-.5,.1,.18,.18,3);
 //front right foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.95,2.32,.5,.1,.18,.18,4);
 //back right foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,1.8,2.32,.5,.1,.18,.18,3);
 //back left foot
 drawCube(gl,boxVertices,boxIndices,program,canvas,1.8,2.32,-.5,.1,.18,.18,4);
 //tail start
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,-1,0,.15,.25,.25,1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,-1.4,0,.15,.22,.25,1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,-1.8,-.3,.15,.22,.25,1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,-2.1,-.4,.15,.22,.25,1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,-2.3,-.4,.15,.22,.25,1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,-2.5,-.25,.15,.22,.25,1);
 drawCube(gl,boxVertices,boxIndices,program,canvas,2.85,-2.7,-.25,.15,.17,.17,1);
 //tailend
 //neck
 drawCube(gl,boxVertices,boxIndices,program,canvas,-.95,-1.3,0,.3,.3,.3,0);
 //head
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1.5,-2.3,0,.75,.75,.75,2);
 //right ear
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,-3,.5,.15,.22,.25,2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,-3.2,.5,.1,.2,.2,2);
 //left ear
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,-3,-.5,.15,.22,.25,2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-1,-3.2,-.5,.1,.2,.2,2);
 //snout
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.25,-2,0,.35,.35,.35,2);
 //nose
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,-2.25,0,.08,.08,.08,2);
 //whiskers
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,-2.05,0,.04,.04,1.2,2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,-2.15,0,.04,.04,1.2,2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.6,-2.25,0,.04,.04,1.2,2);
 //eyes
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.2,-2.65,-.5,.10,.20,.20,2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.2,-2.65,.5,.10,.20,.20,2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.25,-2.65,-.5,.10,.20,.05,2);
 drawCube(gl,boxVertices,boxIndices,program,canvas,-2.25,-2.65,.5,.10,.20,.05,2);

};

function drawCube(gl,boxVertices,boxIndices,program,canvas,xTrans,yTrans,zTrans,xScale,yScale,zScale,rotate){
 var boxVertexBufferObject = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, boxVertexBufferObject);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(boxVertices), gl.STATIC_DRAW);

  var boxIndexBufferObject = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, boxIndexBufferObject);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(boxIndices), gl.STATIC_DRAW);

  var positionAttribLocation = gl.getAttribLocation(program, 'vertPosition');
  var colorAttribLocation = gl.getAttribLocation(program, 'vertColor');
  gl.vertexAttribPointer(
    positionAttribLocation, // Attribute location
    3, // Number of elements per attribute
    gl.FLOAT, // Type of elements
    gl.FALSE,
    6 * Float32Array.BYTES_PER_ELEMENT, // Size of an individual vertex
    0 // Offset from the beginning of a single vertex to this attribute
  );
  gl.vertexAttribPointer(
    colorAttribLocation, // Attribute location
    3, // Number of elements per attribute
    gl.FLOAT, // Type of elements
    gl.FALSE,
    6 * Float32Array.BYTES_PER_ELEMENT, // Size of an individual vertex
    3 * Float32Array.BYTES_PER_ELEMENT // Offset from the beginning of a single vertex to this attribute
  );

  gl.enableVertexAttribArray(positionAttribLocation);
  gl.enableVertexAttribArray(colorAttribLocation);
  gl.useProgram(program);

  var matWorldUniformLocation = gl.getUniformLocation(program, 'mWorld');
  var matViewUniformLocation = gl.getUniformLocation(program, 'mView');
  var matProjUniformLocation = gl.getUniformLocation(program, 'mProj');

  var worldMatrix = new Float32Array(16);
  var viewMatrix = new Float32Array(16);
  var projMatrix = new Float32Array(16);
  mat4.identity(worldMatrix);
  mat4.lookAt(viewMatrix,[-20,-23,-20],[0,0,0],[0,1,0]);
  mat4.perspective(projMatrix,glMatrix.toRadian(-20),canvas.width/canvas.height,0.1,1000.0);
  
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

  var angle = 0;
  var angle2 = 0;
  var angle3 = 0;
  var loop = function(){
  	angle =  performance.now()/1700/6*2*Math.PI;
  	angle2 = performance.now()/175/6*2*Math.PI;
  	angle3 = .25*Math.sin(2*performance.now()/1000/6*2*Math.PI);
	angle4 = .28*Math.sin(3*performance.now()/1700/6*2*Math.PI);
	angle5 = .28*Math.cos(3*performance.now()/1700/6*2*Math.PI);
	
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
  	gl.uniformMatrix4fv(matWorldUniformLocation, gl.FALSE, worldMatrix);
  	gl.drawElements(gl.TRIANGLES,boxIndices.length, gl.UNSIGNED_SHORT, 0);
  	requestAnimationFrame(loop);
  };
  requestAnimationFrame(loop);
}

