/*
 * REST Lib
 */

function httpGet(theUrl) {
	
	var xmlHttp = new XMLHttpRequest();	
	xmlHttp.open( "GET", theUrl, false );
	xmlHttp.send( null );
	
	return xmlHttp.responseText;
}

/*
 * Button Controls
 */
$("#button1").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=48&intensity=128&tempo=128")
	console.log("Button 1 Event Called");
});

$("#button2").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=49&intensity=128&tempo=128")
	console.log("Button 2 Event Called");
});

$("#button3").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=50&intensity=128&tempo=128")
	console.log("Button 3 Event Called");
});

$("#button4").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=51&intensity=128&tempo=128")
	console.log("Button 4 Event Called");
});

$("#button5").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=52&intensity=128&tempo=128")
	console.log("Button 5 Event Called");
});

$("#button6").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=53&intensity=128&tempo=128")
	console.log("Button 6 Event Called");
});

$("#button7").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=54&intensity=128&tempo=128")
	console.log("Button 7 Event Called");
});

$("#button8").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=55&intensity=128&tempo=128")
	console.log("Button 8 Event Called");
});

$("#button9").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=56&intensity=128&tempo=128")
	console.log("Button 9 Event Called");
});

$("#button10").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=57&intensity=128&tempo=128")
	console.log("Button 10 Event Called");
});

$("#button11").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=58&intensity=128&tempo=128")
	console.log("Button 11 Event Called");
});

$("#button12").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=59&intensity=128&tempo=128")
	console.log("Button 12 Event Called");
});

$("#button13").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=60&intensity=128&tempo=128")
	console.log("Button 13 Event Called");
});

$("#button14").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=89&intensity=128&tempo=128")
	console.log("Button 14 Event Called");
});

$("#button15").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=130&intensity=128&tempo=128")
	console.log("Button 15 Event Called");
});

$("#button16").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=133&intensity=128&tempo=128")
	console.log("Button 16 Event Called");
});

$("#button17").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=136&intensity=128&tempo=128")
	console.log("Button 17 Event Called");
});

$("#button18").click(function( event ) {
	event.preventDefault();
	httpGet("http://192.168.1.126/sequence?id=147&intensity=128&tempo=128")
	console.log("Button 18 Event Called");
});

$("#button-rave").click(function( event ) {
	event.preventDefault();
	var value = $(".manual-input").val();
	if (!(parseInt(value) % 1 === 0)){
		return;
	}
	var request = "http://192.168.1.126/sequence?id=" + value + "&intensity=128&tempo=128";
	console.log(request);
	console.log("http://192.168.1.126/sequence?id=49&intensity=128&tempo=128");
	httpGet(request);
	console.log(value);
});