const x_offset = 30;
const y_offset = 30;

var COLOUR =  '#505050';  // This is the drawing color
var radius = 3;           // Constant radio for the line
var socket = io();        // websocket to the server
var previousPosition=[0,0]; // previous position to draw a line from
var ctx = Sketch.create(); //Creating the drawing context
var firstMessage=true;    // What the first message, to start on the first value
var width;
var height;
var color = [0,0,0];

    function drawBox(colour) {
      ctx.fillStyle = ctx.strokeStyle = colour;
      ctx.lineWidth = radius;
      ctx.beginPath();
      ctx.moveTo(x_offset,y_offset);
      ctx.lineTo(x_offset,80);
      ctx.lineTo(80,80);
      ctx.lineTo(80,y_offset);
      ctx.lineTo(x_offset,y_offset)
      ctx.fill();
    }

    ctx.container = document.getElementById( 'container' ); //reference drawing canvas
    ctx.autoclear= false; // making sure it stays
    ctx.retina='auto';
    ctx.setup = function() { console.log( 'setup' );} // Setup all variables
    ctx.keydown= function() { if ( ctx.keys.C ) ctx.clear();} // handeling keydowns

    drawBox('rgb(0,0,0)');
    
    socket.on('reset', function() { // on a 'reset' message clean and reste firstMessage
      firstMessage=true;
      color = [0,0,0];
      ctx.clear();
    });

    socket.on('new-pos', function(newPosition, mode) { // handling new sensor values

      colorString = 'rgb(' + color[0] + ',' + color[1] + ',' + color[2] + ')';

      drawBox(colorString);

      if (mode == 'draw') {

        width = ctx.width - 2 * x_offset;
        height = ctx.height - 2 * y_offset;

        newPosition[0] = x_offset + newPosition[0] / 1023 * width;
        newPosition[1] = height - (newPosition[1] / 1023 * height - y_offset);

        if(firstMessage) { // if its the first message store that value as previous
          firstMessage=false;
          previousPosition=newPosition;
        } else { // any other message we use to draw.
          ctx.lineCap = 'round';
          ctx.lineJoin = 'round';
          ctx.fillStyle = ctx.strokeStyle = colorString;
          ctx.lineWidth = radius;
          ctx.beginPath();  //begin a adrawing
          ctx.moveTo( previousPosition[0], previousPosition[1] ); // from
          ctx.lineTo( newPosition[0],  newPosition[1]); // to
          ctx.stroke(); // and only draw a stroke
          previousPosition=newPosition; // update to the new position.
        }
        // See https://github.com/soulwire/sketch.js/wiki/API for sketch references
      } else {
        //TODO: Map the incoming 10-bit numbers to the height and width of the screen.
        color[0] = parseInt(newPosition[0] / 1023 * 255);
        color[1] = parseInt(newPosition[1] / 1023 * 255);
        color[2] = parseInt(newPosition[2] / 1023 * 255);
      }
    });
