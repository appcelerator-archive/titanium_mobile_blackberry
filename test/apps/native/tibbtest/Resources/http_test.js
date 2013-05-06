var url = "http://www.appcelerator.com";
 var client = Ti.Network.createHTTPClient({
     // function called when the response data is available
     onload : function(e) {
         Ti.API.info("Received text: " + this.responseText);
         alert('success');
     },
     // function called when an error occurs, including a timeout
     onerror : function(e) {
         Ti.API.debug(e.error);
         alert('error');
     },
     timeout : 5000  // in milliseconds
 });
 // Prepare the connection.
 client.open("GET", url);
 // Send the request.
 client.send();