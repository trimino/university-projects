
**Web Server** is a multi-threaded we server, capable of serving multiple requests in parallel.



## Basic Requirements
1. A webpage stored on the web server (localhost with index.html as the base html file)
2. A process will be running on the server and listening to the specified port (port 8080 is used)
3. In the web browser, if you type **http:localhost:8080/index.html**, the web server process shall fetch the index.html from the file system, compose the http response, and send it back to the browser
4. If the web browser can display the page correctly, the web server process is functiong as required for a Status Code 200 response
5. 301 and 404 Status Codes are implented as well


## Compilation Instructions

    git clone https:github.com/trimino/WebServer.git
    cd WebServer/src
    javac com/company/Server.java
    java com.company.Server
 

## Running Program 
* After running the java command open a web browser (Chrome, Mozilla, and Microsoft Edge have been tested)
* All the HTTP Request and Respones messages will be dislayed in the same terminanl as the java command is running in
* Type in the URL **http://localhost:8080/index.html** 
* Open another tap and type: **http://localhost:8080/linux.jpeg**
* For 301 Status Code open another tab and type: **http://localhost:8080/change.html**
  * This should redirect the client to the more/newIndex.html
 * For 404 Status Code open another tab and type anything after the '/': **http://localhost:8080/<type_anything> 
* Note: This can all be down without closing any tabs (Multi-Threaded Behaviour)
  
  
## Assumptions
* RUN CODE IN TERMINAL AND NOT IN INTELLIJ IDE
