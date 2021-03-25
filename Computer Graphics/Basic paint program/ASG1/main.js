var VSHADER_SOURCE = 
'attribute vec4 a_Position;\n'+
'void main(){\n' +
' gl_Position = a_Position;\n'+
' gl_PointSize = 8.0;\n'+
' }\n';

var FSHADER_SOURCE = 
'precision mediump float;\n'+
'uniform vec4 u_FragColor;\n' +
'void main(){\n' +
'gl_FragColor = u_FragColor;\n'+
'}\n';

function main() {
	var canvas = document.getElementById('webgl');
	var gl = getWebGLContext(canvas,false);
	if (!gl) {
		console.log('Failed to get the rendering context for WebGL');
		return;
	}
	
	if (!createShaderProgram(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
		console.log('Failed to initialize shaders.');
		return;
	}
	var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
	if(a_Position < 0){
		console.log('Failed to get the storage location of a Position');
		return;
	}
	var u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
	var mouseheld = false;
	canvas.onmousedown = function(ev){mouseheld = true; click(ev,gl,canvas,a_Position,u_FragColor)};
	canvas.onmouseup = function(ev){mouseheld = false};
	canvas.onmousemove = function(ev){if(mouseheld == true)click(ev,gl,canvas,a_Position,u_FragColor)};
	gl.clearColor(0.0,0.0,0.0,1.0);
	gl.clear(gl.COLOR_BUFFER_BIT);
}

var g_points = [];
var g_colors = [];
var shape_size;

function click(ev,gl,canvas,a_Position,u_FragColor,red,green,blue){
	var center_x = ev.clientX;
	var center_y = ev.clientY;
	var blue = document.getElementById("blue").value/255;
	var red = document.getElementById("red").value/255;
	var green = document.getElementById("green").value/255;
	
	var size = document. getElementById("size").value/300;
	shape_size = size;
	var seg = document.getElementById("seg").value;
	var rect = ev.target.getBoundingClientRect();
	
	center_x = ((center_x-rect.left) - canvas.height/2)/(canvas.height/2);
	center_y = (canvas.width/2 - (center_y-rect.top))/(canvas.width/2);

	if(document.getElementById("triangle").checked){
		drawTriangle(gl,center_x,center_y,a_Position,u_FragColor,red,green,blue);
	}
	else if(document.getElementById("square").checked){
		drawSquare(gl,center_x,center_y,a_Position,u_FragColor,red,green,blue);
	}
	else if(document.getElementById("circle").checked){
		var segs = document.getElementById("seg").value;
		if(segs == 1){
			drawTriangle(gl,center_x,center_y,a_Position,u_FragColor,red,green,blue);
		}
		else if(segs == 2){
			drawSquare(gl,center_x,center_y,a_Position,u_FragColor,red,green,blue);
		}
		else{
			drawCircle(gl,center_x,center_y,a_Position,u_FragColor,red,green,blue);

		}
	}
document.getElementById("clear").onclick = function() {
		g_points = [];
		gl.clear(gl.COLOR_BUFFER_BIT);
	};
}

function initVertexBuffers(gl,vertices,n) {
  //var vertices = new Float32Array([0, 0.5,-0.5,-0.5, 0.5,-0.5]);
  //var n = 3; 
  var vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }

  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);

  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

  var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return -1;
  }
  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);

  gl.enableVertexAttribArray(a_Position);

  return n;
}

function drawTriangle(gl,center_x,center_y,a_Position,u_FragColor,red,green,blue){
	var blue = document.getElementById("blue").value/255;
	var red = document.getElementById("red").value/255;
	var green = document.getElementById("green").value/255;

	var x1 = center_x - shape_size/2; 
	var y1 = center_y - shape_size/2;
	
	var x2 = center_x + shape_size/2;
	var y2 = center_y - shape_size/2;
	
	var x3 = center_x;
	var y3 = center_y + shape_size/2;

	var x4 = center_x + shape_size/6;
	var y4 = center_y + shape_size/6;

	var x5 = center_x - shape_size/6 ;
	var y5 = center_y + shape_size/6;

	var x6 = center_x;
	var y6 = center_y - shape_size/2;

	var x7 = center_x - shape_size/4; 
	var y7 = center_y - shape_size/2;

	var x8 = center_x + shape_size/4; 
	var y8 = center_y - shape_size/2;

	var x9 = center_x - shape_size/4;
	var y9 = center_y;

	var x10 = center_x + shape_size/4;
	var y10 = center_y;

	var x11 = center_x - shape_size/2.7;
	var y11 = center_y - shape_size/4;

	var x12 = center_x + shape_size/2.7;
	var y12 = center_y - shape_size/4;

	var x13 = center_x + shape_size/12;
	var y13 = center_y + shape_size/3;

	var x14 = center_x - shape_size/12;
	var y14 = center_y + shape_size/3;

	var x15 = center_x + shape_size/24;
	var y15 = center_y + shape_size/2.5;

	var x16 = center_x - shape_size/24;
	var y16 = center_y + shape_size/2.5;

	var x17 = center_x - shape_size/6;
	var y17 = center_y - shape_size/2;

	var x18 = center_x + shape_size/6;
	var y18 = center_y - shape_size/2;

	var x19 = center_x - shape_size/2.5;
	var y19 = center_y - shape_size/3;

	var x20 = center_x + shape_size/2.5;
	var y20 = center_y - shape_size/3;

	var x21 = center_x - shape_size/3.5;
	var y21 = center_y - shape_size/12;

	var x22 = center_x + shape_size/3.5;
	var y22 = center_y - shape_size/12;

	var x23 = center_x - shape_size/3;
	var y23 = center_y - shape_size/6;

	var x24 = center_x + shape_size/3;
	var y24 = center_y - shape_size/6;

	var x25 = center_x - shape_size/2.5;
	var y25 = center_y - shape_size/2;

	var x26 = center_x + shape_size/2.5;
	var y26 = center_y - shape_size/2;

	var x27 = center_x - shape_size/2.25;
	var y27 = center_y - shape_size/2.5;

	var x28 = center_x + shape_size/2.25;
	var y28 = center_y - shape_size/2.5;

	var x29 = center_x + shape_size/4.5;
	var y29 = center_y + shape_size/12;

	var x30 = center_x - shape_size/4.5;
	var y30 = center_y + shape_size/12;

	var x31 = center_x + shape_size/8;
	var y31 = center_y + shape_size/4;

	var x32 = center_x - shape_size/8;
	var y32 = center_y + shape_size/4;

	var x33 = center_x - shape_size/10;
	var y33 = center_y - shape_size/2;

	var x34 = center_x + shape_size/10;
	var y34 = center_y - shape_size/2;

	var x35 = center_x - shape_size/3;
	var y35 = center_y - shape_size/2;

	var x36 = center_x + shape_size/3;
	var y36 = center_y - shape_size/2;


	g_points.push([x1,y1],[x2,y2],[x3,y3],[x4,y4],[x5,y5],[x6,y6],[x7,y7],[x8,y8],
		[x9,y9],[x10,y10],[x11,y11],[x12,y12],[x13,y13],[x14,y14],[x15,y15]
		,[x16,y16],[x17,y17],[x18,y18],[x19,y19],[x20,y20],[x21,y21],[x22,y22]
		,[x23,y23],[x24,y24],[x25,y25],[x26,y26],[x27,y27],[x28,y28],[x29,y29],
		[x30,y30],[x31,y31],[x32,y32],[x33,y33],[x34,y34],[x35,y35],[x36,y36]);	
		gl.clear(gl.COLOR_BUFFER_BIT);
		var len = g_points.length;
		for(var i = 0; i < len; i++){ 
			var xy = g_points[i];
			gl.vertexAttrib3f(a_Position,xy[0],xy[1],0.0);
			gl.uniform4f(u_FragColor,red,green,blue,1); 
			gl.drawArrays(gl.POINTS, 0, 1);
		}
	}


function drawSquare(gl, center_x, center_y, a_Position,u_FragColor,red,green,blue){
		var x1 = center_x - shape_size/2; 
		var y1 = center_y - shape_size/2;
	
		var x2 = center_x + shape_size/2;
		var y2 = center_y - shape_size/2;
	
		var x3 = center_x - shape_size/2;
		var y3 = center_y + shape_size/2;

		var x4 = center_x + shape_size/2;
		var y4 = center_y + shape_size/2;

		var x5 = center_x;
		var y5 = center_y + shape_size/2;

		var x6 = center_x;
		var y6 = center_y - shape_size/2;

		var x7 = center_x + shape_size/2;
		var y7 = center_y;

		var x8 = center_x - shape_size/2;
		var y8 = center_y;

		var x9 = center_x + shape_size/2;
		var y9 = center_y + shape_size/4;

		var x10 = center_x + shape_size/2;
		var y10 = center_y - shape_size/4;

		var x11 = center_x - shape_size/2;
		var y11 = center_y + shape_size/4;

		var x12 = center_x - shape_size/2;
		var y12 = center_y - shape_size/4;

		var x13 = center_x + shape_size/4;
		var y13 = center_y - shape_size/2;

		var x14 = center_x - shape_size/4;
		var y14 = center_y - shape_size/2;

		var x15 = center_x + shape_size/4;
		var y15 = center_y + shape_size/2;

		var x16 = center_x - shape_size/4;
		var y16 = center_y + shape_size/2;

		var x17 = center_x - shape_size/8;
		var y17 = center_y + shape_size/2;

		var x18 = center_x + shape_size/8;
		var y18 = center_y + shape_size/2;

		var x19 = center_x - shape_size/2.5;
		var y19 = center_y + shape_size/2;

		var x20 = center_x + shape_size/2.5;
		var y20 = center_y + shape_size/2;

		var x21 = center_x - shape_size/2.5;
		var y21 = center_y - shape_size/2;

		var x22 = center_x + shape_size/2.5;
		var y22 = center_y - shape_size/2;

		var x23 = center_x - shape_size/8;
		var y23 = center_y - shape_size/2;

		var x24 = center_x + shape_size/8;
		var y24 = center_y - shape_size/2;

		var x25 = center_x - shape_size/8;
		var y25 = center_y - shape_size/2;

		var x26 = center_x + shape_size/8;
		var y26 = center_y - shape_size/2;

		var x27 = center_x - shape_size/2;
		var y27 = center_y - shape_size/8;

		var x28 = center_x + shape_size/2;
		var y28 = center_y - shape_size/8;

		var x29 = center_x + shape_size/2;
		var y29 = center_y + shape_size/8;

		var x30 = center_x - shape_size/2;
		var y30 = center_y + shape_size/8;

		var x31 = center_x + shape_size/2;
		var y31 = center_y + shape_size/2.5;

		var x32 = center_x - shape_size/2;
		var y32 = center_y + shape_size/2.5;

		var x33 = center_x + shape_size/2;
		var y33 = center_y - shape_size/2.5;

		var x34 = center_x - shape_size/2;
		var y34 = center_y - shape_size/2.5;

		var x35 = center_x - shape_size/16;
		var y35 = center_y + shape_size/2;

		var x36 = center_x + shape_size/16;
		var y36 = center_y + shape_size/2;

		var x37 = center_x - shape_size/16;
		var y37 = center_y - shape_size/2;

		var x38 = center_x + shape_size/16;
		var y38 = center_y - shape_size/2;

		var x39 = center_x - shape_size/2;
		var y39 = center_y - shape_size/16;

		var x40 = center_x + shape_size/2;
		var y40 = center_y - shape_size/16;

		g_points.push([x1,y1],[x2,y2],[x3,y3],[x4,y4],[x5,y5],[x6,y6],[x7,y7],
			[x7,y7],[x8,y8],[x9,y9],[x10,y10],[x11,y11],[x12,y12],[x13,y13],
			[x14,y14],[x15,y15],[x16,y16],[x17,y17],[x18,y18],[x19,y19],[x20,y20],
			[x21,y21],[x22,y22],[x23,y23],[x24,y24],[x25,y25],[x26,y26],
			[x27,y27],[x28,y28],[x29,y29],[x30,y30],[x31,y31],[x32,y32],
			[x33,y33],[x34,y34],[x35,y35],[x36,y36],[x37,y37],[x38,y38],
			[x39,y39],[x40,y40],[center_x,center_y]);	
		gl.clear(gl.COLOR_BUFFER_BIT);
		var len = g_points.length;
		for(var i = 0; i < len; i++){
			var xy = g_points[i];
			gl.vertexAttrib3f(a_Position,xy[0],xy[1],0.0); 
			gl.uniform4f(u_FragColor,red,green, blue,1.0);
			gl.drawArrays(gl.POINTS, 0, 1);
		}
}

function drawCircle(gl, center_x, center_y, a_Position,u_FragColor,red,green,blue){

	var x1 = center_x; 
	var y1 = center_y + shape_size/2;
	
	var x2 = center_x - shape_size/2;
	var y2 = center_y;
	
	var x3 = center_x + shape_size/2;
	var y3 = center_y;

	var x4 = center_x;
	var y4 = center_y - shape_size/2;

	var x5 = center_x + shape_size/3;
	var y5 = center_y + shape_size/3;

	var x6 = center_x - shape_size/3;
	var y6 = center_y - shape_size/3;

	var x7 = center_x - shape_size/3;
	var y7 = center_y + shape_size/3;

	var x8 = center_x + shape_size/3;
	var y8 = center_y - shape_size/3;

	var x9 = center_x - shape_size/4;
	var y9 = center_y + shape_size/2.5;

	var x10 = center_x + shape_size/4;
	var y10 = center_y - shape_size/2.5;

	var x11 = center_x - shape_size/2.5;
	var y11 = center_y + shape_size/4;

	var x12 = center_x + shape_size/2.5;
	var y12 = center_y - shape_size/4;

	var x13 = center_x + shape_size/2.5;
	var y13 = center_y + shape_size/4;

	var x14 = center_x - shape_size/2.5;
	var y14 = center_y - shape_size/4;

	var x15 = center_x + shape_size/4;
	var y15 = center_y + shape_size/2.5;

	var x16 = center_x - shape_size/4;
	var y16 = center_y - shape_size/2.5;

	var x17 = center_x + shape_size/16;
	var y17 = center_y + shape_size/2.12;

	var x18 = center_x - shape_size/16;
	var y18 = center_y - shape_size/2.12;

	var x19 = center_x + shape_size/16;
	var y19 = center_y - shape_size/2.12;

	var x20 = center_x - shape_size/16;
	var y20 = center_y + shape_size/2.12;

	var x21 = center_x + shape_size/2.12;
	var y21 = center_y - shape_size/16;

	var x22 = center_x - shape_size/2.12;
	var y22 = center_y + shape_size/16;

	var x23 = center_x + shape_size/2.12;
	var y23 = center_y + shape_size/16;

	var x24 = center_x - shape_size/2.12;
	var y24 = center_y - shape_size/16;

	var x25 = center_x + shape_size/2.25;
	var y25 = center_y + shape_size/5.5;

	var x26 = center_x - shape_size/2.25;
	var y26 = center_y - shape_size/5.5;

	var x27 = center_x + shape_size/2.25;
	var y27 = center_y - shape_size/5.5;

	var x28 = center_x - shape_size/2.25;
	var y28 = center_y + shape_size/5.5;

	var x29 = center_x + shape_size/5.5;
	var y29 = center_y + shape_size/2.25;

	var x30 = center_x - shape_size/5.5;
	var y30 = center_y - shape_size/2.25;

	var x31 = center_x + shape_size/5.5;
	var y31 = center_y - shape_size/2.25;

	var x32 = center_x - shape_size/5.5;
	var y32 = center_y + shape_size/2.25;

	var x33 = center_x + shape_size/7;
	var y33 = center_y - shape_size/2.15;

	var x34 = center_x - shape_size/7;
	var y34 = center_y + shape_size/2.15;

	var x35 = center_x + shape_size/7;
	var y35 = center_y + shape_size/2.15;

	var x36 = center_x - shape_size/7;
	var y36 = center_y - shape_size/2.15;

	var x37 = center_x + shape_size/2.15;
	var y37 = center_y - shape_size/7;

	var x38 = center_x - shape_size/2.15;
	var y38 = center_y + shape_size/7;

	var x39 = center_x + shape_size/2.15;
	var y39 = center_y + shape_size/7;

	var x40 = center_x - shape_size/2.15;
	var y40 = center_y - shape_size/7;

	g_points.push([x1,y1],[x2,y2],[x3,y3],[x4,y4],[x5,y5],[x6,y6],
		[x7,y7],[x8,y8],[x9,y9],[x10,y10],[x11,y11],[x12,y12],
		[x13,y13],[x14,y14],[x15,y15],[x16,y16],[x17,y17],[x18,y18],
		[x19,y19],[x20,y20],[x21,y21],[x22,y22],[x23,y23],[x24,y24],
		[x25,y25],[x26,y26],[x27,y27],[x28,y28],[x29,y29],[x30,y30],
		[x31,y31],[x32,y32],[x33,y33],[x34,y34],[x35,y35],[x36,y36],
		[x37,y37],[x38,y38],[x39,y39],[x40,y40],[center_x,center_y]);
	gl.clear(gl.COLOR_BUFFER_BIT);
	var len = g_points.length;
	for(var i = 0; i < len; i++){
		var xy = g_points[i];
		gl.vertexAttrib3f(a_Position,xy[0],xy[1],0.0);
		gl.uniform4f(u_FragColor,red,green, blue,1.0); 
		gl.drawArrays(gl.POINTS, 0, 8);
	}

}